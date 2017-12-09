import sys
import threading
import maindesign
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5 import QtCore, QtGui, QtWidgets
from parser1 import *
import time

ui = maindesign.Ui_MainWindow()
editstr = ''

brun = 0

def read_edit():
    return str(ui.textEdit.toPlainText())


def write_edit(str):
    global editstr
    editstr=editstr + str
    ui.textEdit.setText(editstr)

def clear_edit():
    ui.textEdit.setText('')

def backspace_edit():
    global editstr
    editstr = editstr[0:len(editstr)-1]
    ui.textEdit.setText(editstr)

sta = 'up'
xpos = 50
ypos = 670

def rotatemap(x):
    switcher = {
        'up': uprotate,
        'down': downrotate,
        'left': leftrotate,
        'right': rightrotate,
    }
    return switcher.get(x, None)

def movemap(x):
    switcher = {
        'up': upmove,
        'down': downmove,
        'left': leftmove,
        'right': rightmove,
    }
    return switcher.get(x, None)


def uprotate():
    global sta
    ui.label.setPixmap(QtGui.QPixmap("res/left.png"))
    sta = 'left'


def downrotate():
    global sta
    ui.label.setPixmap(QtGui.QPixmap("res/right.png"))
    print('downrotate')
    sta = 'right'


def leftrotate():
    global sta
    ui.label.setPixmap(QtGui.QPixmap("res/down.png"))
    print('leftrotate')
    sta = 'down'


def rightrotate():
    global sta
    ui.label.setPixmap(QtGui.QPixmap("res/up.png"))
    print('rightrotate')
    sta = 'up'


def upmove():
    global xpos,ypos
    ypos = ypos - 155


def downmove():
    global xpos,ypos
    ypos = ypos + 155


def leftmove():
    global xpos,ypos
    xpos = xpos - 150


def rightmove():
    global xpos,ypos
    xpos = xpos + 150

def leftturn():
    rotatemap(sta)()
    time.sleep(0.3)

def rightturn():
    rotatemap(sta)()
    time.sleep(0.1)
    rotatemap(sta)()
    time.sleep(0.1)
    rotatemap(sta)()
    time.sleep(0.3)

def forward():
    global xpos, ypos
    movemap(sta)()
    ui.label.setGeometry(QtCore.QRect(xpos, ypos, 181, 181))

def see(x):
    print('see run')
    if x=='left':
        return True
    else:
        return False


def F_button_click():
    write_edit('F')

def L_button_click():
    write_edit('L')

def R_button_click():
    write_edit('R')

def LBracket_button_click():
    write_edit('(')

def RBracket_button_click():
    write_edit(')')

def N1_button_click():
    write_edit('1')

def N2_button_click():
    write_edit('2')

def N3_button_click():
    write_edit('3')

def N4_button_click():
    write_edit('4')

def N5_button_click():
    write_edit('5')

def Backspace_button_click():
    backspace_edit()

def Run_button_click():
    global brun
    brun = 1
    print('brun'+str(brun))


def thread1():
    global brun,global_env
    print('thread runs'+str(brun))
    while(True):
        try:
            if brun == 1:
                brun = 0
                global_env = standard_env()
                mstr = read_edit().strip('\r\n')
                mstr_lines = re.split('\n', mstr)
                for ln in mstr_lines:
                    repl(ln)
        except:
            print('code syntax error')
        time.sleep(0.1)


if __name__ =='__main__':
    app = QApplication(sys.argv)
    MainWindow = QMainWindow()
    #ui = maindesign.Ui_MainWindow()
    ui.setupUi(MainWindow)
    ui.FButton.clicked.connect(F_button_click)
    ui.LButton.clicked.connect(L_button_click)
    ui.RButton.clicked.connect(R_button_click)
    ui.LBracketButton.clicked.connect(LBracket_button_click)
    ui.RBracketButton.clicked.connect(RBracket_button_click)
    ui.BackspaceButton.clicked.connect(Backspace_button_click)
    ui.RunButton.clicked.connect(Run_button_click)
    ui.N1Button.clicked.connect(N1_button_click)
    ui.N2Button.clicked.connect(N2_button_click)
    ui.N3Button.clicked.connect(N3_button_click)
    ui.N4Button.clicked.connect(N4_button_click)
    ui.N5Button.clicked.connect(N5_button_click)

    #append function to exes in parser1.py
    exes.Fevent.append(forward)
    exes.Levent.append(leftturn)
    exes.Revent.append(rightturn)
    exes.Sevent.append(see)

    MainWindow.show()

    t1 = threading.Thread(target=thread1)
    t1.setDaemon(True)
    t1.start()


    sys.exit(app.exec_())

