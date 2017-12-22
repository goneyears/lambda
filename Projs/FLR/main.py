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
xpos = 60
ypos = 640

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
    ui.aeroplane_label.setGeometry(QtCore.QRect(xpos, ypos, 181, 181))
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

def Clear_button_click():
    clear_edit()

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

class Rect:
    def __init__(self, posx, posy, width, height):
        self.x = posx
        self.y = posy
        self.w = width
        self.h = height
        self.rect = QtCore.QRect(self.x, self.y, self.w, self.h)

def compoinit():

    aeroplane = Rect(60, 640, 100, 100)

    label11 = Rect(50, 30, 150, 150)
    label12 = Rect(50, 180, 150, 150)
    label13 = Rect(50, 330, 150, 150)
    label14 = Rect(50, 480, 150, 150)
    label15 = Rect(50, 630, 150, 150)

    label21 = Rect(200, 30, 150, 150)
    label22 = Rect(200, 180, 150, 150)
    label23 = Rect(200, 330, 150, 150)
    label24 = Rect(200, 480, 150, 150)
    label25 = Rect(200, 630, 150, 150)

    label31 = Rect(350, 30, 150, 150)
    label32 = Rect(350, 180, 150, 150)
    label33 = Rect(350, 330, 150, 150)
    label34 = Rect(350, 480, 150, 150)
    label35 = Rect(350, 630, 150, 150)

    label41 = Rect(500, 30, 150, 150)
    label42 = Rect(500, 180, 150, 150)
    label43 = Rect(500, 330, 150, 150)
    label44 = Rect(500, 480, 150, 150)
    label45 = Rect(500, 630, 150, 150)

    label51 = Rect(650, 30, 150, 150)
    label52 = Rect(650, 180, 150, 150)
    label53 = Rect(650, 330, 150, 150)
    label54 = Rect(650, 480, 150, 150)
    label55 = Rect(650, 630, 150, 150)

    ClearButton = Rect(60, 880, 131, 111)

    textEdit = Rect(910, 30, 1121, 821)

    N1Button = Rect(910, 890, 131, 111)
    N2Button = Rect(1050, 890, 131, 111)
    N3Button = Rect(1190, 890, 131, 111)
    N5Button = Rect(1470, 890, 131, 111)
    N4Button = Rect(1330, 890, 131, 111)
    BackspaceButton = Rect(1610, 890, 131, 111)
    NewlineButton = Rect(1850, 890, 131, 111)

    FButton = Rect(910, 1030, 131, 111)

    LButton = Rect(1050, 1030, 131, 111)
    RButton = Rect(1190, 1030, 131, 111)
    BButton = Rect(1330, 1030, 131, 111)
    LBracketButton = Rect(1470, 1030, 131, 111)
    RBracketButton = Rect(1610, 1030, 131, 111)
    RunButton = Rect(1850, 1030, 131, 111)

    NButton = Rect(910, 1160, 131, 111)
    SButton = Rect(1050, 1160, 131, 111)
    UButton = Rect(1190, 1160, 131, 111)
    EqualButton = Rect(1330, 1160, 131, 111)
    RMBracketButton = Rect(1610, 1160, 131, 111)
    LMBracketButton = Rect(1470, 1160, 131, 111)
    StopButton = Rect(1850, 1160, 131, 111)

    IfButton = Rect(910, 1280, 131, 111)
    WhileButton = Rect(1260, 1280, 201, 111)
    ElseButton = Rect(1050, 1280, 201, 111)

    menubar = Rect(0, 0, 2053, 38)

    ui.aeroplane_label.setGeometry(aeroplane.rect)

    ui.label11.setGeometry(label11.rect)
    ui.label12.setGeometry(label12.rect)
    ui.label13.setGeometry(label13.rect)
    ui.label14.setGeometry(label14.rect)
    ui.label15.setGeometry(label15.rect)

    ui.label21.setGeometry(label21.rect)
    ui.label22.setGeometry(label22.rect)
    ui.label23.setGeometry(label23.rect)
    ui.label24.setGeometry(label24.rect)
    ui.label25.setGeometry(label25.rect)

    ui.label31.setGeometry(label31.rect)
    ui.label32.setGeometry(label32.rect)
    ui.label33.setGeometry(label33.rect)
    ui.label34.setGeometry(label34.rect)
    ui.label35.setGeometry(label35.rect)

    ui.label41.setGeometry(label41.rect)
    ui.label42.setGeometry(label42.rect)
    ui.label43.setGeometry(label43.rect)
    ui.label44.setGeometry(label44.rect)
    ui.label45.setGeometry(label45.rect)

    ui.label51.setGeometry(label51.rect)
    ui.label52.setGeometry(label52.rect)
    ui.label53.setGeometry(label53.rect)
    ui.label54.setGeometry(label54.rect)
    ui.label55.setGeometry(label55.rect)

    ui.ClearButton.setGeometry(ClearButton.rect)

    ui.textEdit.setGeometry(textEdit.rect)

    ui.N1Button.setGeometry(N1Button.rect)
    ui.N2Button.setGeometry(N2Button.rect)
    ui.N3Button.setGeometry(N3Button.rect)
    ui.N5Button.setGeometry(N5Button.rect)
    ui.N4Button.setGeometry(N4Button.rect)
    ui.BackspaceButton.setGeometry(BackspaceButton.rect)
    ui.NewlineButton.setGeometry(NewlineButton.rect)

    ui.FButton.setGeometry(FButton.rect)

    ui.LButton.setGeometry(LButton.rect)
    ui.RButton.setGeometry(RButton.rect)
    ui.BButton.setGeometry(BButton.rect)
    ui.LBracketButton.setGeometry(LBracketButton.rect)
    ui.RBracketButton.setGeometry(RBracketButton.rect)
    ui.RunButton.setGeometry(RunButton.rect)

    ui.NButton.setGeometry(NButton.rect)
    ui.SButton.setGeometry(SButton.rect)
    ui.UButton.setGeometry(UButton.rect)
    ui.EqualButton.setGeometry(EqualButton.rect)
    ui.RMBracketButton.setGeometry(RMBracketButton.rect)
    ui.LMBracketButton.setGeometry(LMBracketButton.rect)
    ui.StopButton.setGeometry(StopButton.rect)

    ui.IfButton.setGeometry(IfButton.rect)
    ui.WhileButton.setGeometry(WhileButton.rect)
    ui.ElseButton.setGeometry(ElseButton.rect)

    ui.menubar.setGeometry(menubar.rect)

if __name__ =='__main__':
    app = QApplication(sys.argv)
    MainWindow = QMainWindow()
    #ui = maindesign.Ui_MainWindow()
    ui.setupUi(MainWindow)


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


    ui.BackspaceButton.clicked.connect(Backspace_button_click)
    ui.NewlineButton.clicked.connect(Newline_button_click)

    ui.ClearButton.clicked.connect(Clear_button_click)
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


    sys.exit(app.exec_())

