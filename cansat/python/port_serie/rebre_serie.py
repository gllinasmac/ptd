"""
DOCUMENTACIÓ
https://www.luisllamas.es/controlar-arduino-con-python-y-la-libreria-pyserial/
https://maker.pro/pic/tutorial/introduction-to-python-serial-ports

"""

"""
PASSA 1
Instal·lar llibreria pyserial

Obrir una terminal i executar:
sudo apt install python3-pip
pip install pyserial
Si no funciona: pip install pyserial --break-system-packages

https://github.com/pyserial/pyserial
"""

from serial import *
from time import *

"""
PASSA 2
Esbrinar el nom del port USB on hi ha connectat l'APC220

Amb l'APC220 connectat a l'entorn Linux (apareix un requadre quan connectam l'USB)
Obrim una terminal i escrivim una de les dues opcions:
ls /dev/cu.* 
ls /dev/tty*

Per estar segur que el dispositiu és el correcte, podem llevar l'usb i tornar a executar la instrucció
Si ha desaparegut és el correcte

En Windows serà COM: ho podem veure a l'administrador de dispositivius

Una altra opció és mirar el nom que apareix a l'arduino IDE
"""

"""
Escrivim el nom en aquesta variable
"""
#port = '/dev/ttyUSB0'
#portChromebook = '/dev/ttyACM0'
#port = '/dev/cu.usbserial-1410'
port ='/dev/cu.usbmodem14101' #arduino
#portBluetooth = '/dev/cu.Bluetooth-Incoming-Port'

# 9600 ha de ser la mateixa velocitat que l'arduino
port_serie = Serial(port, 9600)


if(port_serie.is_open):
    print(f"Connexió establerta a {port_serie.name}")

while True:
    #port_serie.write(b'hola')

    """
    EXPLICACIÓ NO IMPORTANT
    Les dades que rebem es guarden en el buffer fins que són llegides
    in_waiting és una variable que guarda el nombre de bytes en el buffer
    """ 
    if(port_serie.in_waiting > 0): # Si el port sèrie té dades 

        # Llegim les dades que tenim al buffer fins que trobem un bot de línia (\n\r)
        lectura = port_serie.readline()
        #print("Dades rebudes: "+str(lectura)) #b indica que són bytes.
        lectura = lectura.decode('Ascii') #Convertim de bytes a string
        #print(f"Dades transformades en string: {lectura}")
        lectura = lectura.rstrip("\r\n'") #Llevam \r\n que representa un final de línia
    
        #lectura conté el que hem enviat de l'Arduino
        print(lectura)
        #exemple: lectura = "1,Biel,440000,800,3.5"

        #print("-"*10)

        




port_serie.close() # Tanca el port