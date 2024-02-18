nom_fitxer = "hola_mundo.txt"


# 'a' significa 'append' i fa que afegim línies a un fitxer sense borrar lo que ja tenim
with open(nom_fitxer, 'a') as file_object:
    file_object.write("Holaaaa\n")
    file_object.write("Hola mundo 3")