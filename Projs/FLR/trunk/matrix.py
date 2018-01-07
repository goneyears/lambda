from PyQt5 import QtCore, QtGui, QtWidgets


class Position:
    def __init__(self, xpos, ypos):
        self.x = xpos
        self.y = ypos

class Objs:
    def __init__(self):
        self.item = []

    def addelement(self, objs):
        self.item = objs.copy()
        self.item.insert(0, None)


class Obj:
    def __init__(self, obj):
        self.obj = obj
        self.leftstart = self.obj.geometry().left()
        self.topstart = self.obj.geometry().top()


    def move(self, left, top):
        self.obj.move(left, top)

    def back(self):
        self.obj.move(self.leftstart, self.topstart)

    def geometry(self):
        return self.obj.geometry()

class Block:
    def __init__(self, x, y, lbl, obj, t='normal'):
        self.location = Position(x, y)
        self.tp = t
        self.lbl = lbl
        self.poss = []
        self.curpos = 0
        if(lbl != None):
            self.curavailtop = self.lbl.geometry().top()
            self.curavailleft = self.lbl.geometry().left()
            self.calcobjspos(obj)
            print('lblgeometry  : ' + str(self.geometry()))
            print(self.poss)
        else:
            self.curavailtop = 0
            self.curavailleft = 0

    def dispic(self,picpath):
        self.lbl.setPixmap(QtGui.QPixmap(picpath))

    def geometry(self):
        return self.lbl.geometry()

    def calcobjspos(self, obj):
        geo = QtCore.QRect(self.geometry().left(), self.geometry().top(), obj.geometry().width(), obj.geometry().height())
        while True:
            self.poss.append(geo)

            if geo.right() + geo.width() <= self.geometry().right():
                geo = QtCore.QRect(geo.right(), geo.top(), geo.width(), geo.height())
            elif geo.bottom() + geo.height() <= self.geometry().bottom():
                geo = QtCore.QRect(self.geometry().left(), geo.bottom(), geo.width(),geo.height())
            else:
                break;


    def getobj(self, obj):
        obj.move(self.poss[self.curpos].left(), self.poss[self.curpos].top())
        self.curpos += 1

    def releaseobj(self, obj):
        obj.back()
        self.curpos -= 1


class Matrix:
    def __init__(self, blks):
        self.blocks = list(map(list, zip(*blks))) #T transform to block array
        self.lastpos = Position(1, 5)
        self.curpos = Position(1, 5)
        self.lastblock = self.blocks[self.lastpos.x][self.lastpos.y]
        self.curblock = self.blocks[self.curpos.x][self.curpos.y]

    def xinc(self):
        self.curpos.x = self.curpos.x + 1
    def xdec(self):
        self.curpos.x = self.curpos.x - 1
    def yinc(self):
        self.curpos.y = self.curpos.y + 1
    def ydec(self):
        self.curpos.y = self.curpos.y - 1

    def up(self):
        self.lastpos.x = self.curpos.x
        self.lastpos.y = self.curpos.y
        self.lastblock = self.blocks[self.lastpos.x][self.lastpos.y]
        self.ydec()
        self.curblock = self.blocks[self.curpos.x][self.curpos.y]


    def down(self):
        self.lastpos.x = self.curpos.x
        self.lastpos.y = self.curpos.y
        self.lastblock = self.blocks[self.lastpos.x][self.lastpos.y]
        self.yinc()
        self.curblock = self.blocks[self.curpos.x][self.curpos.y]

    def right(self):
        self.lastpos.x = self.curpos.x
        self.lastpos.y = self.curpos.y
        self.lastblock = self.blocks[self.lastpos.x][self.lastpos.y]
        self.xinc()
        self.curblock = self.blocks[self.curpos.x][self.curpos.y]

    def left(self):
        self.lastpos.x = self.curpos.x
        self.lastpos.y = self.curpos.y
        self.lastblock = self.blocks[self.lastpos.x][self.lastpos.y]
        self.xdec()
        self.curblock = self.blocks[self.curpos.x][self.curpos.y]


    def iswall(self,pos):
        if self.blocks[pos.x][pos.y].tp != 'normal':
            return True
        return False

    def checkobject(self,d):
        p = Position(0,0)
        if d == 'left':
            (p.x, p.y) = (self.curpos.x - 1,self.curpos.y)

        elif d == 'right':
            (p.x, p.y) = (self.curpos.x + 1,self.curpos.y)

        elif d == 'up':
            (p.x, p.y) = (self.curpos.x    ,self.curpos.y - 1)

        elif d == 'down':
            (p.x, p.y) = (self.curpos.x    ,self.curpos.y + 1)

        else:
            print('see parameter error')
            return None;


        return self.iswall(p)





