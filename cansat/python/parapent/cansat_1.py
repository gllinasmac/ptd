import serial
import time
import simplekml
import math

"""
Dades càlcul altura
"""
h0 = 0 #altura on ens trobam
p0 = 101325 # pressió a l'altura on ens trobam del dia
t0 = 21 # temperatura del dia
R_AST = 8.3144598 # constant dels gasos ideals
M_MOLAR = 0.0289644 # massa molar aire
G = 9.80668 # gravetat
"""
Dades càlcul temperatura
"""
VCC = 5 # Voltatge
R_AUX = 10000 #Resistència auxiliar
BETA = 3950 #Constant del termistir
T0 = 298.15 #Kelvin
"""
Fitxer de text
"""
nom_fitxer_sensors = "cansat1_sensors.csv"
nom_fitxer_calculs = "cansat1_calculs.csv"
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

altitud_anterior_formula = 0
altitud_anterior_bmp280 = 0
velocitat_formula = 0
velocitat_bmp280 = 0
temperatura_model_teoric = 0
temperatura_model_experimental = 0

if(port_serie.is_open):
    print(f"Connexió establerta a {port_serie.name}")
    with open(nom_fitxer_calculs, 'a') as file_object:
        file_object.write("Paquet, Equip, Pressió, Altura (BMP280), Altura (Fórmula), Velocitat(BMP280), Velocitat (Fórmula), Lectura termistor, Temperatura model teòric, Temperatura model experimental, Temperatura (BMP280)\n")
    
    with open(nom_fitxer_sensors, 'a') as file_object:
        file_object.write("Paquet, Equip, Lectura termistor, Pressió, Altitud BMP280, Temperatura BMP280, Lectura IR\n")
    
    with open(nom_fitxer_gps, 'a') as file_object:
        file_object.write(f"Dia,Hora,Longitud,Latitud,Altitud,Velocitat\n")
    

    print("Esperant dades:")

while True:
    if(port_serie.in_waiting > 0):
        lectura = port_serie.readline()
        lectura = lectura.decode('Ascii')
        lectura = lectura.rstrip("\r\n'")    
        print(lectura)
    
        dades = lectura.split(',')
        
        # Guardam dades en variables
        num_paquet = dades[0]
        nom_equip = dades[1]
        lectura_termistor = int(dades[2])
        pressio = float(dades[3])
        altitud_bmp280 = float(dades[4])
        temperatura_bmp280 = float(dades[5])
        lectura_ir = int(dades[6])

        with open(nom_fitxer_sensors, 'a') as file_object:
            file_object.write(f"{num_paquet},{nom_equip},{lectura_termistor},{pressio},{altitud_bmp280},{temperatura_bmp280},{lectura_ir}\n")

        if len(dades) > 7:
            dia = dades[7]
            hora = dades[8]
            latitud = float(dades[9])
            longitud = float(dades[10])
            altitud_gps = float(dades[11])
            velocitat_horitzontal_gps = float(dades[12]) #km/h

            with open(nom_fitxer_gps, 'a') as file_object:
                file_object.write(f"{dia},{hora},{latitud},{longitud},{altitud_gps},{velocitat_horitzontal_gps}\n")

            coordenades_trajectoria.append((longitud,latitud,altitud_gps))
            trajectoria.coords = coordenades_trajectoria
            kml.save(nom_fitxer_google_earth)

        #Calculam altura amb fórmula de pressió
        altitud_formula = h0 + (math.log(p0/pressio)*R_AST*t0)/(G*M_MOLAR)

        #Càlcul velocitat a partir altura
        if(altitud_anterior_formula != 0):
            velocitat_formula = altitud_anterior_formula - altitud_formula

        if(altitud_anterior_bmp280 != 0):
            velocitat_bmp280 = altitud_anterior_bmp280 - altitud_bmp280
        
        altitud_anterior_formula = altitud_formula
        altitud_anterior_bmp280 = altitud_bmp280

        # Càlcul temperatura a partir de lectura termistor
        if(lectura_termistor != 0):
            Vm = VCC * lectura_termistor / 1023.0
            R = R_AUX / ((VCC / Vm)-1)
            temperatura_model_teoric = BETA / (math.log(R/R_AUX)+(BETA / T0)) - 273.15
            temperatura_model_experimental = 0


        with open(nom_fitxer_calculs, 'a') as file_object:
            file_object.write(f"{num_paquet},{nom_equip},{pressio},{altitud_bmp280},{round(altitud_formula,2)},{round(velocitat_bmp280,2)},{velocitat_formula},{lectura_termistor},{temperatura_model_teoric},{round(temperatura_model_experimental)},{temperatura_bmp280}\n")
        
port_serie.close() # Tanca el port

