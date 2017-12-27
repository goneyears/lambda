from PyQt5 import QtCore, QtGui, QtWidgets


class Position:
    def __init__(self, xpos, ypos):
        self.x = xpos
        self.y = ypos

class Block:
    def __init__(self, x, y, lbl, t='normal'):
        self.location = Position(x, y)
        self.tp = t
        self.lbl = lbl
    def dispic(self,picpath):
        self.lbl.setPixmap(QtGui.QPixmap(picpath))
    def geometry(self):
        return self.lbl.geometry()

class Matrix:
    def __init__(self, blks):
        # self.blocks = []
        self.blocks = list(map(list, zip(*blks)))
        self.lastpos = Position(1, 5)
        self.curpos = Position(1, 5)
        self.lastblk = self.blocks[self.lastpos.x][self.lastpos.y]
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
        self.lastblk = self.blocks[self.lastpos.x][self.lastpos.y]
        self.ydec()
        self.curblock = self.blocks[self.curpos.x][self.curpos.y]


    def down(self):
        self.lastpos.x = self.curpos.x
        self.lastpos.y = self.curpos.y
        self.lastblk = self.blocks[self.lastpos.x][self.lastpos.y]
        self.yinc()
        self.curblock = self.blocks[self.curpos.x][self.curpos.y]

    def right(self):
        self.lastpos.x = self.curpos.x
        self.lastpos.y = self.curpos.y
        self.lastblk = self.blocks[self.lastpos.x][self.lastpos.y]
        self.xinc()
        self.curblock = self.blocks[self.curpos.x][self.curpos.y]

    def left(self):
        self.lastpos.x = self.curpos.x
        self.lastpos.y = self.curpos.y
        self.lastblk = self.blocks[self.lastpos.x][self.lastpos.y]
        self.xdec()
        self.curblock = self.blocks[self.curpos.x][self.curpos.y]

    # def getcurblock(self):
    #     return self.blocks[self.curpos.x,self.curpos.y]
    #
    # def getcurpos(self):
    #     return self.curpos

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
        # return False



