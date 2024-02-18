from vpython import *

"""
PILOTA QUE ES MOU
"""
ball = sphere(pos = vector(-5,0,0), radius = 1, color = color.cyan, make_trail=True)
ball.vel = vector(0,0,0)
ball.acc = vector(0,0,0)

#Cada quan s'actualitza
dt = 0.005

"""
FLETXA VELOCITAT
"""

fletxa_vel = arrow(pos = ball.pos, axis = ball.vel, shaftwidth = 0.5, color = color.green)

def update_fletxa_vel():
    fletxa_vel.pos = ball.pos
    fletxa_vel.axis = ball.vel

"""
DIBUIXAR EIXOS
"""

def dibuixar_eixos():
    #EIXOS
    color_eix_x = color.white
    color_eix_y = color.white
    color_eix_z = color.white
    gruix_eixos = 0.5
    llarg_eixos = 25

    eix_x = arrow(pos = vector(0,0,0), axis=vector(llarg_eixos,0,0),color = color_eix_x, shaftwidth=gruix_eixos)
    text_eix_x = label(pos=vector(llarg_eixos,0,0),text="X")
    eix_y = arrow(pos = vector(0,0,0), axis=vector(0,llarg_eixos,0),color = color_eix_y, shaftwidth=gruix_eixos)
    text_eix_y = label(pos=vector(0,llarg_eixos,0),text="Y")
    eix_z = arrow(pos = vector(0,0,0), axis=vector(0,0,llarg_eixos),color = color_eix_z, shaftwidth=gruix_eixos)
    text_eix_z = label(pos=vector(0,0,llarg_eixos),text="Z")


"""
TEXT VALORS MOVIMENT
"""

wtext_acc = wtext(pos = scene.caption_anchor, text=f"Acceleració: ({ball.acc.x},{ball.acc.y},{ball.acc.z})")
scene.append_to_caption('\n')
wtext_vel = wtext(pos = scene.caption_anchor, text=f"Velocitat: ({ball.vel.x},{ball.vel.y},{ball.vel.z})")
scene.append_to_caption('\n')
wtext_pos = wtext(pos = scene.caption_anchor, text=f"Posició: ({ball.pos.x},{ball.pos.y},{ball.pos.z})")

scene.append_to_caption('\n\n')

def update_wtext():
    wtext_acc.text = f"Acceleració: ({round(ball.acc.x,1)},{round(ball.acc.y,1)},{round(ball.acc.z,1)})"
    wtext_vel.text = f"Velocitat: ({round(ball.vel.x,1)},{round(ball.vel.y,1)},{round(ball.vel.z,1)})"
    wtext_pos.text = f"Posició: ({round(ball.pos.x,1)},{round(ball.pos.y,1)},{round(ball.pos.z,1)})"

"""
SLIDERS ACCELERACIÓ
"""


def set_acc_x(s):
    ball.acc.x = s.value

def set_acc_y(s):
    ball.acc.y = s.value

def set_acc_z(s):
    ball.acc.z = s.value

scene.append_to_caption("Acceleració X: ")
slider_acc_x = slider(bind =set_acc_x, min=-5, max=5, value=ball.acc.x, step=0.1, length=220, left=15)
scene.append_to_caption('\n\n')
scene.append_to_caption("Acceleració Y: ")
slider_acc_y = slider(bind =set_acc_y, min=-5, max=5, value=ball.acc.y, step=0.1, length=220, left=15)
scene.append_to_caption('\n\n')
scene.append_to_caption("Acceleració Z: ")
slider_acc_z = slider(bind =set_acc_z, min=-5, max=5, value=ball.acc.z, step=0.1, length=220, left=15)


def update_acc():
    pass
    #Aquí rebrem les dades dels sensors.

def update_vel():
    ball.vel += ball.acc*dt

def update_pos():
    ball.pos += ball.vel*dt

"""
DIBUIXAM ESCENA
"""

dibuixar_eixos()

while True:
    update_acc()
    update_vel()
    update_pos()
    update_fletxa_vel()
    update_wtext()
        
    sleep(dt)