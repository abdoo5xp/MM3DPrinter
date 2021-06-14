import files
from tkinter import *
from tkinter import messagebox
# from PIL import ImageTK,Image
from tkinter import filedialog
from tkinter import ttk
import time
import os
import re

defaultMaterial = 'X'

# parts entered to the Cura software
partsColors = {'DefaultMaterial': 'X',
               ';MESH:1_Body_Pupils_BLACK.stl': 'X',
               ';MESH:3_Legs_Beak_YELLOW.stl': 'Y',
               ';MESH:2_Belly_Eyes_WHITE.stl': 'Z'}


'Every thing is widget, and the root is the main window on which yo pace your widgets '
root = Tk()
root.title("Gcode Converter")
root.geometry("600x400") # f"{width}x{height}"

'creating the label widget'
WindowHeader = Label(root, text="Hello there ")
GcodePathLabel = Label(root, text="Gcode Path ", fg="black").place(x=50, y=10)

GcodePathEntry = Entry(root, width=50, borderwidth=3, fg="purple")
GcodePathEntry.place(x=50,y=35)
# e.grid(row=0, column=0, columnspan=3, padx=10, pady=10)
GcodePathEntry.insert(0, "Enter your Gcode Path  ")


def browseaction():
    'Display the file dialogue'
    root.filename = filedialog.askopenfilename(initialdir=os.getcwd(), title="Select The Gcode File ", filetypes=(("gcode", "*.gcode"),))
    if root.filename:
        GcodePathEntry.delete(0, END)
        GcodePathEntry.insert(0, root.filename)

Button(root, text="Browse", width=13, height=1, command=browseaction, fg="black", bg="grey").place(x=400, y=33)


def Enteraction():
    global SlicerGcodefile
    ' Get the path of the Gcode file from the text path '
    'Then open it using openfile function from your files library '
    'Then call parse function that will parse this file and display the parts in the list, after adding them '
    'in the dictionary with initial values for materials with the first material as the default material '
    GcodeFile = files.openFile(GcodePathEntry.get(), 'r')
    SlicerGcodefile = files.openFile("SlicerGcode.gcode", 'a')
    parseGcodeFile(GcodeFile)


Button(root, text="Enter", width=13, height=1, command=Enteraction, fg="black", bg="grey").place(x=400, y=150)


def Generateaction():
    None

Button(root, text="Generate", width=13, height=1, command=Generateaction, fg="black", bg="grey").place(x=400, y=350)

listyBox = Listbox(root)
listyBox.place(x=50, y=70)

i = 0
ll = ['part1','part2','part3','part4','part5']
for item in ll:
    listyBox.insert(i, ll[i])
    i += 1


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
            
        elif (newPartmatch) or (';End of Gcode' in line):
            writeGcode(firstExtrusionLen, lastExtrusionLen, CurrentPart)
            CurrentPart = newPartmatch.group()
            firstExtrusionLen = lastExtrusionLen
        #reset the object before going into the next iteration
        Extrusionmatch = 0
        newPartmatch   = 0



def writeGcode(first, last, partName):
    global SlicerGcodefile
    SlicerGcodefile.write('G0 '+ partsColors[partName] + str(round(last-first,5))+"\n")



'display the root window infinitely'
root.mainloop()

'Closing the file at the end of the program '
files.closeFile(SlicerGcodefile)

'''
; at the start, we are gonna provide length > buffer length (a = 15cm)
; after that, we're gonna provide length < buffer length (b = 8cm)
;; buffer length = (c = 10cm)

; if the length needed will exceed length given of current color, 
;;feed the rest of it from the next color
'''
