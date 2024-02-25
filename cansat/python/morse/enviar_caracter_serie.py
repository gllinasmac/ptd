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

#port = '/dev/cu.usbserial-1420' #APC
port ='/dev/cu.usbmodem14201' #ARDUINO
#port = '/dev/cu.Bluetooth-Incoming-Port'


#port_serie = serial.Serial(portAPC220, BAUD_RATE)
port_serie = serial.Serial(port, BAUD_RATE)
#port_serie = serial.Serial(portBluetooth, BAUD_RATE)

enviar = True

SENYAL_INICI_COMUNICACIO = 'x'

time.sleep(0.5)
if(port_serie.is_open):
    print(f"Connexió establerta a {port_serie.name}")
    time.sleep(2)
    print(f"Enviam el caràcter {SENYAL_INICI_COMUNICACIO}, esperam confirmació.")
    missatge = 'x'
    missatge_bytes = missatge.encode("Ascii")
    port_serie.write(missatge_bytes)

    while(port_serie.in_waiting == 0):
        pass

    if(port_serie.in_waiting > 0): # Si el port sèrie té dades 

        # Llegim les dades que tenim al buffer fins que trobem un bot de línia (\n\r)
        lectura = port_serie.readline()
        lectura = lectura.decode('Ascii') #Convertim de bytes a string
        lectura = lectura.rstrip("\r\n'") #Llevam \r\n que representa un final de línia

        print(lectura)




    
missatge = input("Quin caràcter vols enviar? ")

while missatge != 'q':
    print(f"S'HA ENVIAT EL MISSATGE: {missatge}")
    
    missatge_bytes = missatge.encode("Ascii")
    port_serie.write(missatge_bytes)
    # in_waiting és una variable que guarda el nombre de bytes en el buffer
    # Les dades que rebem es guarden en el buffer fins que són llegides
    # Abans de continuar enviant esperam que l'arduino ens retorni el missatge rebut.
    
    missatge = input("Escriu el caràcter que vols enviar. (q per sortir) ")

print("Adeu!")
port_serie.close() # Tanca el port