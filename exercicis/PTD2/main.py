from funcions import *

jugador = demanarNom()

benvinguda(jugador)

benvinguda()

mostrarInstruccions()


comensaJoc = False
while comensaJoc == True:
    comensaJoc = mostrarMenu() #Tornarà vertader si comença i fals si s'acaba el joc
    if(comensaJoc == True):
        # Tornarà un enter amb les rondes que es jugaran
        rondes = demanarRondes() 

        joc(rondes)

#faig un canvi
        
#faig un altre canvi

#Modifico a github
