import sys
import threading
import maindesign
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5 import QtCore, QtGui, QtWidgets
from parser1 import *
import time
from matrix import *
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

def leftrotatemap(curstate):
    switcher = {
        'up': leftstate,
        'down': rightstate,
        'left': downstate,
        'right': upstate,
    }
    return switcher.get(curstate, None)

def rightrotatemap(curstate):
    switcher = {
        'up': rightstate,
        'down': leftstate,
        'left': upstate,
        'right': downstate,
    }
    return switcher.get(curstate, None)

def movemap(x):
    switcher = {
        'up': upmove,
        'down': downmove,
        'left': leftmove,
        'right': rightmove,
    }
    return switcher.get(x, None)


def leftstate():
    global sta
    ui.label.setPixmap(QtGui.QPixmap("res/left.png"))
    print('leftstate')
    sta = 'left'


def rightstate():
    global sta
    ui.label.setPixmap(QtGui.QPixmap("res/right.png"))
    print('rightstate')
    sta = 'right'


def downstate():
    global sta
    ui.label.setPixmap(QtGui.QPixmap("res/down.png"))
    print('downstate')
    sta = 'down'


def upstate():
    global sta
    ui.label.setPixmap(QtGui.QPixmap("res/up.png"))
    print('upstate')
    sta = 'up'


def upmove():
    global xpos,ypos
    ypos = ypos - 155
    mx.up()


def downmove():
    global xpos,ypos
    ypos = ypos + 155
    mx.down()

def leftmove():
    global xpos,ypos
    xpos = xpos - 150
    mx.left()

def rightmove():
    global xpos,ypos
    xpos = xpos + 150
    mx.right()

def leftturn():
    leftrotatemap(sta)()
    time.sleep(0.3)

def rightturn():
    rightrotatemap(sta)()
    time.sleep(0.3)

def forward():
    global xpos, ypos
    movemap(sta)()
    ui.label.setGeometry(QtCore.QRect(xpos, ypos, 181, 181))
    time.sleep(0.3)

def see(dir):
    print('see run')
    print(dir)
    # print(mx.see(dir))
    if sta == 'up':
        if dir == 'forward':
            return mx.checkobject('up')
        elif dir == 'backward':
            return mx.checkobject('down')
        elif dir == 'left':
            return mx.checkobject('left')
        elif dir == 'right':
            return mx.checkobject('right')
        else:
            print ('error direction input')
    elif sta == 'down':
        if dir == 'forward':
            return mx.checkobject('down')
        elif dir == 'backward':
            return mx.checkobject('up')
        elif dir == 'left':
            return mx.checkobject('right')
        elif dir == 'right':
            return mx.checkobject('left')
        else:
            print ('error direction input')

    elif sta == 'left':
        if dir == 'forward':
            return mx.checkobject('left')
        elif dir == 'backward':
            return mx.checkobject('right')
        elif dir == 'left':
            return mx.checkobject('down')
        elif dir == 'right':
            return mx.checkobject('up')
        else:
            print ('error direction input')

    elif sta == 'right':
        if dir == 'forward':
            return mx.checkobject('right')
        elif dir == 'backward':
            return mx.checkobject('left')
        elif dir == 'left':
            return mx.checkobject('up')
        elif dir == 'right':
            return mx.checkobject('down')
        else:
            print ('error direction input')

    else:
        print('error sta in see function')

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

