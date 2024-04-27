from llibreries import *
from f_comunicacio import *
from f_fitxers import *

cansat = connectar()
    
logs = crear_fitxer_logs()
while True:
    lectura = llegir_serie(cansat)
    if lectura:
        print(lectura)
        guardar_dades(lectura, logs)

        
        
        
