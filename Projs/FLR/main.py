import sys
import threading
import maindesign
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5 import QtCore, QtGui, QtWidgets
from parser1 import *
import time
from matrix import *

ui = maindesign.Ui_MainWindow()
brun = 0
lbls = []
def read_edit():
    return str(ui.textEdit.toPlainText())


def write_edit(str):
    c = ui.textEdit.textCursor()
    c.insertText(str)
    ui.textEdit.setFocus()

def clear_edit():
    ui.textEdit.clear()
    ui.textEdit.setFocus()

def backspace_edit():
    c = ui.textEdit.textCursor()
    c.deletePreviousChar()
    ui.textEdit.setFocus()

sta = 'up'
xpos = 0
ypos = 0
xgap = 0
ygap =0
planegeo = QtCore.QRect(0,0,0,0)
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
    ui.aeroplane_label.setPixmap(QtGui.QPixmap("res/left.png"))
    print('leftstate')
    sta = 'left'


def rightstate():
    global sta
    ui.aeroplane_label.setPixmap(QtGui.QPixmap("res/right.png"))
    print('rightstate')
    sta = 'right'


def downstate():
    global sta
    ui.aeroplane_label.setPixmap(QtGui.QPixmap("res/down.png"))
    print('downstate')
    sta = 'down'


def upstate():
    global sta
    ui.aeroplane_label.setPixmap(QtGui.QPixmap("res/up.png"))
    print('upstate')
    sta = 'up'


def upmove():
    global xpos,ypos
    ypos = ypos - ygap

    mx.up()


def downmove():
    global xpos,ypos
    ypos = ypos + ygap
    mx.down()

def leftmove():
    global xpos,ypos
    xpos = xpos - xgap
    mx.left()

def rightmove():
    global xpos,ypos
    xpos = xpos + xgap
    mx.right()

def leftturn():

    ui.aeroplane_label.hide()
    leftrotatemap(sta)()
    ui.aeroplane_label.show()
    updategeo()

def rightturn():
    rightrotatemap(sta)()
    updategeo()

def forward():
    global xpos,ypos
    global planegeo
    movemap(sta)()
    updategeo()

def updategeo():
    global xpos,ypos
    global planegeo
    time.sleep(0.0001)
    planegeo.moveTopLeft(QtCore.QPoint(xpos,ypos))
    print('planegeo movetopleft:'+str(planegeo))
    ui.aeroplane_label.setGeometry(planegeo)
    time.sleep(0.3)

def see(dir):
    print('see run')
    print(dir)
    print(sta)
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

def isrun():
    print('isrun?' + str(brun))
    return True if brun == 1 else False

def F_button_click():
    write_edit('F')

def L_button_click():
    write_edit('L')

def R_button_click():
    write_edit('R')

def B_button_click():
    write_edit('B')

def N_button_click():
    write_edit('N')

def S_button_click():
    write_edit('S')

def U_button_click():
    write_edit('U')

def Equal_button_click():
    write_edit('=')

def LBracket_button_click():
    write_edit('(')

def RBracket_button_click():
    write_edit(')')

def LMBracket_button_click():
    write_edit('[')

def RMBracket_button_click():
    write_edit(']')

def If_button_click():
    write_edit('IF')

def Else_button_click():
    write_edit('ELSE')

def While_button_click():
    write_edit('WHILE')

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

def Newline_button_click():
    write_edit('\n')

def Backspace_button_click():
    backspace_edit()

t = QtCore.QTimer()
t.timeout.connect(clear_edit)
def Clear_button_press():
    print('clear press')
    t.start(2000)

def Clear_button_release():
    print('clear release')
    t.stop()

def Run_button_click():
    global brun
    brun = 1
    print('brun'+str(brun))

def Stop_button_click():
    global brun
    brun = 0
    print('brun'+str(brun))


def thread1():
    global brun,global_env
    print('thread runs'+str(brun))
    while(True):
        try:
            if brun == 1:
                global_env = standard_env()
                mstr = read_edit().strip('\r\n')
                mstr_lines = re.split('\n', mstr)
                for ln in mstr_lines:
                    repl(ln)
                brun = 0
        except:
            print('code syntax error')
        time.sleep(0.1)

bresize = 0
def threadresize():
    global bresize
    while(True):
        # try:
        if bresize == 1:
            bresize = 0
            time.sleep(0.5)
            if bresize == 0:
                uiinitial()

        time.sleep(0.5)
def uiinitial():
    global planegeo
    global xgap, ygap
    global xpos, ypos
    global lbls
    planegeo = ui.label15.geometry()
    xpos = planegeo.left()
    ypos = planegeo.top()
    xgap = planegeo.width()
    ygap = planegeo.height()
    ui.aeroplane_label.setPixmap(QtGui.QPixmap("res/up.png"))
    time.sleep(0.6)
    ui.aeroplane_label.setPixmap(QtGui.QPixmap("res/left.png"))
    time.sleep(0.3)
    ui.aeroplane_label.setPixmap(QtGui.QPixmap("res/down.png"))
    time.sleep(0.3)
    ui.aeroplane_label.setPixmap(QtGui.QPixmap("res/right.png"))
    time.sleep(0.3)
    ui.aeroplane_label.setPixmap(QtGui.QPixmap("res/up.png"))
    time.sleep(0.3)
    ui.aeroplane_label.setGeometry(planegeo)

    lbls[mx.curpos[0]][mx.curpos[1]].setPixmap(QtGui.QPixmap("res/up.png"))
    print('planegeo initial:'+str(planegeo))

class nQMainWindow(QMainWindow):

    def resizeEvent(self, a0: QtGui.QResizeEvent):
        global bresize
        bresize = 1
        print('resize')


if __name__ =='__main__':
    app = QApplication(sys.argv)
    MainWindow = nQMainWindow()
    #ui = maindesign.Ui_MainWindow()
    ui.setupUi(MainWindow)

    lbls = [

        [None, None, None, None, None, None, None],
        [None, ui.label11, ui.label21, ui.label31, ui.label41, ui.label51, None],
        [None, ui.label12, ui.label22, ui.label32, ui.label42, ui.label52, None],
        [None, ui.label13, ui.label23, ui.label33, ui.label43, ui.label53, None],
        [None, ui.label14, ui.label24, ui.label34, ui.label44, ui.label54, None],
        [None, ui.label15, ui.label25, ui.label35, ui.label45, ui.label55, None],
        [None, None, None, None, None, None, None],
    ]

    ui.FButton.clicked.connect(F_button_click)
    ui.LButton.clicked.connect(L_button_click)
    ui.RButton.clicked.connect(R_button_click)
    ui.BButton.clicked.connect(B_button_click)
    ui.NButton.clicked.connect(N_button_click)
    ui.SButton.clicked.connect(S_button_click)
    ui.UButton.clicked.connect(U_button_click)
    ui.EqualButton.clicked.connect(Equal_button_click)
    ui.LBracketButton.clicked.connect(LBracket_button_click)
    ui.RBracketButton.clicked.connect(RBracket_button_click)
    ui.LMBracketButton.clicked.connect(LMBracket_button_click)
    ui.RMBracketButton.clicked.connect(RMBracket_button_click)
    ui.IfButton.clicked.connect(If_button_click)
    ui.ElseButton.clicked.connect(Else_button_click)
    ui.WhileButton.clicked.connect(While_button_click)

    ui.NewlineButton.clicked.connect(Newline_button_click)

    ui.BackspaceButton.clicked.connect(Backspace_button_click)
    ui.BackspaceButton.pressed.connect(Clear_button_press)
    ui.BackspaceButton.released.connect(Clear_button_release)

    ui.RunButton.clicked.connect(Run_button_click)
    ui.StopButton.clicked.connect(Stop_button_click)
    ui.N1Button.clicked.connect(N1_button_click)
    ui.N2Button.clicked.connect(N2_button_click)
    ui.N3Button.clicked.connect(N3_button_click)
    ui.N4Button.clicked.connect(N4_button_click)
    ui.N5Button.clicked.connect(N5_button_click)


    #temporary test adapt for low resolution screen
    #compoinit()
    #append function to exes in parser1.py
    exes.Fevent.append(forward)
    exes.Levent.append(leftturn)
    exes.Revent.append(rightturn)
    exes.Sevent.append(see)
    exes.Runevent.append(isrun)


    MainWindow.show()
    t1 = threading.Thread(target=thread1)
    t1.setDaemon(True)
    t1.start()

    #this thread used to check window resizing
    t2 = threading.Thread(target=threadresize)
    t2.setDaemon(True)
    t2.start()
    sys.exit(app.exec_())

