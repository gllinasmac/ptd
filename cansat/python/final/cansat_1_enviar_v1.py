import serial

BAUD_RATE = 9600
# nom_port = '/dev/cu.usbserial-1420' #APC
nom_port = "/dev/cu.usbmodem14101"  # Arduino cable

cansat = serial.Serial(nom_port, BAUD_RATE)

while True:
    missatge = input(f"Quin missatge vols enviar? (escriu -q per a sortir): ")

    if missatge == '-q':
        break
    
    print(f"Enviant el missatge: {missatge}")
    missatge_bytes = missatge.encode('Ascii')
    cansat.write(missatge_bytes)
                    


print("Adeu!")
cansat.close() # Tanca el port