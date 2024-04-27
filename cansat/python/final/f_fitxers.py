from llibreries import *

def crear_fitxer_logs():
    return "logs/logs_"+datetime.today().strftime("%Y-%m-%d_%H:%M:%S")+".txt"

def guardar_dades(text, nom_fitxer):
    with open(nom_fitxer, 'a') as file_object:
        file_object.write(text+'\n')