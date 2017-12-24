class Block:
    def __init__(self, x, y, t='normal'):
        self.position = [x, y]
        self.tp = t

class Matrix:
    def __init__(self):
        self.blocks = [
            [Block(0,0,'upleftcorner'),   Block(1,0,'upwall'),   Block(2,0,'upwall'),   Block(3,0,'upwall'),   Block(4,0,'upwall'),   Block(5,0,'upwall'),   Block(6,0,'uprightcorner')],
            [Block(0,1,'leftwall'),       Block(1,1),            Block(2,1),            Block(3,1),            Block(4,1),            Block(5,1),            Block(6,1,'rightwall')],
            [Block(0,2,'leftwall'),       Block(1,2),            Block(2,2),            Block(3,2),            Block(4,2),            Block(5,2),            Block(6,2,'rightwall')],
            [Block(0,3,'leftwall'),       Block(1,3),            Block(2,3),            Block(3,3),            Block(4,3),            Block(5,3),            Block(6,3,'rightwall')],
            [Block(0,4,'leftwall'),       Block(1,4),            Block(2,4),            Block(3,4),            Block(4,4),            Block(5,4),            Block(6,4,'rightwall')],
            [Block(0,5,'leftwall'),       Block(1,5),            Block(2,5),            Block(3,5),            Block(4,5),            Block(5,5),            Block(6,5,'rightwall')],
            [Block(0,6,'downleftcorner'), Block(1,6,'downwall'), Block(2,6,'downwall'), Block(3,6,'downwall'), Block(4,6,'downwall'), Block(5,6,'downwall'), Block(6,6,'downrightcorner')],
        ]
        self.lastpos = [1, 5]
        self.curpos = [1,5]

    def xinc(self):
        self.curpos[0] = self.curpos[0] + 1
    def xdec(self):
        self.curpos[0] = self.curpos[0] - 1
    def yinc(self):
        self.curpos[1] = self.curpos[1] + 1
    def ydec(self):
        self.curpos[1] = self.curpos[1] - 1

    def up(self):
        self.lastpos[0] = self.curpos[0]
        self.lastpos[1] = self.curpos[1]
        self.ydec()

    def down(self):
        self.lastpos[0] = self.curpos[0]
        self.lastpos[1] = self.curpos[1]
        self.yinc()

    def right(self):
        self.lastpos[0] = self.curpos[0]
        self.lastpos[1] = self.curpos[1]
        self.xinc()

    def left(self):
        self.lastpos[0] = self.curpos[0]
        self.lastpos[1] = self.curpos[1]
        self.xdec()

    def getcurblock(self):
        return self.blocks[self.curpos[0],self.curpos[1]]

    def getcurpos(self):
        return self.curpos

    def iswall(self,pos):
        if self.blocks[pos[0]][pos[1]].tp != 'normal':
            return True
        return False

    def checkobject(self,d):
        if d == 'left':
            p = [self.curpos[0] - 1,self.curpos[1]]

        elif d == 'right':
            p = [self.curpos[0] + 1,self.curpos[1]]

        elif d == 'up':
            p = [self.curpos[0]    ,self.curpos[1] - 1]

        elif d == 'down':
            p = [self.curpos[0]    ,self.curpos[1] + 1]

        else:
            print('see parameter error')
            return None;


        return self.iswall(p)
        # return False



mx = Matrix()
# mx.up()
# mx.right()
# mx.right()
print(mx.getcurpos())
print(mx.checkobject('right'))