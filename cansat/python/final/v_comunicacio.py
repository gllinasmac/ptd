"""
Taxa de transferència de dades en Hz.
Ha de ser la mateixa que a l'Arduino
"""
BAUD_RATE = 9600

"""
Nom del port on està connectat Arduino.

Mirar nom a Arduino IDE o ls /dev/cu.* en Linux
"""
# nom_port = '/dev/cu.usbserial-1420' #APC
nom_port_cansat = "/dev/cu.usbmodem14101"  # Arduino cable
# nom_port = '/dev/cu.Bluetooth-Incoming-Port'

"""
ESTAT 0. MODE REPÒS
Posa el CanSat en repòs i no fa res.
"""
SENYAL_REPOS = '0'
"""
ESTAT 1. TEST DE CONNEXIÓ
Envia una senyal al cansat per a comprobar que té connexió.
S'encendrà un LED verd i s'enviarà un missatge de confirmació.
"""
SENYAL_CONNEXIO = '1' 
"""
ESTAT 2. MODE LOCALITZAR.
Començar a pitar a intervals regulars.
"""
SENYAL_LOCALITZAR = '2'
"""
ESTAT 3. MODE ENVIAR DADES
Envia les dades dels sensors.
"""
SENYAL_ENVIAR_DADES = '3'
"""
ESTAT 5. MODE GEOLOCALITZACIÓ
Envia la geolocalització del Cansat
"""
SENYAL_GEOLOCALITZACIO = '5'
"""
ESTAT 6. MODE ENVIAR MORSE
Envia la senyal del sensor IR per a comunicar-nos amb Morse.
"""
SENYAL_ENVIAR_MORSE = '6'
"""
ESTAT 7. MODE REBRE MISSATGES
Posa el CanSat esperant missatges que reproduïrà en Morse
"""
SENYAL_REBRE_MORSE = '7'

"""
Codi per acabar el programa d'enviar dades
"""
CODI_FINAL_ENVIAR = '-q'

"""Caràcter que separa l'estat del missatge"""
CARACTER_SEPARAR_MISSATGE = '/'

"""Caràcter que separa les dades enviades pels sensors"""
CARACTER_SEPARAR_DADES = ','

"""Posicions que ocupen a la lectura de dades del cansat"""
POS_NUM_PAQUET = 0
POS_NOM_CANSAT = 1
POS_TERMISTOR = 2
POS_PRESSIO = 3
POS_TEMP_BMP280 = 4