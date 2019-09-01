import numpy as np
import cv2 as cv
import glob


#criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 30, 0.001)

imagenes = glob.glob('*.jpg')
n = 13
corners=0
objpoints = [] # 3d point in real world space
imgpoints = [] # 2d points in image plane.

objp = np.zeros((7*7,3), np.float32) #Genera un arreglo de 49 renglones y 3 columnas de floats instanciados a 0.
objp[:,:2] = np.mgrid[0:7,0:7].T.reshape(-1,2)

for file_name in imagenes:

	imagen = cv.imread(file_name)
	gray = cv.cvtColor(imagen, cv.COLOR_BGR2GRAY)
	ret, corners = cv.findChessboardCorners(gray, (7,7), corners)

	if ret == True:
		objpoints.append(objp)
		imgpoints.append(corners)
		
		im = cv.drawChessboardCorners(imagen, (7,7), corners, ret)

		cv.imwrite(str(n)+'.jpg',im)
		n = n+1
	

#cv.imshow('img', imagen)
#cv.waitKey(50000)
#cv.destroyAllWindows()

#print(corners)

return_, matriz_camara, coef_distorsion, rotacion_vecs, traslacion_vecs = cv.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)

#print(matriz_camara)
#print(coef_distorsion)
#print(rotacion_vecs)
#print(traslacion_vecs)

archivo = open("Parametros.txt", "a")

archivo.write(str(len(imagenes))+" ")

# Use a for if more lines are needed.
archivo.write(str(matriz_camara[0][0])+" ")
archivo.write(str(matriz_camara[0][2])+" ")
archivo.write(str(matriz_camara[1][1])+" ")
archivo.write(str(matriz_camara[1][2])+" ")

archivo.write(str(coef_distorsion[0][0])+" ")
archivo.write(str(coef_distorsion[0][1])+" ")
archivo.write(str(coef_distorsion[0][2])+" ")
archivo.write(str(coef_distorsion[0][3])+" ")
archivo.write(str(coef_distorsion[0][4])+"\n")

archivo.close()


