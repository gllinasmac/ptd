# https://www.luisllamas.es/controlar-arduino-con-python-y-la-libreria-pyserial/
# https://maker.pro/pic/tutorial/introduction-to-python-serial-ports

#Empram la llibreria PySerial
#pip install pyserial
# https://github.com/pyserial/pyserial
import serial
import time

# Velocitat de transferència de dades.
# Indica com de ràpid funciona el port sèrie
# Ha de ser la mateixa que a l'Arduino
BAUD_RATE = 9600 # En bits per segon

# Instrucció per veure els dispositius sèrie connectats:
# En linux o mac: ls /dev/cu.*
# En Windows serà COM: Ho podem veure a l'administrador de dispositius
# També si obrim Arduino IDE ho veurem

port = '/dev/cu.usbserial-1420' #APC220
#port ='/dev/cu.usbmodem14101' #Arduino
#port = '/dev/cu.Bluetooth-Incoming-Port' #Bluetooth

port_serie = serial.Serial(port, BAUD_RATE)

time.sleep(0.5)
if(port_serie.is_open):
    print(f"Connexió establerta a {port_serie.name}")

missatge = input("Quin caràcter vols enviar? ")

while missatge != 'q':
    print(f"Enviant el caràcter {missatge}")
    missatge_bytes = missatge.encode("Ascii")
    port_serie.write(missatge_bytes)
                
    missatge = input("Escriu el caràcter que vols enviar. (q per sortir) ")

print("Adeu!")
port_serie.close() # Tanca el port