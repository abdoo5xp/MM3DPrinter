f = open('UMPenguin.gcode', 'r')
i = 1
old_i = 0
previous_color = 'none'
for line in f:
    if ('3_Legs_Beak_YELLOW.stl' in line) and (previous_color != '3_Legs_Beak_YELLOW'):
            print('yellow was found at line' + str(i))
            previous_color = '3_Legs_Beak_YELLOW'
            
    elif ('2_Belly_Eyes_WHITE.stl' in line) and (previous_color != '2_Belly_Eyes_WHITE'):
            print('white was found at line' + str(i))
            previous_color = '2_Belly_Eyes_WHITE'
            
    elif ('1_Body_Pupils_BLACK.stl' in line) and (previous_color != '1_Body_Pupils_BLACK'):
            print('Black was found at line' + str(i))
            previous_color = '1_Body_Pupils_BLACK'
    i+=1
f.close()

# now getting max time elapsed 
max_time = 0
temp = ' '

f = open('UMPenguin.gcode', 'r')
for line in f:
    if(';TIME_ELAPSED' in line):
        print(line[(len(';TIME_ELAPSED')+1):-1])
f.close()