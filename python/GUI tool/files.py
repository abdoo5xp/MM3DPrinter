import sys,os 

#A function that takes the file name and the mode r , w ,a or r+,
#then tries to open it,
#if the file can be opened returns the file object,
#else returns None   
def openFile(filename, mode):
	try:
		file = open(filename, mode)
		print("file: "+file.name+" opened successfully")
		return file 
	except IOError:
		print("Couldn't open the file ")
		return None
		
#A function that takes the file object,
#then tries to close it,
#if the file can't be closed due to an IO error prints a msg,
#if the file can't be closed due to an Attribute Error (appears if the passed file is None) prints another msg.

def closeFile(file):
	try:
		file.close()
		print("file: "+file.name+" closed successfully")
	except IOError:
		print("Couldn't close : "+file.name)
	except AttributeError:
		print("Couldn't close a None file ")
