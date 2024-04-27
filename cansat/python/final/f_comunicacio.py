from llibreries import *
from f_comunicacio import *
from f_fitxers import *
from f_generals import *


def comprobar_connexio(port):
    time.sleep(0.5)
    try:
        port_obert = port.is_open
    except serial.SerialException:
        print("Error, port tancat")
    else:
        if(port_obert):
            print(f"Connexió establerta a {port.name}")
    
def connectar(nom_port = nom_port_cansat):
    while True:
        mirar_si_usuari_surt(nom_port)
        try:
            cansat = serial.Serial(nom_port, BAUD_RATE)
        except serial.SerialException:
            print(f"No s'ha pogut connectar al port: {nom_port}")
            nom_port = input(f"Escriu el nom del port al que et vols connectar ({CODI_FINAL_ENVIAR} per a sortir del programa): ")
            mirar_si_usuari_surt(nom_port)
        else:
            comprobar_connexio(cansat)
            return cansat
    


def hi_ha_dades(port):
    try:
        num_dades = port.in_waiting
    except serial.SerialException:
        print("S'ha desconnectat el port")
        acabar_programa()
    except OSError:
        print("S'ha desconnectat el port")
        acabar_programa()

    
    else:
        return num_dades > 0

"""
Llegeix dades del port sèrie.
"""
def llegir_serie(port):

    if(hi_ha_dades(port)):
        return port.readline().decode('Ascii').rstrip("\r\n")

def enviar_serie(port, missatge):
    print(f"Enviant el missatge: {missatge}")
    missatge_bytes = missatge.encode('Ascii')
    port.write(missatge_bytes)




def decodificar_dades(dades):
     return dades.decode('Ascii').rstrip("\r\n")
