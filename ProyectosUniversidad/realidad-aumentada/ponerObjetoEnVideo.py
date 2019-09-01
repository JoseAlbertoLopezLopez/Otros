import numpy as np
import cv2 as cv
import glob
import time

# Import video.
camara = cv.VideoCapture("chessboardVideo.mp4")
# Use built-in camera.
# camara = cv.VideoCapture(0)
aux = True

# Output video with rendered object.
videoOutput = cv.VideoWriter("chessboardVideoWithObject.mp4", cv.VideoWriter_fourcc(*'X264'), 30, (640,480), 1)


corners=0
objpoints = [] # 3d point in real world space
imgpoints = [] # 2d points in image plane.

objp = np.zeros((7*7,3), np.float32) #Genera un arreglo de 49 renglones y 3 columnas de floats instanciados a 0.
objp[:,:2] = np.mgrid[0:7,0:7].T.reshape(-1,2)

frame = 0

def draw_cube(img, imgpoints, frame):

    imgpoints = np.int32(imgpoints).reshape(-1,2)

    # draw ground floor in green
    #img = cv.drawContours(img, [imgpts[:4]],-1,(0,255,0),-3)

    # draw pillars in blue color
    #for i,j in zip(range(4),range(4,8)):
    #    img = cv.line(img, tuple(imgpoints[i]), tuple(imgpoints[j]),(0,255,0),5)

    # draw planes
    #img = cv.drawContours(img, [imgpoints[:4]],-1,(0,255,0),-1)
    plano2 = np.array([imgpoints[1], imgpoints[2], imgpoints[6], imgpoints[5]], dtype=int)
    img = cv.drawContours(img, [plano2],-1,(255,0,0),-1)
    plano3 = np.array([imgpoints[2], imgpoints[3], imgpoints[7], imgpoints[6]], dtype=int)
    img = cv.drawContours(img, [plano3],-1,(0,0,255),-1)
    plano1 = np.array([imgpoints[0], imgpoints[1], imgpoints[5], imgpoints[4]], dtype=int)
    img = cv.drawContours(img, [plano1],-1,(0,0,255),-1)
    plano4 = np.array([imgpoints[3], imgpoints[0], imgpoints[4], imgpoints[7]], dtype=int)
    img = cv.drawContours(img, [plano4],-1,(255,0,0),-1)
    img = cv.drawContours(img, [imgpoints[4:]],-1,(0,255,0),-1)
    
    # Contorno sin rellenar.
    #img = cv.drawContours(img, [imgpoints[:4]],-1,(0,255,0),2)
    # Rectangle.
    #img = cv.rectangle(img,tuple(imgpoints[1]),tuple(imgpoints[3]),(0,0,255))

    return img

def rotar(arr, frame):
    
    if arr[0][0][0] > arr[1][0][0] and (frame > 1800 and frame < 2830):
        arr = np.rot90(arr, 1, (0,1))
        arr = np.rot90(arr, 1, (0,1))
        arr = np.rot90(arr, 1, (0,1))
    
    if arr[0][0][1] > arr[1][0][1] and (frame > 1800 and frame < 2830):
        arr = np.rot90(arr, 1, (0,1))

    return arr

axis_cube = np.float32([[0,0,0], [0,3,0], [3,3,0], [3,0,0],[0,0,-3],[0,3,-3],[3,3,-3],[3,0,-3]])

while(True):

    # Capture frame-by-frame
    ret, imagen = camara.read()
    frame += 1

    gray = cv.cvtColor(imagen, cv.COLOR_BGR2GRAY)
    ret, corners = cv.findChessboardCorners(gray, (7,7), None, flags=cv.CALIB_CB_FAST_CHECK)
    
    # Rectify chessboard points if they were rotated.
    if ret:
        cornersAux = corners.reshape((7, 7, 2))
        cornersAux = rotar(cornersAux, frame)
        corners = cornersAux.reshape((49, 1, 2))
    
    objpoints.append(objp)
    imgpoints.append(corners)
    
    if ret:
        return_, matriz_camara, coef_distorsion, rotacion_vecs, traslacion_vecs = cv.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
        # Find the rotation and translation vectors.
        return_, rotacion_vecs, traslacion_vecs, inliers = cv.solvePnPRansac(objp, corners, matriz_camara, coef_distorsion)
        
        # project 3D points to image plane
        if return_:
            imgpoints, jacobiano = cv.projectPoints(axis_cube, rotacion_vecs, traslacion_vecs, matriz_camara, coef_distorsion)
            imagen = draw_cube(imagen, imgpoints, frame)
    
    objpoints = [] # 3d point in real world space
    imgpoints = [] # 2d points in image plane.

    # Display the resulting frame
    cv.imshow('frame',imagen)
    # Pause the display.
    #time.sleep(0.01)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
    
    # Save frame to video.
    videoOutput.write(imagen)

# When everything done, release the capture
camara.release()
cv.destroyAllWindows()

