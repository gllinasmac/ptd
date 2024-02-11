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
temps_inici = 0
temps_final = 0

temps_minim_punt = 0.5
temps_maxim_punt = 1.5
temps_maxim_retxa = 3

missatge = []

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
        #print(lectura)


        dada_ir = lectura

        if dada_ir == "0" and senyal_iniciat == False:

            senyal_iniciat = True
            senyal_acabat = False
            temps_inici = time()

        if dada_ir == "1" and senyal_iniciat == True:
            senyal_iniciat = False
            senyal_acabat = True

        if senyal_acabat == True:
            temps_final = time()
            temps_missatge = temps_final - temps_inici
            print(f"Duració del missatge: {temps_missatge}")

            if temps_missatge > temps_maxim_punt and temps_missatge < temps_maxim_retxa:
                
                missatge.append("R")

            if temps_missatge > temps_minim_punt and temps_missatge < temps_maxim_punt:
                
                missatge.append("P")

            if temps_missatge < temps_minim_punt:
                print("Massa curt")
                missatge = []

            if temps_missatge >= temps_maxim_retxa:
                print("Massa llarg")
                missatge = []

            print(missatge)
            senyal_acabat = False

        if len(missatge) == 3:
            print("MISSATGE REBUT!")
            if missatge[0] == "P" and missatge[1] == "P" and missatge[2] == "P":
                print("S")
            if missatge[0] == "R" and missatge[1] == "R" and missatge[2] == "R":
                print("O")

            missatge = []
            




port_serie.close() # Tanca el port