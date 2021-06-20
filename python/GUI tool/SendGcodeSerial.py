import SerialConn as SC
import serial
from tkinter import messagebox
import threading
import files
import re

'''The data will be sent 
    The first Two bytes will be the Number of Bytes the STM will receive 
    Then 1 byte -> character "X" or "Y" or "Z" or "E" 
    Then 2 Bytes the Length in millimeter multiplied by 1000 to avoid using floating point numbers in STM 
    ***The Least Significant Byte will be sent first*** 
'''

serialPort = None
SlicerGcodeFile =None
Sendtask = 0
PRECISION = 1000

def send(SlicerGcodePath, ComPort):
    global serialPort, Sendtask,SlicerGcodeFile
    SlicerGcodeFile = files.openFile(SlicerGcodePath, 'r')
    if SlicerGcodeFile:
        if ComPort != "NO COM":
            if Sendtask == 0:
                Sendtask = 1
                sendprocess = threading.Thread(target=sendHandler)
                sendprocess.setDaemon(True)
                serialPort = serial.Serial(ComPort, 9600, timeout=1)
                sendprocess.start()
            else:
                messagebox.showerror("Sending Error", "Wait till this Transmission is complete \n")
        else:
            messagebox.showerror("Error", "No COM Port is selected ")
    else:
        messagebox.showerror("Error", "Error Slicer Gcode File Not Found ")


def sendNumberOfBytes():
    global SlicerGcodeFile, serialPort
    line_count = 0
    '''Counting the number of lines  '''
    for line in SlicerGcodeFile:
        if line != "\n":
            line_count += 1
    '''Sending the Lines Count in the first two bytes '''
    serialPort.send(line_count.to_bytes(2, "little"))


def sendData():
    global SlicerGcodeFile, serialPort

    for line in SlicerGcodeFile:
        match = re.search(r'(\w)(\d+\.?\d+)', line)
        if match:
            '''Send the ASCII of the Character -> X or Y or Z or E or F '''
            serialPort.write(match.group(1))

            '''Convert the Floating point number with the required precision
               Then Convert it to int then to bytes then send it '''
            ExtrusionLengthString = match.group(2)
            ExtrusionLengthNumber = round(float(ExtrusionLengthString), 3) * PRECISION
            '''This is to avoid overflow of the Number if the number after precision multiplication 
                exceeds the two bytes limit
                Note: for those who are going to develop The STM Code 
                     you can have a state machine if you have received a character then start concatenating 
                     the upcoming bytes till you form your number (find another character) 
            '''
            if ExtrusionLengthNumber < 65536:
                ExtrusionLengthBytes = int(ExtrusionLengthNumber).to_bytes(2, "little")
            else:
                ExtrusionLengthBytes = int(ExtrusionLengthNumber).to_bytes(3, "little")

            serialPort.write(ExtrusionLengthBytes)

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