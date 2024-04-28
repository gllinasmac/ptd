import serial
import time
import math

"""
Dades càlcul altura
"""
h0 = 0.0 #altura on ens trobam
p0 = 101325.0 # pressió a l'altura on ens trobam del dia
t0 = 21.0 # temperatura del dia
R_AST = 8.3144598 # constant dels gasos ideals
M_MOLAR = 0.0289644 # massa molar aire
G = 9.80668 # gravetat
"""
Dades càlcul temperatura
"""
VCC = 5.0 # Voltatge
R_AUX = 10000.0 #Resistència auxiliar
BETA = 3950.0 #Constant del termistir
T0 = 298.15 #Kelvin
"""
Fitxer de text
"""
nom_fitxer_sensors = "cansat1_sensors.csv"
nom_fitxer_calculs = "cansat1_calculs.csv"
nom_fitxer_gps = "cansat1_gps.csv"

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

altitud_anterior_formula = 0
altitud_anterior_bmp280 = 0
velocitat_formula = 0
velocitat_bmp280 = 0
temperatura_model_teoric = 0
temperatura_model_experimental = 0

if(port_serie.is_open):
    print(f"Connexió establerta a {port_serie.name}")
    with open(nom_fitxer_calculs, 'a') as file_object:
        file_object.write("Paquet, Temps cansat, Equip, Pressió, Altura (BMP280), Altura (Fórmula), Velocitat(BMP280), Velocitat (Fórmula), Lectura termistor, Temperatura model teòric, Temperatura model experimental, Temperatura (BMP280)\n")
    
    with open(nom_fitxer_sensors, 'a') as file_object:
        file_object.write("Paquet, Temps cansat, Equip, Lectura termistor, Pressió, Altitud BMP280, Temperatura BMP280, Lectura IR\n")

    print("Esperant dades:")

while True:
    if(port_serie.in_waiting > 0):
        lectura = port_serie.readline()
        lectura = lectura.decode('Ascii')
        lectura = lectura.rstrip("\r\n'")    
        print(lectura)
    
        with open(nom_fitxer_sensors, 'a') as file_object:
            file_object.write(f"{lectura}\n")

        dades = lectura.split(',')
        
        # Guardam dades en variables
        num_paquet = dades[0]
        temps_cansat = dades[1]
        nom_equip = dades[2]
        lectura_termistor = int(dades[3])
        pressio = float(dades[4])
        altitud_bmp280 = float(dades[5])
        temperatura_bmp280 = float(dades[6])
        lectura_ir = int(dades[7])


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
            temperatura_model_experimental = 73.74 - 21.06*math.log(R/1000)


        with open(nom_fitxer_calculs, 'a') as file_object:
            entrada = f"{num_paquet},{temps_cansat},{nom_equip},{pressio},{altitud_bmp280},{round(altitud_formula,2)},{round(velocitat_bmp280,2)},{velocitat_formula},{lectura_termistor},{temperatura_model_teoric},{round(temperatura_model_experimental)},{temperatura_bmp280}\n"
            print(entrada)
            file_object.write(entrada)
        
port_serie.close() # Tanca el port

