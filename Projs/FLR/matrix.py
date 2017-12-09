class Block:
    def __init__(self, x, y, t='normal'):
        self.position = [x, y]
        self.tp = t

class Matrix:
    def __init__(self):
        self.blocks = [
            [Block(0,0,'upleftcorner'),   Block(0,1,'upwall'),   Block(0,2,'upwall'),   Block(0,3,'upwall'),   Block(0,4,'uprightcorner')],
            [Block(1,0,'leftwall'),       Block(1,1),            Block(1,2),            Block(1,3),            Block(1,4,'rightwall')],
            [Block(2,0,'leftwall'),       Block(2,1),            Block(2,2),            Block(2,3),            Block(2,4,'rightwall')],
            [Block(3,0,'leftwall'),       Block(3,1),            Block(3,2),            Block(3,3),            Block(3,4,'rightwall')],
            [Block(4,0,'downleftcorner'), Block(4,1,'downwall'), Block(4,2,'downwall'), Block(4,3,'downwall'), Block(4,4,'downrightcorner')],
        ]
        self.curpos = [0,4]

    def xinc(self):
        self.curpos[0] = self.curpos[0] + 1
    def xdec(self):
        self.curpos[0] = self.curpos[0] - 1
    def yinc(self):
        self.curpos[1] = self.curpos[1] + 1
    def ydec(self):
        self.curpos[1] = self.curpos[1] - 1

    def up(self):
        self.ydec()

    def down(self):
        self.yinc()

    def right(self):
        self.xinc()

    def left(self):
        self.xdec()

    def getcurblock(self):
        return self.blocks[self.curpos[0],self.curpos[1]]

    def getcurpos(self):
        return self.curpos

    def iswall(self,pos):
        if self.blocks[pos[0]][pos[1]].tp != 'normal':
            return True
        return False

    def see(self,d):
        # if d=='left':
        p = [self.curpos[0] - 1,self.curpos[1]]
        return self.iswall(p)
        # return False



mx = Matrix()
mx.up()
mx.right()
mx.right()
print(mx.getcurpos())
print(mx.see('left'))