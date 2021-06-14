from tkinter import *
from tkinter import messagebox
# from PIL import ImageTK,Image
from tkinter import filedialog
from tkinter import ttk
import time
'alt+shift --> moving lines '
'ctrl+shift+ (-)'
'ctrl+shift+ (+)'

'Every thing is widget, and the root is the main window on which yo pace your widgets '
root = Tk()
root.title("Welcome to Elf Parser ")
root.geometry("800x800") # f"{width}x{height}"
# root.iconbitmap("PLACE the path to the window icon in here ")
# root.quit() that is a function that can be used to close your application

'creating the label widget'
label1 = Label(root, text="Hello there ")
label2 = Label(root, text="My name is abdullah ")
'Show it on the root window'
# label.pack()

'******************************************************************************** Grid System ********************************************************************************'

# label1.grid(row=0, column=0)
'Here we notice that the numbers are relative to each other which means column 5 here is the same as column 2 because it is relative to the last label '
# label2.grid(row=1, column=5)


'******************************************************************************** Input/entry widget  ********************************************************************************'
e = Entry(root, width=50, borderwidth=10, fg="purple")
'Columnspan means that you this widget is going to take a size of N normal columns'
# e.grid(row=0, column=0, columnspan=3, padx=10, pady=10)
e.insert(0, "Enter your name : ")
e.delete(0, 5)  # 5 can be -> END

'******************************************************************************** Buttons ********************************************************************************'
def btnaction(text):
    str = text + e.get()
    'Get the text from the input box and display it on the screen '
    label = Label(root, text=str).pack()    #NOTE:This Creates this object on the fly, and if you try to use it again it will give a none object

'So here we used lambda: to allow us to pass parameters to a function'
Btn = Button(root, text="hey you", padx=50, pady=20, command=lambda: btnaction("oh yeah "), fg="#000000", bg="red").pack()  #Another option -> state=DISABLED

'******************************************************************************** Images ********************************************************************************'
# img = ImageTK.photoImage(Image.open("Image path"))
'To add an image you have to put it in a widget so you can put it in any type of widget nearly '
# img_label = Label(image=img)
# img_label.pack()
# img_label.grid_forget()  # this api is used to delete what is in this widget


'******************************************************************************** Frames ********************************************************************************'
'Frames are the same as frames in java, ' \
'they are a way of organization for your root window and for you to place widgets on them ' \
'The frame can be packed but inside of it you can use grid AWESOME '

myframe = LabelFrame(root, text="Console", bg="black", fg="white", padx=100, pady=100, relief=SUNKEN, borderwidth=5)    #This pad goes inside of the frame
myframe.pack(padx=10, pady=10)
label3 = Label(myframe, text="trying out this new frame thing", bd=5, anchor=E, fg="white", bg="black")
label3.grid(sticky=W+E, row=0, column=0) #  is in grid args

'******************************************************************************** Radio Buttons ********************************************************************************'
# r = IntVar() # StringVar() if we want the var to be a string
'you have to set your variable an initial value '
# r.set("2")

def radiobtnaction(value):
    #update a label or something
    #r.get() to get the value of the clicked radio button to know which option is selected
    # Radiobutton(root, text="OPtion1", variable=r, value=1, command=lambda: radiobtnaction(r.get())).pack()
    # Radiobutton(root, text="OPtion2", variable=r, value=2, command=lambda: radiobtnaction(r.get())).pack()
    # Radiobutton(root, text="OPtion3", variable=r, value=3, command=lambda: radiobtnaction(r.get())).pack()
    # Radiobutton(root, text="OPtion4", variable=r, value=4, command=lambda: radiobtnaction(r.get())).pack()
    None
'Another cool way of creating Radio buttons '

selected_pizza = StringVar()
selected_pizza.set("shit")

Toppings =[
    ("pepproni", "pepproni"),
    ("pepper", "pepper"),
    ("cheese", "cheese"),
    ("creez", "creez"),
    ("shit", "shit")
]

pizza_label = Label(root, text=selected_pizza.get())
pizza_label.pack()

def pizzaSelected():
    pizza_label["text"] = selected_pizza.get()

for text, topping in Toppings:
    Radiobutton(root, text=text, value=topping, variable=selected_pizza, command=pizzaSelected).pack(anchor=W)


'******************************************************************************** message boxes ********************************************************************************'

def popup():
    messagebox.showwarning("Warning", "Oh look what you have done")

Button(root, text="Cick!", command=popup).pack()

'******************************************************************************** New window  ********************************************************************************'
'Be careful if you create a new window in a function once the function ends,' \
' the garbage collector will destroy the object so make sure to use global keyword'

newWindow = Toplevel()
newWindow.title("new window is here ")
# newWindow.destroy() this is used to close the new window

lbl = Label(newWindow,text="yaay").pack()

'******************************************************************************** file dialouges  ********************************************************************************'
root.filename = filedialog.askopenfilename(initialdir="/", title="select a file ", filetypes=(("elf", "*.elf"), ("mp3", "*.mp3"), ("hex", "*.hex"), ("All files", "*.*")))
#other diaogues returns values also use these values to di whatever you want

'******************************************************************************** Progress bar ********************************************************************************'


def step():
    for x in range(0,10):
        label.config(text=my_progress['value'])
        my_progress['value'] +=20
        root.update_idletasks()
        time.sleep(1)


def stop():
    my_progress.stop()


label = Label(root, text="shit")

my_progress = ttk.Progressbar(root, orient=HORIZONTAL,
                              length=350, mode='determinate')
my_progress.pack(pady=20)

btn = Button(root, text="progress", command=step).pack(pady=10)
btn2 = Button(root, text="Stop", command=stop).pack(pady=10)



'display the root window infinitely'
root.mainloop()

'we notice here that this print is not executed till the application is terminated'
print("hello elf file")
