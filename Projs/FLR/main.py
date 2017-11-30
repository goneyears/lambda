import sys
import maindesign
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5 import QtCore, QtGui, QtWidgets
ui = maindesign.Ui_MainWindow()

sta = 'up'
i = 1
def rotatemap(x):
    switcher = {
        'up': uprotate,
        'down': downrotate,
        'left': leftrotate,
        'right': rightrotate,
    }
    return switcher.get(x, None)

def uprotate():
    global sta
    ui.label.setPixmap(QtGui.QPixmap("../../../../../Desktop/left.png"))
    sta = 'left'
    print(sta)

def downrotate():
    global sta
    ui.label.setPixmap(QtGui.QPixmap("../../../../../Desktop/right.png"))
    print('downrotate')
    sta = 'right'

def leftrotate():
    global sta
    ui.label.setPixmap(QtGui.QPixmap("../../../../../Desktop/down.png"))
    print('leftrotate')
    sta = 'down'

def rightrotate():
    global sta
    ui.label.setPixmap(QtGui.QPixmap("../../../../../Desktop/up.png"))
    print('rightrotate')
    sta = 'up'

def F_button_click():
    print(sta)
    ui.label.setPixmap(QtGui.QPixmap("../../../../../Desktop/polygon.png"))

def L_button_click():
    global sta
    print(sta)
    rotatemap(sta)
    print(i)

def R_button_click():
    rotatemap(sta)
    rotatemap(sta)
    rotatemap(sta)


if __name__ =='__main__':
    app = QApplication(sys.argv)
    MainWindow = QMainWindow()
    #ui = maindesign.Ui_MainWindow()
    ui.setupUi(MainWindow)
    ui.FButton.clicked.connect(F_button_click)
    ui.LButton.clicked.connect(L_button_click)
    ui.RButton.clicked.connect(R_button_click)
    MainWindow.show()
    sys.exit(app.exec_())