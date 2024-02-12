#pip install geopy

from geopy import distance, Point
from math import sqrt

#latitut (N-S), longitud (E-W), altura (m)
coords_1 = [40.001117,3.835535,100]
coords_2 = [40.005972,3.837255,500]

print(coords_1[:2]) #[:2] significa tots els valors fins al de la posició 2 (no inclòs)

#Si posam l'altura, ens dóna error.
distancia_2d = distance.geodesic(coords_1[:2],coords_2[:2]).meters

print("EN 2D")
print(f"P1: latitut = {coords_1[0]}, longitud = {coords_1[1]}")
print(f"P2: latitut = {coords_2[0]}, longitud = {coords_2[1]}")
print(f"Distància = {round(distancia_2d,2)} metres")
distancia_3d = sqrt(distancia_2d**2 + (coords_1[2] - coords_2[2])**2)
print("EN 3D")
print(f"P1: latitut = {coords_1[0]}, longitud = {coords_1[1]}, altura = {coords_1[2]}")
print(f"P2: latitut = {coords_2[0]}, longitud = {coords_2[1]}, altura = {coords_2[2]}")
print(f"Distància = {round(distancia_3d,2)} metres")

"""
Distància al satèl·lit
Total del recorregut
"""