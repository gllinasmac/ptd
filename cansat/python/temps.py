from time import *

# Guardam el temps inicial
temps_inici = time()

# Contam fins a 100.000
for i in range(100000):
    pass

# Guardam el temps després 
temps_final = time()

# El temps que ha passat és la resta
temps_transcorregut = temps_final - temps_inici
print(temps_transcorregut)


