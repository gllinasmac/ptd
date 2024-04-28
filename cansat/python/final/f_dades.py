import math
import f_generals, f_fitxers
import v_comunicacio, v_sensors


def mostrar_dades_sensors(lectura:str, nom_fitxer):
    valors = separar_valors(lectura)

    num_paquet = valors[v_comunicacio.POS_NUM_PAQUET]
    nom_cansat = valors[v_comunicacio.POS_NOM_CANSAT]

    termistor = int(valors[v_comunicacio.POS_TERMISTOR])
    Vm = v_sensors.VCC * termistor / 1023.0
    Vm - v_sensors.VCC - Vm #Si el termistor està girat
    R = v_sensors.R_AUX / ((v_sensors.VCC / Vm)-1)
    temperatura_model_teoric = v_sensors.BETA / (math.log(R/v_sensors.R_AUX)+(v_sensors.BETA / v_sensors.T0)) - 273.15
    temperatura = 73.74 - 21.06*math.log(R/1000)

    pressio = valors[v_comunicacio.POS_PRESSIO]

    if pressio != "nan":
        pressio = round(float(pressio),2)
    else:
        pressio = None
    
    altura_pressio = None 
    if pressio:
        altura_pressio = round(v_sensors.h0 + (math.log(v_sensors.p0/pressio)*v_sensors.R_AST*v_sensors.t0)/(v_sensors.G*v_sensors.M_MOLAR),2)

    temp_bmp280 = valors[v_comunicacio.POS_TEMP_BMP280]
    if temp_bmp280 != "nan":
        temp_bmp280 = round(float(temp_bmp280),2)
    else:
        temp_bmp280 = None

    missatge = f"""
Cansat: {nom_cansat}
Paquet: {num_paquet}
Lectura termistor: {termistor}
Voltatge: {round(Vm,2)} V
Resistència: {round(R,2)} Ohms
Temperatura termistor: {round(temperatura,2)} ºC
Temperatura BMP280: {temp_bmp280} ºC
Pressió: {pressio} Pa
Altura pressió: {altura_pressio}"""
    
    f_generals.mostrar_missatge(missatge)
    dades = [nom_cansat, num_paquet, termistor, round(Vm,2), round(R,2), round(temperatura,2),temp_bmp280,pressio, altura_pressio]
    f_fitxers.guardar_dades(dades,nom_fitxer)



def separar_valors(missatge:str) -> list:
    return missatge.split(v_comunicacio.CARACTER_SEPARAR_DADES)
