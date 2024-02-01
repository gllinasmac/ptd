"""
triangle = []

fila1 = [1]
triangle.append(fila1)
fila2 = [1,1]
triangle.append(fila2)

fila3 = []
fila3.append(1)
fila3.append(triangle[1][0]+triangle[1][1])
fila3.append(1)
triangle.append(fila3)

fila4 = []
fila4.append(1)
fila4.append(triangle[2][0]+triangle[2][1])
fila4.append(triangle[2][1]+triangle[2][2])
fila4.append(1)
triangle.append(fila4)
""" 

files = 50

triangle = []
fila1 = [1]
triangle.append(fila1)
fila2 = [1,1]
triangle.append(fila2)

for i in range(2,files):
    fila = []
    fila.append(1)
    
    for j in range(1, len(triangle[i-1])):
        fila.append(triangle[i-1][j-1]+triangle[i-1][j])

    fila.append(1)
    triangle.append(fila)

# print(triangle)


text_fila = ""
for numero in triangle[files - 1]:
    text_fila += str(numero)
    text_fila += "*"
text_fila = text_fila[:-1]


len_final = len(text_fila)

for fila in triangle:

    numeros_fila = ""
    for numero in fila:
        numeros_fila += str(numero)
        numeros_fila += " "
    numeros_fila = numeros_fila[:-1]

    len_fila_actual = len(numeros_fila)
    num_espais_blanc = int((len_final - len_fila_actual) / 2)

    espais_blanc = " "*num_espais_blanc
    text_fila = espais_blanc + numeros_fila



    print(text_fila)




