import serial
import time
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
        file_object.write("Paquet, Equip, Pressió, Altura (BMP280), Altura (Fórmula), Velocitat(BMP280), Velocitat (Fórmula), Lectura termistor, Temperatura model teòric, Temperatura model experimental, Temperatura (BMP280), Temperatura (DHT11), Humitat, Diòxid de carboni, Òxid de nitrògen, Amoníac, UV\n")
    
    with open(nom_fitxer_sensors, 'a') as file_object:
        file_object.write("Paquet, Equip, Lectura termistor, Pressió, Altitud BMP280, Temperatura BMP280, Temperatura DHT11, Humitat, Lectura MQ135, Lectura UV \n")
    

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
        temps_cansat = int(dades[1])
        nom_equip = dades[2]
        lectura_termistor = int(dades[3])
        pressio = float(dades[4])
        altitud_bmp280 = float(dades[5])
        temperatura_bmp280 = float(dades[6])
        temperatura_dht11 = float(dades[7])
        humitat = int(dades[8])
        lectura_mq135 = int(dades[9])
        lectura_uv = int(dades[10])

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

        # Càlculs del sensor de qualitat d'aire
        mq135_voltaje = lectura_mq135 * (5.0 / 1023.0)
        mq135_resistencia = 1000*((5-mq135_voltaje)/mq135_voltaje)
        dioxid_de_carboni = 245*pow(mq135_resistencia/5463, -2.26)
        oxid_de_nitrogen = 132.6*pow(mq135_resistencia/5463, -2.74)
        amoniac = 161.7*pow(mq135_resistencia/5463, -2.26)
        
        with open(nom_fitxer_calculs, 'a') as file_object:
            entrada = f"{num_paquet},{nom_equip},{pressio},{altitud_bmp280},{round(altitud_formula,2)},{round(velocitat_bmp280,2)},{velocitat_formula},{lectura_termistor},{temperatura_model_teoric},{round(temperatura_model_experimental)},{temperatura_bmp280}, {temperatura_dht11},{humitat},{dioxid_de_carboni},{oxid_de_nitrogen},{amoniac},{lectura_uv}\n" 
            print(entrada)
            file_object.write(entrada)
        
port_serie.close() # Tanca el port

