
cadena = "a,2,c,3.4,e"
#separa cada valor per les comes i ho guarda en una llista
dades = cadena.split(',')
print(dades)

#Així podem accedir a cada valor i guardar-lo en una variable
dada1 = dades[0]
dada2 = int(dades[1]) # Les dades són un text, per tant, s'han de convertir al tipus que volem
dada3 = dades[2]
dada4 = float(dades[3]) 
dada5 = dades[4]

print(f"Dada 1: {dada1}")
print(f"Dada 2: {dada2}")
print(f"Dada 3: {dada3}")
print(f"Dada 4: {dada4}")
print(f"Dada 5: {dada5}")


