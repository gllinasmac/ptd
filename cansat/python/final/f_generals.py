import sys, os
import f_fitxers
import v_comunicacio

def acabar_programa():
    print("Adeu!")
    sys.exit()

def mirar_si_usuari_surt(text_usuari):
    if text_usuari == v_comunicacio.CODI_FINAL_ENVIAR:
        acabar_programa()

def demanar_missatge():
    missatge = input(f"Quin missatge vols enviar? ({v_comunicacio.CODI_FINAL_ENVIAR} per a sortir): ")
    return missatge

def mostrar_missatge(lectura):
    os.system("clear")
    print(f_fitxers.hora()+": "+lectura)

def mostrar_info_estats():
    print("""
          0: REPÒS -> Redueix l'activitat per estalviar energia.
          1: TEST CONNEXIÓ -> Enviam una dada al cansat. Després torna a repòs.
          2: LOCALITZAR -> El cansaat pita fins que és localitzat.
          3: ENVIAR DADES -> Envia les dades dels seus sensors
          4: REBRE MISSATGE -> Envia la lectura del sensor IR.
          5: ENVIAR MISSATGE -> Enviam un missatge al CanSat. Ha de començar amb un #.
          6: GEOLOCALITZACIO -> Envia les dades del GPS
          """)