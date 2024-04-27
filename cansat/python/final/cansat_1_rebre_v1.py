import serial
from datetime import datetime

BAUD_RATE = 9600
# nom_port = '/dev/cu.usbserial-1420' #APC
nom_port = "/dev/cu.usbmodem14101"  # Arduino cable

cansat = serial.Serial(nom_port, BAUD_RATE)

logs = "logs/logs_"+datetime.today().strftime("%Y-%m-%d_%H:%M:%S")+".txt"

while True:
    lectura = cansat.readline().decode('Ascii').rstrip("\r\n")
    print(lectura)
    with open(logs, 'a') as file_object:
        file_object.write(lectura+'\n')
    
        
        
        
