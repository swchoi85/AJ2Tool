from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtCore import Qt, pyqtSignal

import sys
import cv2
import time
import numpy as np


def getPixmap(img):
     ndim = img.ndim
     if ( ndim > 2 ) :
         height, width, channel = img.shape
         bytesPerLine = 3 * width
         qImg = QImage(img.data, width, height, bytesPerLine, QImage.Format_RGB888)
     else:
         height, width = img.shape
         bytesPerLine = 1 * width
         qImg = QImage(img.data, width, height, bytesPerLine, QImage.Format_Grayscale8)
     return QPixmap.fromImage(qImg)

class Thread1(QThread):
    data = pyqtSignal(QPixmap)

    def getEmpty(self):
        return self.empty;

    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.qPixmapFileVar = QPixmap()
        self.image = np.zeros((0,0), np.uint8)
        self.empty = np.zeros((0,0), np.uint8)
        self.rImg = np.zeros((0,0), np.uint8)
        self.lImg = np.zeros((0,0), np.uint8)
        self.exp  = 1000

    def run(self):
        self.lImg = np.zeros((0,0), np.uint8)
        self.rImg = np.zeros((0,0), np.uint8)
        self.cap = cv2.VideoCapture(0)
        self.cap.set(3,800)
        self.cap.set(4,1200)
        self.cap.set(cv2.CAP_PROP_EXPOSURE, 200)
        self.image = np.zeros((0,0), np.uint8)
#//        print("backend ",self.cap.getBackendName())
        iImg = self.empty.copy()
        for i in range(1000):
            retval,camImg = self.cap.read()
            if not (retval):
                break;

            camImg = cv2.cvtColor(camImg, cv2.COLOR_BGR2GRAY)
            cw,ch = camImg.shape
            if ( (cw == 1200) & (ch == 800) ):
                self.lImg = camImg[0:600,0:800].copy()
                self.rImg = camImg[600:1200,0:800].copy()
                eyeImg = np.zeros((600,1600), np.uint8)
                eyeImg[0:600,0:800] = self.rImg.copy()
                eyeImg[0:600,800:1600] = self.lImg.copy()
                eyeImg = cv2.flip(eyeImg,1)

                qImg =  getPixmap(eyeImg)
#                self.parent.camScreen.setPixmap(qImg)
                self.data.emit(qImg)

                if( self.parent.position == 0):
                    frame = self.lImg
                else:
                    frame = self.rImg
                
                x,y,w,h =  self.parent.normalize.checkEyeImg(frame)
                if ( x != 0 ):
                   iImg = frame[y:y+h,x:x+w].copy()
                   height, width = iImg.shape
                   tImg =  getPixmap(iImg)
                   self.parent.irisScreen.setPixmap(tImg)

                  
            else:
                print("Invalid frame ",cw," ",ch)
            

            if ( self.parent.mStop == True ):
                print("Stop Called\n")
                break

            time.sleep(0.01)
#            self.modifyExposure(frame)

#        print("Timeout")
        self.cap.release()

        self.image = iImg.copy()

    def setImage(self,img):
        self.image = img.copy()

    def getLeft(self):
        x,y,w,h =  self.parent.normalize.checkEyeImg(self.lImg)
        iImg = self.lImg[y:y+h,x:x+w].copy()
        self.image = iImg.copy()
        return self.image

    def getRight(self):
        x,y,w,h =  self.parent.normalize.checkEyeImg(self.rImg)
        iImg = self.rImg[y:y+h,x:x+w].copy()
        self.image = iImg.copy()
        return self.image

    def getImage(self):
        return self.image

    def modifyExposure(self,frame):
        m1,m2,m3,m4 = cv2.mean(frame)
        exp = int(160 -  m1)
        exp = self.exp + exp
        if ( exp < 100 ):
            exp = 100
        if ( exp > 1000 ):
            exp = 1000

        if (abs( self.exp - exp )> 2) :
            self.exp = exp
            self.cap.set(cv2.CAP_PROP_EXPOSURE, self.exp)
#            print("Set Exposure ",self.exp)
