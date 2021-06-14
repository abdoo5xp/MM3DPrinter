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
    SlicerGcodefile = files.openFile("SlicerGcode.gcode", 'a')
    parseGcodeFile(GcodeFile)
    files.closeFile(GcodeFile)
    files.closeFile(SlicerGcodefile)


def updatePartsList():
    global PartsList
    listIdx = 0
    for part in partsMaterials:
        if part != 'DefaultMaterial':
            PartsList.insert(listIdx, part[6:])
            listIdx += 1
    PartsList.xview()
    PartsList.yview()


def getPartsList(fileObject):
    global partsMaterials
    for line in fileObject:
        newPartmatch = re.search(r'.*\.stl', line)
        if newPartmatch:
            if newPartmatch.group() not in partsMaterials:
                partsMaterials[newPartmatch.group()] = defaultMaterial


def parseGcodeFile(fileObject):
    firstExtrusionLen = 0
    lastExtrusionLen = 0
    IsfirstFlag = 1
    CurrentPart = 'DefaultMaterial'
    for line in fileObject:
        Extrusionmatch = re.search(r'(E)(\d.*)', line)
        newPartmatch = re.search(r'.*\.stl', line)

        if Extrusionmatch:
            if IsfirstFlag:
                IsfirstFlag = 0
                firstExtrusionLen = float(Extrusionmatch.group(2))
            else:
                lastExtrusionLen = float(Extrusionmatch.group(2))

        elif newPartmatch :
            writeGcode(firstExtrusionLen, lastExtrusionLen, CurrentPart)
            CurrentPart = newPartmatch.group()
            firstExtrusionLen = lastExtrusionLen

        elif ';End of Gcode' in line:
            writeGcode(firstExtrusionLen, lastExtrusionLen, CurrentPart)


def writeGcode(first, last, partName):
    global SlicerGcodefile
    SlicerGcodefile.write('G0 ' + partsMaterials[partName] + str(round(last - first, 5)) + "\n")


def materialSelectedaction():
    None
    # global
    # PartsList.selectedMaterial.get()


SlicerGcodefile =None
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
selectedMaterial.set("M1")

MaterialsList =[
    ("M1", "X"),
    ("M2", "Y"),
    ("M3", "Z"),
    ("M4", "E")
]

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
