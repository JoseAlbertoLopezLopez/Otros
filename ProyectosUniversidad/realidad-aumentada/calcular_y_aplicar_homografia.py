import numpy as np
import cv2 as cv



img_fuente = cv.imread('Libro.jpg')
puntos_img_fuente = np.array([[2830, 1209], [4362, 1304],[3730, 3014], [1673, 2432]])

img_destino = cv.imread('a2.jpeg')
puntos_img_destino = np.array([[0, 0],[img_destino.shape[0], 0],[img_destino.shape[0], img_destino.shape[1]],[0, img_destino.shape[1]]])

matriz_homografia, status = cv.findHomography(puntos_img_fuente, puntos_img_destino)
#print(matriz_homografia)

img_salida = cv.warpPerspective(img_fuente, matriz_homografia, (img_destino.shape[1],img_destino.shape[0]))

#cv.imshow("Source Image", img_fuente)
#cv.imshow("Destination Image", img_destino)

cv.imwrite('b.jpg',img_salida)

cv.namedWindow("Warped Source Image",cv.WINDOW_NORMAL)
cv.resizeWindow("Warped Source Image", 600,600)
cv.imshow("Warped Source Image", img_salida)

cv.waitKey(0)
