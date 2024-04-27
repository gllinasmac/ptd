from llibreries import *


def connectar(nom_port):
    try:
        port = serial.Serial(nom_port, BAUD_RATE)
    except serial.SerialException:
        print(f"No s'ha pogut connectar al port: {nom_port}")
    else:
        time.sleep(0.5)
        if(port.is_open):
            print(f"Connexió establerta a {port.name}")

        return port
    
        

"""
Llegeix dades del port sèrie.
"""
def llegir_serie(port):
    if(port.in_waiting > 0):
        return port.readline().decode('Ascii').rstrip("\r\n")
    else:
        return None


def enviar_serie(port, missatge):
    print(f"Enviant el missatge: {missatge}")
    missatge_bytes = missatge.encode('Ascii')
    port.write(missatge_bytes)

