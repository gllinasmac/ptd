import f_comunicacio, f_generals, f_fitxers
import v_comunicacio

cansat = f_comunicacio.connectar("/dev/cu.usbserial-1420")

logs = f_fitxers.crear_fitxer_logs("enviar")

while True:
    f_generals.mostrar_info_estats()

    missatge = f_generals.demanar_missatge()
    
    f_generals.mirar_si_usuari_surt(missatge)

    f_comunicacio.enviar_serie(cansat, missatge)