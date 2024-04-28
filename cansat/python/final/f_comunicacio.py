import time, serial
import f_generals
import v_comunicacio

def comprobar_connexio(port):
    time.sleep(1)
    try:
        port_obert = port.is_open
    except serial.SerialException:
        print("Error, port tancat")
        return False
    else:
        return True


def connectar(nom_port:str=v_comunicacio.nom_port_cansat) -> serial.Serial:
    """Genera una connexió amb el port

    Args
        nom_port : str
            Instància del port al qual volem enviar. 
            Default: nom definit a fitxer de variables.
    """
    while True:
        f_generals.mirar_si_usuari_surt(nom_port)
        try:
            connexio = serial.Serial(nom_port, v_comunicacio.BAUD_RATE)
        except serial.SerialException:
            print(f"No s'ha pogut connectar al port: {nom_port}")
            nom_port = input(
                f"Escriu el nom del port al que et vols connectar ({v_comunicacio.CODI_FINAL_ENVIAR} per a sortir del programa): "
            )
            f_generals.mirar_si_usuari_surt(nom_port)
        else:
            f_generals.mostrar_missatge(f"Connexió establerta a {connexio.name}")
            return connexio


def hi_ha_dades(port:serial.Serial) -> bool:
    try:
        num_dades = port.in_waiting
    except OSError:
        print("S'ha desconnectat el port")
        f_generals.acabar_programa()
    else:
        return num_dades > 0


def llegir_serie(port:serial.Serial) -> str:
    """Llegeix una línia del port sèrie.

    Args:
        port (serial object): Instància del port al qual volem enviar

    Return:
        String amb tots els caràcters fins a trobar un salt de línia.
    """

    if hi_ha_dades(port):
        return port.readline().decode("Ascii").rstrip("\r\n")



def enviar_serie(port: serial.Serial, missatge: str):
    """Envia un missatge a través del port sèrie

    Args:
        port 
            Instància del port al qual volem enviar
        missatge
            Missatge que volem enviar
    """

    print(f"Enviant el missatge: {missatge}")
    missatge_bytes = missatge.encode("Ascii")
    port.write(missatge_bytes)


def decodificar_dades(dades):
    return dades.decode("Ascii").rstrip("\r\n")

def estat(lectura : str) -> str:
    return lectura.split(v_comunicacio.CARACTER_SEPARAR_MISSATGE)[0]

def missatge(lectura:str) -> str:
    return lectura.split(v_comunicacio.CARACTER_SEPARAR_MISSATGE)[1]

