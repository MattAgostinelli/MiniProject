#Version 0.1 Matthew Agostinelli 8/6/2018
#This is the start of the py remote for the RS-7
#I want to start building the class so I can then make a GUI for the raz pi 3
#I want to use Kivy as a GUI for this project, I will use some of the functions in this class to be able to build buttons that the customer can press 
import serial
import serial.tools.list_ports
import string
import time
ser = ''
def serial_connection():
	#First I list the com ports available
	ports = list(serial.tools.list_ports.comports())
	for p in ports:
		print(p)
	#Now I get the com port numbers from the devices labeled as a Arduino COM Device	
	for port_no, description, address in ports :
		if 'Arduino' in description:
		 	COMPORT = port_no
		 	print(COMPORT+' has an Arduino Connected.....')
	#Now I set the COMPORT to the selected comport
	ser = serial.Serial(COMPORT)
	# I want to be able to change the baudrate in teh program though a settings tab
	ser.baudrate = 9600
	ser.timeout = 1
	ser.write_timeout = 1
	#close the com port before talking with unit
	ser.close()
	try:
		ser.open()
		print('Arduino is now Connected')
	except Exception :
		print("error open serial port")
		raise	
	# Check to see if the serial port is open, if not the program will error out
	if ser.is_open:
		#Flush the input and output before connecting to the unit
		ser.write(b'MLType\r\n')
		#ser.write(b'sta\r\n')
		out = ''
	#Give the ML time to respond, we need to set this to wait for a response depending on the command we use
		time.sleep(1)
		out = ser.readlines()
		print(out)
	return ser
############################################### 
def check_ML(ser):
	ver = ''
	ser.write(b'MLver\r\n')
	time.sleep(1)
	ver = ser.read_until('\r\n').decode('utf-8')
	if '1.' in ver:
		print('You are Connected to a MiniLight Version '+ver)
	else:
		print('You are not Connected to an MiniLight Please Talk with Matt A About Solution')
	return ver

def close_ML(ser):
	'''
	out = ''
	ser.write(b'MLTO\r\n')
	time.sleep(1)
	out = ser.read_until('\r\n').decode('utf-8')
	print(out)
	'''
	ser.flush()
	ser.close()

def reset_ML(ser):
	ser.write(b'MLrst\r\n')
	ser.close()

def serial_numb(ser):
	ser.write(b'MLsn\r\n')
	usn = ser.read_until('\r\n').decode('utf-8')
	print('Your Unit Serial Numbers are :',usn)
	return usn
##############################################















	