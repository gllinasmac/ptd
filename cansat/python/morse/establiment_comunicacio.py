from serial import *
from time import *


#port = '/dev/ttyUSB0'
#portChromebook = '/dev/ttyACM0'
#port = '/dev/cu.usbserial-1410'
port ='/dev/cu.usbmodem14201' #arduino
#portBluetooth = '/dev/cu.Bluetooth-Incoming-Port'

# 9600 ha de ser la mateixa velocitat que l'arduino
port_serie = Serial(port, 9600)
SENYAL_INICI_COMUNICACIO = 'x'


missatge = []

if(port_serie.is_open):
    print(f"Connexió establerta a {port_serie.name}")
    sleep(2)
    print(f"Enviam el caràcter {SENYAL_INICI_COMUNICACIO}, esperam confirmació.")
    missatge = 'x'
    missatge_bytes = missatge.encode("Ascii")
    port_serie.write(missatge_bytes)

    while(port_serie.in_waiting == 0):
        pass

while port_serie.in_waiting > 0: # Si el port sèrie té dades significa que hem rebut un missatge

    lectura = port_serie.readline() #Llegim bytes
    lectura = lectura.decode('Ascii') #Convertim a strinG
    lectura = lectura.rstrip("\r\n'") #Llevam \r\n que representa un final de línia

    print("Recepció de: "+lectura)

port_serie.close() # Tanca el port