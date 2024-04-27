#from llibreries import *
from f_comunicacio import *

from v_comunicacio import *
from v_sensors import *

cansat = connectar(nom_port_cansat)

while True:
    missatge = input(f"Quin missatge vols enviar? (escriu {CODI_FINAL_ENVIAR} per a sortir): ")

    if missatge == CODI_FINAL_ENVIAR:
        break

    enviar_serie(cansat, missatge)
                    


print("Adeu!")
cansat.close() # Tanca el port