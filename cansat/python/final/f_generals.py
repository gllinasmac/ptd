from llibreries import *
from f_comunicacio import *
from f_fitxers import *

def acabar_programa():
    print("Adeu!")
    sys.exit()

def mirar_si_usuari_surt(text_usuari):
    if text_usuari == CODI_FINAL_ENVIAR:
        acabar_programa()
    