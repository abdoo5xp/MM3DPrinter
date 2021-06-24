from PySide2.QtCore import Slot

import SerialConn as SC
import serial
from tkinter import messagebox
import threading
import files
import re
import os

'''The data will be sent 
    The first Two bytes will be the Number of Bytes the STM will receive 
    Then 1 byte -> character "X" or "Y" or "Z" or "E" 
    Then 2 Bytes the Length in millimeter multiplied by 1000 to avoid using floating point numbers in STM 
    ***The Least Significant Byte will be sent first*** 

    Add a check on the Size of the Slicer.gcode if it exceeds 65KB display an error message to the user 
    and terminate the operation 
'''

serialPort = None
SlicerGcodeFile =None
Sendtask = 0
PRECISION = 1000

def send(SlicerGcodePath, ComPort):
    global serialPort, Sendtask,SlicerGcodeFile
    if CheckGcodeFileSize(SlicerGcodePath):
        SlicerGcodeFile = files.openFile(SlicerGcodePath, 'r')
        if SlicerGcodeFile:
            if ComPort != "NO COM":
                if Sendtask == 0:
                    Sendtask = 1
                    sendprocess = threading.Thread(target=sendHandler)
                    sendprocess.setDaemon(True)
                    serialPort = serial.Serial(ComPort, 9600, timeout=10)
                    sendprocess.start()
                else:
                    messagebox.showerror("Sending Error", "Wait till this Transmission is complete \n")
            else:
                messagebox.showerror("Error", "No COM Port is selected ")
        else:
            messagebox.showerror("Error", "Error Slicer Gcode File Not Found ")
    else:
        messagebox.showerror("Error", "Error Slicer Gcode file exceeds Maximum Limit ")

def sendNumberOfBytes():
    global SlicerGcodeFile, serialPort
    line_count = 0
    '''Counting the number of lines  '''
    for line in SlicerGcodeFile:
        if line != "\n":
            line_count += 1
    print("Number of lines = ", line_count )
    print("Number of Bytes = ", line_count * 4)
    line_count *= 4
    '''Sending the Lines Count in the first two bytes '''
    serialPort.write(line_count.to_bytes(2, "little"))



def sendData():
    global serialPort
    SlicerGcodeFile.seek(0)
    bytescounter = 0
    for line in SlicerGcodeFile:
        print(line)
        match = re.search(r'(\w)(\d+\.?\d+)', line)
        if match:

            '''Send the ASCII of the Character -> X or Y or Z or E or F '''
            serialPort.write(bytes(match.group(1), 'ascii'))
            bytescounter += len(bytes(match.group(1), 'ascii'))


            '''Convert the Floating point number with the required precision
            Then Convert it to int then to bytes then send it '''
            ExtrusionLengthString = match.group(2)
            ExtrusionLengthNumber = round(float(ExtrusionLengthString), 3)
            if match.group(1) != 'F':
                ExtrusionLengthNumber *= PRECISION
                '''This is to avoid overflow of the Number if the number after precision multiplication 
                    exceeds the two bytes limit
                    Note: for those who are going to develop The STM Code 
                         you can have a state machine if you have received a character then start concatenating 
                         the upcoming bytes till you form your number (find another character) 
                '''

            '''to get your number on STM you have to shift left the upcoming bytes you are sending row data not ascii man '''
            ExtrusionLengthBytes = int(ExtrusionLengthNumber).to_bytes(3, "little")
            print(ExtrusionLengthBytes)
            bytescounter += len(ExtrusionLengthBytes)
            serialPort.write(ExtrusionLengthBytes)
    print("bytescounter = ",bytescounter)
def sendHandler():
    global serialPort, Sendtask

    sendNumberOfBytes()
    # TODO: We can add time.sleep() for (ex: 2 ms), for the STM to receive the data length if needed
    sendData()

    '''After sending the File close the Port'''
    serialPort.close()
    '''After sending the File close the File'''
    files.closeFile(SlicerGcodeFile)
    '''Refresh the Send task Flag'''
    Sendtask=0


def CheckGcodeFileSize(GcodeFilePath):
    # to use this function, make sure that you have imported 'os'
    '''
    The python os module has stat() function where we can pass the file name as argument. 
    This function returns a tuple structure that contains the file information. We can 
    then get its st_size property to get the file size in bytes.
    '''
    file_stats = os.stat(GcodeFilePath)

    # 64 KB limit, this will give us a 4,681 max number  of lines
    if (file_stats.st_size >= 65536):      
        print(f'File Size in Bytes = '+str(round(file_stats.st_size/1024,3))+ ' KB')
        return False
    else:
        return True