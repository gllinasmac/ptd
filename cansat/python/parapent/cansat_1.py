from serial import *
from time import *
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
nom_fitxer = "cansat1.csv"

"""
Esbrinar el nom del port USB on hi ha connectat l'APC220

Amb l'APC220 connectat a l'entorn Linux (apareix un requadre quan connectam l'USB)
Obrim una terminal i escrivim una de les dues opcions:
ls /dev/cu.* 
ls /dev/tty*
En Windows serà COM: ho podem veure a l'administrador de dispositivius
"""

portUSB ='/dev/cu.usbmodem14101' #Escrivim el nom del port USB

port_serie = Serial(portUSB, 9600)
altura_anterior_formula = 0
altura_anterior_bmp280 = 0
velocitat_formula = 0
velocitat_bmp280 = 0

if(port_serie.is_open):
    print(f"Connexió establerta a {port_serie.name}")
    with open(nom_fitxer, 'a') as file_object:
        file_object.write("Paquet, Equip, Pressió, Altura (BMP280), Altura (Fórmula), Velocitat(BMP280), Velocitat (Fórmula), Lectura termistor, Temperatura model teòric, Temperatura model experimental, Temperatura (BMP280)")
    
    print("Esperant dades:")

while True:
    if(port_serie.in_waiting > 0):
        lectura = port_serie.readline()
        lectura = lectura.decode('Ascii')
        lectura = lectura.rstrip("\r\n'")    
        #print(lectura)
    
        dades = lectura.split(',')

        num_paquet = dades[0]
        nom_equip = dades[1]
        pressio = dades[2]
        lectura_termistor = dades[3]
        altura_bmp280 = dades[4]
        temperatura_bmp280 = dades[5]

        altura_formula = h0 + (math.log(p0/pressio)*R_AST*t0)/(G*M_MOLAR)

        if(altura_anterior_formula != 0):
            velocitat_formula = altura_anterior_formula - altura_formula

        if(altura_anterior_bmp280 != 0):
            velocitat_bmp280 = altura_anterior_bmp280 - altura_bmp280
        
        altura_anterior_formula = altura_formula
        altura_anterior_bmp280 = altura_bmp280

        Vm = VCC * lectura_termistor / 1023.0
        R = R_AUX / ((VCC / Vm)-1)
        temperatura_model_teoric = BETA / (math.log(R/R_AUX)+(BETA / T0)) - 273.15
        temperatura_model_experimental = 0


        with open(nom_fitxer, 'a') as file_object:
            file_object.write(f"{num_paquet},{nom_equip},{pressio},{altura_bmp280},{altura_formula},{velocitat_bmp280},{velocitat_formula},{lectura_termistor},{temperatura_model_teoric},{temperatura_model_experimental},{temperatura_bmp280}")

port_serie.close() # Tanca el port

