import files
from tkinter import *
from tkinter import messagebox
# from PIL import ImageTK,Image
from tkinter import filedialog
from tkinter import ttk
import time
import os

# parts entered to the Cura software
partsColors = {}


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
    ' Get the path of the Gcode file from the text path '
    'Then open it using openfile function from your files library '
    'Then call parse function that will parse this file and display the parts in the list, after adding them '
    'in the dictionary with initial values for materials with the first material as the default material '
    None

Button(root, text="Enter", width=13, height=1, command=Enteraction, fg="black", bg="grey").place(x=400, y=93)


def Generateaction():
    None

Button(root, text="Generate", width=13, height=1, command=Generateaction, fg="black", bg="grey").place(x=400, y=153)

listyBox = Listbox(root)
listyBox.place(x=50, y=70)

i = 0
ll = ['part1','part2','part3','part4','part5']
for item in ll:
    listyBox.insert(i, ll[i])
    i += 1
'display the root window infinitely'
root.mainloop()


