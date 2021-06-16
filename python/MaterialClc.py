
X_Material_Count = 0
Y_Material_Count = 0
Z_Material_Count = 0

with open("D:\ITI\Graduation project\MM3DPrinter\python\GUI tool\SlicerGcode.gcode",'r') as file:

    for line in file :
        if 'X' in line:
            X_Material_Count+=float(line[line.find('X')+1:])
        elif 'Y' in line:
            Y_Material_Count+=float(line[line.find('Y')+1:])
        elif 'Z' in line:
            Y_Material_Count+=float(line[line.find('Z')+1:])    
            
    print("X_Material_Length = "+str(round(X_Material_Count, 3)) + "\n")
    print("X_Material_Length = "+str(round(Y_Material_Count, 3)) + "\n")
    print("X_Material_Length = "+str(round(Z_Material_Count, 3)))


