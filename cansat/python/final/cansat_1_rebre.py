from llibreries import *
from f_comunicacio import *
from f_fitxers import *


cansat = connectar(nom_port_cansat)
logs = crear_fitxer_logs()

if cansat != None:
    while True:
        lectura = llegir_serie(cansat)
        if lectura != None:
            print(lectura)
            guardar_dades(lectura, logs)

            
            
            
