import numpy as np
import cv2 as cv


imagen = cv.imread('Tablero_dist3.jpg')

imagen2 = cv.imread('Casa.jpg')

gray = cv.cvtColor(imagen, cv.COLOR_BGR2GRAY)

corners=0
objpoints = [] # 3d point in real world space
imgpoints = [] # 2d points in image plane.

objp = np.zeros((7*7,3), np.float32) #Genera un arreglo de 49 renglones y 3 columnas de floats instanciados a 0.
objp[:,:2] = np.mgrid[0:7,0:7].T.reshape(-1,2)

ret, corners = cv.findChessboardCorners(gray, (7,7), corners)

objpoints.append(objp)
imgpoints.append(corners)

#Dibujar mostrar esquinas de tablero encontrado.
#cv.drawChessboardCorners(imagen, (7,7), corners, ret)
#cv.namedWindow('Esquinas',cv.WINDOW_NORMAL)
#cv.resizeWindow('Esquinas', 600,600)
#cv.imshow('Esquinas', imagen)
#cv.waitKey(0)

return_, matriz_camara, coef_distorsion, rotacion_vecs, traslacion_vecs = cv.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)

imagen_sin_distorsion = cv.undistort(imagen2, matriz_camara, coef_distorsion)

cv.imwrite('undistort.jpg',imagen_sin_distorsion)

cv.namedWindow('Imagen sin distorsion',cv.WINDOW_NORMAL)
cv.resizeWindow('Imagen sin distorsion', 600,600)
cv.imshow('Imagen sin distorsion', imagen_sin_distorsion)
cv.waitKey(0)
