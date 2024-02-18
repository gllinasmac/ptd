from vpython import *

FPS = 30

dt = 1/FPS

scene.title="Simulació cansat"

"""
PARÀMETRES
"""
#EIXOS
color_eix_x = color.white
color_eix_y = color.white
color_eix_z = color.white
gruix_eixos = 1
llarg_eixos = 150

#LLAUNA
radi_llauna = 33
altura_llauna = 115
gruix_eixos_llauna = 2
radi_centre_llauna = 5
color_llauna = color.white
color_eixos_llauna = color.magenta
color_centre_llauna = color.yellow
textura_llauna = textures.metal
opacitat_llauna_inicial = 0.75
inclinacio_llauna_inicial = vector(0,0,0) #Roll, pitch, yaw

pos_llauna_inicial = vector(0,0,0)

eix_x_llauna_inicial = vector(radi_llauna,0,0)
eix_y_llauna_inicial = vector(0,radi_llauna,0)
eix_z_llauna_inicial = vector(0,0,altura_llauna)

#ANELLA
radi_anella = 5
gruix_anella = 3

#TRONC ANELLA
llarg_tronc_anella = 5

pos_anella_inicial = vector(0,0,altura_llauna+llarg_tronc_anella+radi_anella)
pos_varilla_anella_inicial = vector(0,0,altura_llauna)

eix_anella_inicial = vector(0,1,0)
eix_varilla_anella_inicial = vector(0,0,llarg_tronc_anella)

"""
CANSAT
"""
llauna = cylinder(pos=vector(pos_llauna_inicial), axis=vector(eix_z_llauna_inicial), radius = radi_llauna, texture = textura_llauna,opacity = opacitat_llauna_inicial)
llauna.inclinacio = vector(inclinacio_llauna_inicial)


"""
EIXOS LLAUNA
"""

eix_x_llauna = arrow(pos=llauna.pos, axis = vector(eix_x_llauna_inicial)+vector(50,0,0), shaftwidth = gruix_eixos_llauna, color = color_eixos_llauna)
eix_y_llauna = arrow(pos=llauna.pos, axis = vector(eix_y_llauna_inicial)+vector(0,50,0), shaftwidth = gruix_eixos_llauna, color = color_eixos_llauna)
eix_z_llauna = arrow(pos=llauna.pos, axis = vector(eix_z_llauna_inicial)+vector(0,0,50), shaftwidth = gruix_eixos_llauna, color = color_eixos_llauna)
centre_llauna = sphere(pos = llauna.pos, radius=radi_centre_llauna,color=color_centre_llauna, make_trail = True)

text_eix_x_llauna = label(pos = llauna.pos + eix_x_llauna.axis, text = f"roll = {llauna.inclinacio.x}",height=8,color = color_eixos_llauna)
text_eix_y_llauna = label(pos = llauna.pos + eix_y_llauna.axis, text = f"pitch = {llauna.inclinacio.y}",height=8,color = color_eixos_llauna)
text_eix_z_llauna = label(pos = llauna.pos + eix_z_llauna.axis, text = f"yaw = {llauna.inclinacio.z}",height=8,color = color_eixos_llauna)


"""
ALTRES ELEMENTS
"""
anella = ring(pos = vector(pos_anella_inicial),axis = vector(eix_anella_inicial), radius = radi_anella, thickness = gruix_anella,texture = textures.metal)
varilla_anella = cylinder(pos=vector(pos_varilla_anella_inicial),axis=vector(eix_varilla_anella_inicial),radius=gruix_anella, texture = textures.metal)


scene.visible = False # show nothing yet
scene.waitfor("textures")
scene.visible = True  # show everything

"""
EIXOS
"""

eix_x = arrow(pos = vector(0,0,0), axis=vector(llarg_eixos,0,0),color = color_eix_x, shaftwidth=gruix_eixos)
text_eix_x = label(pos=vector(llarg_eixos,0,0),text="X")
eix_y = arrow(pos = vector(0,0,0), axis=vector(0,llarg_eixos,0),color = color_eix_y, shaftwidth=gruix_eixos)
text_eix_y = label(pos=vector(0,llarg_eixos,0),text="Y")
eix_z = arrow(pos = vector(0,0,0), axis=vector(0,0,llarg_eixos),color = color_eix_z, shaftwidth=gruix_eixos)
text_eix_z = label(pos=vector(0,0,llarg_eixos),text="Z")


"""
INCLINACIÓ
"""

def update_inclinacio(inclinacio):

    #X (roll)
    roll = inclinacio.x
    llauna.rotate(angle=radians(roll),axis = eix_x_llauna.axis,origin=llauna.pos)
    varilla_anella.rotate(angle=radians(roll),axis = eix_x_llauna.axis,origin=llauna.pos)
    anella.rotate(angle=radians(roll),axis = eix_x_llauna.axis,origin=llauna.pos)
    eix_y_llauna.rotate(angle=radians(roll),axis = eix_x_llauna.axis,origin=llauna.pos)
    text_eix_y_llauna.rotate(angle=radians(roll),axis = eix_x_llauna.axis,origin=llauna.pos)
    eix_z_llauna.rotate(angle=radians(roll),axis = eix_x_llauna.axis,origin=llauna.pos)
    text_eix_z_llauna.rotate(angle=radians(roll),axis = eix_x_llauna.axis,origin=llauna.pos)
    

    # Y (pitxh)
    pitch = inclinacio.y
    llauna.rotate(angle=radians(pitch),axis = eix_y_llauna.axis,origin = llauna.pos)
    varilla_anella.rotate(angle=radians(pitch),axis = eix_y_llauna.axis,origin=llauna.pos)
    anella.rotate(angle=radians(pitch),axis = eix_y_llauna.axis,origin=llauna.pos)
    eix_x_llauna.rotate(angle=radians(pitch),axis = eix_y_llauna.axis,origin=llauna.pos)
    text_eix_x_llauna.rotate(angle=radians(pitch),axis = eix_y_llauna.axis,origin=llauna.pos)
    eix_z_llauna.rotate(angle=radians(pitch),axis = eix_y_llauna.axis,origin=llauna.pos)
    text_eix_z_llauna.rotate(angle=radians(pitch),axis = eix_y_llauna.axis,origin=llauna.pos)
    

    # Z (yaw)
    yaw = inclinacio.z
    llauna.rotate(angle=radians(yaw),axis = eix_z_llauna.axis,origin=llauna.pos)
    varilla_anella.rotate(angle=radians(yaw),axis = eix_z_llauna.axis,origin=llauna.pos)
    anella.rotate(angle=radians(yaw),axis = eix_z_llauna.axis,origin=llauna.pos)
    eix_x_llauna.rotate(angle=radians(yaw),axis = eix_z_llauna.axis,origin=llauna.pos)
    text_eix_x_llauna.rotate(angle=radians(yaw),axis = eix_z_llauna.axis,origin=llauna.pos)
    eix_y_llauna.rotate(angle=radians(yaw),axis = eix_z_llauna.axis,origin=llauna.pos)
    text_eix_y_llauna.rotate(angle=radians(yaw),axis = eix_z_llauna.axis,origin=llauna.pos)
    
    

"""
BOTÓ DE RESET
"""
def reset(b):
    
    
    update_inclinacio(-llauna.inclinacio)

    llauna.inclinacio = vector(inclinacio_llauna_inicial)

    slider_roll.value = llauna.inclinacio.x
    slider_pitch.value = llauna.inclinacio.y
    slider_yaw.value = llauna.inclinacio.z
    
    llauna.pos = vector(pos_llauna_inicial)
    llauna.color = vector(color_llauna)
    menu_colors.selected = 'Metall'

    eix_x_llauna.pos= vector(pos_llauna_inicial)
    eix_y_llauna.pos= vector(pos_llauna_inicial)
    eix_z_llauna.pos= vector(pos_llauna_inicial)
    
    

    anella.pos= vector(pos_anella_inicial)
    varilla_anella.pos= vector(pos_varilla_anella_inicial)
    


    centre_llauna.pos = vector(pos_llauna_inicial)


    

    #wtext_posicio.text = f"Posició: ({centre_llauna.pos.x},{centre_llauna.pos.y},{centre_llauna.pos.z})"

boto_reset = button(bind = reset , text ="Reset")
scene.append_to_caption("\n")

"""
MENÚ COLOR
"""

def M():
    if menu_colors.selected == 'Vermell':
        llauna.color = color.red
    elif menu_colors.selected == 'Blau':
        llauna.color = color.blue
    elif menu_colors.selected == 'Verd':
        llauna.color = color.green
    elif menu_colors.selected == 'Metall':
        llauna.color = color.white

scene.append_to_caption("Color de la llauna: ")
menu_colors = menu(bind = M, choices=['Metall', 'Vermell','Blau', 'Verd'])
scene.append_to_caption("\n\n")

"""CHECKBOX MOSTRAR"""

def mostrar_eixos():
    if checkbox_eixos.checked:
        eix_x.visible = True
        eix_y.visible = True
        eix_z.visible = True
        text_eix_x.visible = True
        text_eix_y.visible = True
        text_eix_z.visible = True
    else:
        eix_x.visible = False
        eix_y.visible = False
        eix_z.visible = False
        text_eix_x.visible = False
        text_eix_y.visible = False
        text_eix_z.visible = False

checkbox_eixos = checkbox(bind = mostrar_eixos, text = "Mostrar eixos", checked = True)
scene.append_to_caption("\n\n")

mostrar_eixos()



"""
SLIDERS ROTACIÓ
"""

def set_roll():
    delta = slider_roll.value - llauna.inclinacio.x 
    update_inclinacio(vector(delta, 0, 0))
    llauna.inclinacio.x = slider_roll.value
    

def set_pitch():
    delta = slider_pitch.value - llauna.inclinacio.y
    update_inclinacio(vector(0, delta, 0))
    llauna.inclinacio.y = slider_pitch.value
    

def set_yaw():
    delta = slider_yaw.value - llauna.inclinacio.z 
    update_inclinacio(vector(0, 0, delta))
    llauna.inclinacio.z = slider_yaw.value

wtext_inclinacio = wtext(pos = scene.caption_anchor, text = f"Inclinació del cansat: ({llauna.inclinacio.x}, {llauna.inclinacio.y}, {llauna.inclinacio.z})")
scene.append_to_caption("\n\n")
scene.append_to_caption("Roll (X): ")
slider_roll = slider(bind = set_roll, min = -180, max = 180, step = 1, value = inclinacio_llauna_inicial.x, length = 220, left = 15)
scene.append_to_caption("\n")
scene.append_to_caption("Pitch (Y): ")
slider_pitch = slider(bind = set_pitch, min = -180, max = 180, step = 1, value = inclinacio_llauna_inicial.y, length = 220, left = 15)
scene.append_to_caption("\n")
scene.append_to_caption("Yaw (Z): ")
slider_yaw = slider(bind = set_yaw, min = -180, max = 180, step = 1, value = inclinacio_llauna_inicial.z, length = 220, left = 15)

def update_wtext():
    wtext_inclinacio.text = f"Inclinació del cansat: ({llauna.inclinacio.x}, {llauna.inclinacio.y}, {llauna.inclinacio.z})"
    text_eix_x_llauna.text = f"Roll = {llauna.inclinacio.x}"
    text_eix_y_llauna.text = f"Pitch = {llauna.inclinacio.y}"
    text_eix_z_llauna.text = f"Yaw = {llauna.inclinacio.z}"

while True:

    
    update_wtext()

    rate(FPS)