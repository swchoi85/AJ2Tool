import sys
import os
from PyQt5 import uic
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *

form_class = uic.loadUiType("./resource/alkaid.ui")[0]

import cam
import cv2
import numpy as np

import platform

is_x86 = platform.machine() in ("i386", "AMD64", "x86_64")
if ( is_x86 == True) :
    import aj2lib
else :
    import aj2lib
#    import aj2lib_arm64

class MainClass(QMainWindow, form_class):

    def btnStart_clicked(self):
        self.mStop = False
        img = self.camThread.getEmpty()
        pimg = cam.getPixmap(img)
        self.irisScreen.setPixmap(pimg)
        self.normalizeScreen.setPixmap(pimg)
        self.camThread.start()

    def btnOpen_clicked(self):
        fname = QFileDialog.getOpenFileName(self, 'Open file', './',"Files(*.png *.jpg)")
        if fname[0]:
          img = self.camThread.getEmpty()
          pimg = cam.getPixmap(img)
          self.camScreen.setPixmap(pimg)
          self.normalizeScreen.setPixmap(pimg)
          print("Open : ",fname[0])

          img = cv2.imread(fname[0])
          img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
          self.camThread.setImage(img)
          pimg = cam.getPixmap(img)
          self.irisScreen.setPixmap(pimg)
        else:
          print("Open : Cancel")

    def btnSave_clicked(self):
        path = QFileDialog.getSaveFileName(self, 'Save file', './',"Images (*.png *.jpg)")
        fname,file_ext = os.path.splitext(path[0])
        if fname:
          if ( len(file_ext) == 0 ) :
                fname += ".png"
          else :
                fname = path[0]
          print("Save : ",fname)
          img = self.camThread.getImage()
          w,h = img.shape
          if ( w != 0):
              cv2.imwrite(fname,img)
        else:
          print("Save : Cancel")

    def btnStop_clicked(self):
        self.mStop = True

    def btnEnroll_clicked(self):
        print("Enroll")

    def btnIdentify_clicked(self):
        print("Identify")
        img = self.camThread.getImage()
        #//print(img.shape)
        h,w = img.shape
        if ( w == 0 ):
            print("No Image ")
            return

        #pimg = cam.getPixmapGray(img)
        #self.irisScreen.setPixmap(pimg)

        nor = self.normalize
        nImg = nor.process(img)
        pimg = cam.getPixmap(nImg)
        self.normalizeScreen.setPixmap(pimg)
        aa = nor.getCircle()
        x,y,r1,r2,sharp = aa
        self.lineEdit_3.setText(str(sharp))
        #print(aa)
        #print("x y r1 r2 ",x,y,r1,r2)
        if ( x != 0 ):
            img = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
            cv2.circle(img,(x,y),r1,(255,255,0),2)
            cv2.circle(img,(x,y),r2,(0,255,0),2)
            pimg = cam.getPixmap(img)
            self.irisScreen.setPixmap(pimg)

        #print(nImg.shape)

    def btnLeft_clicked(self):
        self.position = 0
        img = self.camThread.getLeft()
        pimg = cam.getPixmap(img)
        self.irisScreen.setPixmap(pimg)
        self.normalizeScreen.setPixmap(self.emptyPimg)

    def btnRight_clicked(self):
        self.position = 1
        img = self.camThread.getRight()
        pimg = cam.getPixmap(img)
        self.irisScreen.setPixmap(pimg)
        self.normalizeScreen.setPixmap(self.emptyPimg)

    @pyqtSlot(QPixmap)
    def showImg(self,img):
        self.camScreen.setPixmap(img)

    def __init__(self):
        QMainWindow.__init__(self)
        # 연결한 Ui를 준비한다.
        self.setupUi(self)
        self.buttonStart.clicked.connect(self.btnStart_clicked)
        self.buttonStop.clicked.connect(self.btnStop_clicked)
        self.buttonEnroll.clicked.connect(self.btnEnroll_clicked)
        self.buttonIdentify.clicked.connect(self.btnIdentify_clicked)
        self.buttonOpen.clicked.connect(self.btnOpen_clicked)
        self.buttonSave.clicked.connect(self.btnSave_clicked)
        self.buttonLeft.clicked.connect(self.btnLeft_clicked)
        self.buttonRight.clicked.connect(self.btnRight_clicked)
        self.position = 0

        self.irisScreen.setScaledContents(True);
        self.camScreen.setScaledContents(True);
        self.normalizeScreen.setScaledContents(True);
        # 화면을 보여준다.
        self.show()

        #Camera Handling Thread
        self.camThread = cam.Thread1(self)
        self.mStop = False
        self.normalize = aj2lib.normalize()
        self.empty = np.zeros((0,0), np.uint8)
        self.emptyPimg = cam.getPixmap(self.empty)

        self.camThread.data.connect(self.showImg)




if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainClass()
    app.exec_()
