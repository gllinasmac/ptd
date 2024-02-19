import serial
import simplekml
import math

"""
Fitxer de text
"""
nom_fitxer_gps = "cansat1_gps.csv"
nom_fitxer_google_earth = "cansat1_trajectoria.kml"

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

"""
Google Earth
"""
kml = simplekml.Kml()
coordenades_trajectoria = []

trajectoria = kml.newlinestring(name="Cansat", 
                               description="Trajectòria cansat")

trajectoria.altitudemode = simplekml.AltitudeMode.absolute #relativetoground
trajectoria.style.linestyle.width = 3
trajectoria.style.linestyle.color = simplekml.Color.red
trajectoria.extrude = 1
#trajectoria.polystyle.fill = 0
trajectoria.polystyle.color = simplekml.Color.hexa("ff000050")
trajectoria.linestyle.gxlabelvisibility = 1

if(port_serie.is_open):
    print(f"Connexió establerta a {port_serie.name}")
    
    with open(nom_fitxer_gps, 'a') as file_object:
        file_object.write(f"Dia,Hora,Longitud,Latitud,Altitud,Velocitat\n")

    print("Esperant dades:")

while True:
    if(port_serie.in_waiting > 0):
        lectura = port_serie.readline()
        lectura = lectura.decode('Ascii')
        lectura = lectura.rstrip("\r\n'")    
        print(lectura)

        with open(nom_fitxer_gps, 'a') as file_object:
            file_object.write(f"{lectura}\n")
    
        dades = lectura.split(',')
        
        num_paquet = dades[0]
        dia = dades[1]
        hora = dades[2]
        latitud = float(dades[3])
        longitud = float(dades[4])
        altitud_gps = float(dades[5])
        velocitat_horitzontal_gps = float(dades[6]) #km/h


        coordenades_trajectoria.append((longitud,latitud,altitud_gps))
        trajectoria.coords = coordenades_trajectoria
        kml.save(nom_fitxer_google_earth)

port_serie.close() # Tanca el port

