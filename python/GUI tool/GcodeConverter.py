import files
from tkinter import *
from tkinter import messagebox
# from PIL import ImageTK,Image
from tkinter import filedialog
from tkinter import ttk
import time
import os
import re


"""""""""""""""""""""""""""""""""""""""""""""""Btns Actions """""""""""""""""""""""""""""""""""""""""""""""
def browseaction():
    'Display the file dialogue'
    root.filename = filedialog.askopenfilename(initialdir=os.getcwd(), title="Select The Gcode File ", filetypes=(("gcode", "*.gcode"),))
    if root.filename:
        GcodePathEntry.delete(0, END)
        GcodePathEntry.insert(0, root.filename)
    # TODO: check for invalid path given

def Enteraction():
    global SlicerGcodefile
    ' Get the path of the Gcode file from the text path '
    'Then open it using openfile function from your files library '
    'Then call getPartsList function that will parse this file and display the parts in the list, after adding them '
    'in the dictionary with initial values for materials with the first material as the default material '
    GcodeFile = files.openFile(GcodePathEntry.get(), 'r')
    getPartsList(GcodeFile)
    files.closeFile(GcodeFile)

    updatePartsList()


def Generateaction():
    global SlicerGcodefile
    GcodeFile = files.openFile(GcodePathEntry.get(), 'r')
    # if the file 'SlicerGcode.gcode' already exist when we open the Gui
    # then its an old version, delete it then create a new empty file with the same name.
    SlicerGcodefile = files.openFile("SlicerGcode.gcode", 'w+')
    
    # add an empty line at the beginning to add the feed rate command later
    SlicerGcodefile.write("\n\n\n\n\n") # 'G0'+' F'+'60'+'00'+'\n' = 5 bytes, so we added 5 x '\n'
    # this method is used until we find a smarter way to do it.
    
    parseGcodeFile(GcodeFile)
    files.closeFile(GcodeFile)
    files.closeFile(SlicerGcodefile)

'''This function fills the GUI List with the parts in the PartsMaterial Dict'''
def updatePartsList():
    global PartsList
    listIdx = 0
    for part in partsMaterials:
        if part != 'DefaultMaterial':
            PartsList.insert(listIdx, part[6:])
            listIdx += 1
    '''Make the list scrollable '''
    PartsList.xview()
    PartsList.yview()
    '''Automatically select the first part '''
    PartsList.select_set(0)

'''This Function fills the PartsMaterial Dict with the parts found in the Gcode File '''
def getPartsList(fileObject):
    global partsMaterials
    for line in fileObject:
        newPartmatch = re.search(r'.*\.stl', line)
        if newPartmatch:
            if newPartmatch.group() not in partsMaterials:
                partsMaterials[newPartmatch.group()] = defaultMaterial


def parseGcodeFile(fileObject):
    global SlicerGcodefile
    
    firstExtrusionLen = 0
    lastExtrusionLen = 0
    IsfirstFlag = 1
    CurrentPart = 'DefaultMaterial'

    
    Feedtemp = 0
    
    for line in fileObject:
        Extrusionmatch = re.search(r'(E)(\d+\.?\d*)', line)  # (E)(\d.*) <---- Wrong if Exxx is followed by words
        newPartmatch = re.search(r'.*\.stl', line)
        
        # the regex here recognize only G1 feed rate, which is the feed rate with given extrusion value 
        FeedRateMatch = re.search(r'G1 (F)(\d+\.?\d*)(\s)' , line)

        '''Detect if Extrusion Resets in the middle Printing Part'''
        IsResetExtruder = re.search(r'G92', line)

        '''Detect if Extrusion Resets in the middle Printing Part'''
        if IsResetExtruder:
            #Get the length of part material before resetting extrusion
            PartLength = lastExtrusionLen - firstExtrusionLen
            firstExtrusionLen = 0

        if Extrusionmatch:
            if IsfirstFlag:
                IsfirstFlag = 0
                firstExtrusionLen = float(Extrusionmatch.group(2))
            else:
                lastExtrusionLen = float(Extrusionmatch.group(2))

        elif newPartmatch :
            #Add the length of part material before resetting extrusion to The last value
            writeGcode(firstExtrusionLen, lastExtrusionLen+PartLength, CurrentPart)
            #Reset PartLength
            PartLength = 0
            CurrentPart = newPartmatch.group()
            firstExtrusionLen = lastExtrusionLen

        elif ';End of Gcode' in line:
            #Add the length of part material before resetting extrusion to The last value
            writeGcode(firstExtrusionLen, lastExtrusionLen+PartLength, CurrentPart)
            #Reset PartLength
            PartLength = 0
        
        # get the maximum feed rate in the Gcode
        if FeedRateMatch:
            # we transform Feed rate found as float because there is a float Feed rate
            if(Feedtemp < float(FeedRateMatch.group(2))):
                Feedtemp = float(FeedRateMatch.group(2))
    
    #usage of the new feed rate is gonna be in another place
    #SlicerGcodefile.seek(0)
    #tempLine = SlicerGcodefile.readline()
    SlicerGcodefile.seek(0)
    SlicerGcodefile.write("G0 F"+ str(int(Feedtemp)*2) + "\n" )
    #print('New Feed rate = 2 x Highest feedrate = '+str(int(Feedtemp)*2))



def writeGcode(first, last, partName):
    global SlicerGcodefile
    SlicerGcodefile.write('G0 ' + partsMaterials[partName] + str(round(last - first, 5)) + "\n")



def materialSelectedaction():
    global PartsList
    global selectedMaterial
    global partsMaterials

    '''The condition to avoid None type Error,
       if the user selects a material without selecting a part '''
    if PartsList.curselection():
        partsMaterials[";MESH:"+PartsList.get(PartsList.curselection()[0])] = selectedMaterial.get()




SlicerGcodefile =None
''' The default material is the skirt printed at the start of the Gcode, 
    we assign it to default material, material X '''
defaultMaterial = 'X'

# parts entered to the Cura software
partsMaterials = {'DefaultMaterial': 'X'}

'''The main window'''
root = Tk()
root.title("Gcode Converter")
root.geometry("600x400")

'''creating the label widget'''
WindowHeader = Label(root, text="Hello there ")
GcodePathLabel = Label(root, text="Gcode Path ", fg="black").place(x=50, y=10)

'''Creating path Entry for Gcode file '''
GcodePathEntry = Entry(root, width=50, borderwidth=3, fg="purple")
GcodePathEntry.place(x=50,y=35)
GcodePathEntry.insert(0, "Enter your Gcode Path  ")

'''Creating the Buttons'''
Button(root, text="Browse", width=13, height=1, command=browseaction, fg="black", bg="grey").place(x=400, y=33)
Button(root, text="Enter", width=13, height=1, command=Enteraction, fg="black", bg="grey").place(x=400, y=150)
Button(root, text="Generate", width=13, height=1, command=Generateaction, fg="black", bg="grey").place(x=400, y=350)

'''The list of parts '''
PartsList = Listbox(root)
PartsList.place(x=50, y=70, width=230)



selectedMaterial = StringVar()
selectedMaterial.set("X") # initial value of the first value selected 



''' Creating a list of tuples; each tuple has the material in 
    the GUI and the corresponding motor axis to that material'''
MaterialsList =[
    ("M1", "X"),
    ("M2", "Y"),
    ("M3", "Z"),
    ("M4", "E")
]


''' Creating the radio buttons '''
placeShift = 0
for Material, MaterialCode in MaterialsList:
    Radiobutton(root, text=Material, value=MaterialCode, variable=selectedMaterial, command=materialSelectedaction).place(x=300, y=(70 + placeShift))
    placeShift +=20


'display the root window infinitely'
root.mainloop()

'Closing the file at the end of the program '
if SlicerGcodefile:
    files.closeFile(SlicerGcodefile)

'''
; at the start, we are gonna provide length > buffer length (a = 15cm)
; after that, we're gonna provide length < buffer length (b = 8cm)
;; buffer length = (c = 10cm)

; if the length needed will exceed length given of current color, 
;;feed the rest of it from the next color
'''
