from datetime import datetime

def dia_hora():
    return datetime.today().strftime("%Y-%m-%d_%H:%M:%S")

def hora():
    return datetime.today().strftime("%H:%M:%S")

def dia():
    return datetime.today().strftime("%Y-%m-%d")

def crear_fitxer_logs(tipus):
    return "logs/logs_"+tipus+"_"+dia_hora()+".txt"

def crear_fitxer_dades():
    nom_fitxer = "logs/dades_"+dia_hora()+".csv"
    with open(nom_fitxer, 'a') as file_object:
        file_object.write("Dia,Hora,Cansat,Paquet,Termistor,Voltatge,Resistencia,Temperatura (termistor),Temperatura (BMP280),Pressió,Altura\n")
    return nom_fitxer


def guardar_log(text, nom_fitxer):
    with open(nom_fitxer, 'a') as file_object:
        file_object.write(dia()+","+hora()+','+text+'\n')

def guardar_dades(dades, nom_fitxer):
    with open(nom_fitxer,'a') as file_object:
        file_object.write(dia()+","+hora()+",")
        for i in range(len(dades)):
        
            file_object.write(str(dades[i]))
            if i != len(dades)-1:
                file_object.write(",")
            else:
                file_object.write("\n")




