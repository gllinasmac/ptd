import f_comunicacio, f_fitxers, f_generals, f_dades
import v_comunicacio


cansat = f_comunicacio.connectar("/dev/cu.usbserial-1420")

fitxer_logs = f_fitxers.crear_fitxer_logs("recepcio")
fitxer_dades = f_fitxers.crear_fitxer_dades()

while True:

    lectura = f_comunicacio.llegir_serie(cansat)
    if lectura:
        estat = f_comunicacio.estat(lectura)
        missatge = f_comunicacio.missatge(lectura)

        if estat == str(v_comunicacio.SENYAL_ENVIAR_DADES):
            f_dades.mostrar_dades_sensors(missatge,fitxer_dades)
        else:
            f_generals.mostrar_missatge(missatge)
        
        f_fitxers.guardar_log(lectura, fitxer_logs)

        
        
        
