from serial import *
from time import *


#port = '/dev/ttyUSB0'
#portChromebook = '/dev/ttyACM0'
#port = '/dev/cu.usbserial-1410'
port ='/dev/cu.usbmodem14101' #arduino
#portBluetooth = '/dev/cu.Bluetooth-Incoming-Port'

# 9600 ha de ser la mateixa velocitat que l'arduino
port_serie = Serial(port, 9600)


senyal_iniciat = False
senyal_acabat = False

comptador_senyals_ir = 0

MINIM_SENYALS_RETXA = 5 #Si rebem més 1's és una retxa

missatge = []

if(port_serie.is_open):
    print(f"Connexió establerta a {port_serie.name}")

while True:

    if(port_serie.in_waiting > 0): # Si el port sèrie té dades 

        # Llegim les dades que tenim al buffer fins que trobem un bot de línia (\n\r)
        lectura = port_serie.readline()
        lectura = lectura.decode('Ascii') #Convertim de bytes a string
        lectura = lectura.rstrip("\r\n'") #Llevam \r\n que representa un final de línia
    
        #print(lectura)

        senyal_ir = lectura


        if senyal_ir == "1" and senyal_iniciat == False:
            comptador_senyals_ir += 1
            senyal_iniciat = True


        if senyal_ir == "0" and senyal_iniciat == True:
            senyal_iniciat = False
            
            if comptador_senyals_ir > MINIM_SENYALS_RETXA:
                missatge.append("-")
            else:
                missatge.append(".")
            
            comptador_senyals_ir = 0

        if len(missatge) == 3:
            print("MISSATGE DESCODIFICAT!")
            if missatge[0] == "." and missatge[1] == "." and missatge[2] == ".":
                print("S")
            if missatge[0] == "-" and missatge[1] == "-" and missatge[2] == "-":
                print("O")

            missatge = []



port_serie.close() # Tanca el port