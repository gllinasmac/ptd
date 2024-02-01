"""
Es dona la benvinguda al jugador de manera personalitzada
"""
def benvinguda(nom = "defaultPlayer"):
    print("Hola ",nom,"que tal estàs")


"""
Demana el nom a l'usuari i torna el nom a la funció principal
"""
def demanarNom():
    nom = input("Digues el teu nom de jugador")
    return nom

def mostrarInstruccions():
    pass

def mostrarMenu():
    pass

def demanarRondes():
    pass

def joc(rondes = 3):
    torns = 0
    puntuacioJugador = 0
    puntuacioMaquina = 0
    while(torns < rondes):
        guanyador = torn()
        if guanyador == "Maquina":
            puntuacioMaquina += 1
        else:
            puntuacioJugador += 1


def torn():
    pass
