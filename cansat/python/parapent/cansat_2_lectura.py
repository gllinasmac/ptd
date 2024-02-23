import serial
import time
import math

"""
Fitxer de text
"""
nom_fitxer_sensors = "cansat2_sensors.csv"

"""
Esbrinar el nom del port USB on hi ha connectat l'APC220

Amb l'APC220 connectat a l'entorn Linux (apareix un requadre quan connectam l'USB)
Obrim una terminal i escrivim una de les dues opcions:
ls /dev/cu.* 
ls /dev/tty*
En Windows serà COM: ho podem veure a l'administrador de dispositivius
"""

#port ='/dev/cu.usbmodem14101' #Arduino
port ='/dev/cu.usbserial-1410' #APC220
port_serie = serial.Serial(port, 9600)


if(port_serie.is_open):
    print(f"Connexió establerta a {port_serie.name}")
    
    with open(nom_fitxer_sensors, 'w') as file_object: # a afegeix al final i w sobreescriu el fitxer
        file_object.write("Paquet, Temps (ms), Equip, Lectura termistor, Pressió, Altitud BMP280, Temperatura BMP280, Temperatura DHT11, Humitat, Lectura MQ135,Diòxid de carboni, Òxid de Nitrogen, Amoníac, Lectura UV \n")
    

    print("Esperant dades:")

while True:
    if(port_serie.in_waiting > 0):
        lectura = port_serie.readline()
        lectura = lectura.decode('Ascii')
        lectura = lectura.rstrip("\r\n'")    
        print(lectura)
    
        
        with open(nom_fitxer_sensors, 'a') as file_object:
            file_object.write(f"{lectura}\n")
        

port_serie.close() # Tanca el port

