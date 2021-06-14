'''
This python code simply translate each gcode command. it tells you a brief next to every command to tell you what it does

create a python tool that you give it a gcode file, she reads each line in that gcode, tries to translate it
>> if it did successfully translate it to one of the commands below, 
the tool writes a comment in the same line saying what does this command do, 
then prints a new line and get the following command

>> if the tool fails to interprets the line/ or the line is a comment of an empty line it leaves and goes to the following


[S<temp>]	Target temperature
'''
# open file1: gcode file  > read and write
# open file2: gcode table > read only
# read line i
# check if not comment nor empty line
    #YES # get first word in it and search it in file number 2
         # write the result you got from file2 next to line i
         # i+=1
    
    #NO  # i+=1
# close both files

file2 = open('shape.gcode', 'r')
file3 = open('educational_out.gcode', 'w')

tempString = ' '
i = 0
inner_search_flag = 0

for line in file2:
    i+=1
    # print('line ' + str(i) + 'has ' + line[0]) # ---> was for debugging
    if (line[0] != ';') and ((line[0] =='G') or (line[0] =='M') or (line[0] == 'T')):
        tempString = (line.split(' '))[0]
        
        ''' if there is an end of line after we split
          that means that line contained only  G10\n 
          then remove the new line character from the line'''
        if('\n' in tempString):
            tempString = tempString[:-1]
        #print('tempString is now ' + tempString + 'x') # ---> was for debugging


        # Search the help file for that command, 
        #if you find it, write what it means in the Out file
        # if not found, write the line as it is in the Out file
        
        ''' we can make a shortcut to speed up things a little bit'''
        if('G0' in tempString or 'G1' in tempString):
            file3.write(line[0:-1] + '\t\t;; -> ' + 'G0-G1: Linear Move' + '\n')
        else:
            file1 = open('HelpSource.gcode', 'r')
            for l_line in file1:
                if(tempString in l_line):
                    file3.write(line[0:-1] + '\t\t;; -> ' + l_line[len(tempString)+1:])
                    file1.close()
                    inner_search_flag = 1
                    break
                else:
                    inner_search_flag = 0
                    None
            
            # if the command not found in the help
            if(inner_search_flag == 0):
                #print the line as it is, bCz not found in helping guide
                file3.write(line[0:-1] + '\n')

    else:
        file3.write(line)

file2.close()
file3.close()
