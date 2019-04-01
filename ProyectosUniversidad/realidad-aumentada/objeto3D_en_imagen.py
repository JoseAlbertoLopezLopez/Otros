import numpy as np
import cv2 as cv
import glob

#Calibracion de camara ########################################################################################################

imagenes = glob.glob('11.jpg')

corners=0
objpoints = [] # 3d point in real world space
imgpoints = [] # 2d points in image plane.

objp = np.zeros((7*7,3), np.float32) #Genera un arreglo de 49 renglones y 3 columnas de floats instanciados a 0.
objp[:,:2] = np.mgrid[0:7,0:7].T.reshape(-1,2)

for file_name in imagenes:

	imagen = cv.imread(file_name)
	gray = cv.cvtColor(imagen, cv.COLOR_BGR2GRAY)
	ret, corners = cv.findChessboardCorners(gray, (7,7), corners)

	objpoints.append(objp)
	imgpoints.append(corners)

return_, matriz_camara, coef_distorsion, rotacion_vecs, traslacion_vecs = cv.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)

#Colocar objeto en imagen #####################################################################################################

def draw_3axis(img, corners, imgpoints):
    corner = tuple(corners[0].ravel())
    img = cv.line(img, corner, tuple(imgpoints[0].ravel()), (255,0,0), 25)
    img = cv.line(img, corner, tuple(imgpoints[1].ravel()), (0,255,0), 25)
    img = cv.line(img, corner, tuple(imgpoints[2].ravel()), (0,0,255), 25)
    return img

def draw_cube(img, corners, imgpoints):
    imgpoints = np.int32(imgpoints).reshape(-1,2)

    # draw ground floor in green
    #img = cv.drawContours(img, [imgpts[:4]],-1,(0,255,0),-3)

    # draw pillars in blue color
    for i,j in zip(range(4),range(4,8)):
        img = cv.line(img, tuple(imgpoints[i]), tuple(imgpoints[j]),(0,255,0),15)

    # draw top layer in red color
    img = cv.drawContours(img, [imgpoints[4:]],-1,(0,255,0),15)
    img = cv.drawContours(img, [imgpoints[:4]],-1,(0,255,0),15)

    return img

axis_3 = np.float32([[3,0,0], [0,3,0], [0,0,-3]]).reshape(-1,3)
axis_cube = np.float32([[0,0,0], [0,3,0], [3,3,0], [3,0,0],[0,0,-3],[0,3,-3],[3,3,-3],[3,0,-3]])
print(axis_cube[4:])

for file_name in imagenes:

    imagen = cv.imread(file_name)
    gray = cv.cvtColor(imagen,cv.COLOR_BGR2GRAY)

    if ret == True:

        # Find the rotation and translation vectors.
        return_, rotacion_vecs, traslacion_vecs, inliers = cv.solvePnPRansac(objp, corners, matriz_camara, coef_distorsion)

        # project 3D points to image plane
        imgpoints, jacobiano = cv.projectPoints(axis_cube, rotacion_vecs, traslacion_vecs, matriz_camara, coef_distorsion)

        imagen = draw_cube(imagen, corners, imgpoints)
        
        cv.imwrite('cubo2.jpg',imagen)
        
        cv.namedWindow('Imagen',cv.WINDOW_NORMAL)
        cv.resizeWindow('Imagen', 600,600)
        cv.imshow('Imagen',imagen)
        k = cv.waitKey(0) & 0xff
        if k == 's':
            cv.imwrite(file_name[:6]+'.png', imagen)

cv.destroyAllWindows()
