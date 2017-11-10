import re

class Zout:
    def __init__(self, aline):
        self.Str = aline
        self.Var = ''
        self.StN = ''
        self.ZN = ''
        self.ZName = ''
        self.Motion = ''
        self.Ztype = ''
        self.tozout(aline)

    def tozout(self, aline):
        """transform station statement to Cylinder Outputs struct"""
        # SetAusg(A120,5,A.St201_Y1_2_SwivelUnit_backward);
        #front|back|up|down|left|right
        pattern = re.compile(r'.*(?P<Var>A.*[sS]t(?P<StN>\d+)_Y(?P<ZN>\d+)_[24]_(?P<ZName>\w+)_'
                             r'(?P<Motion>open|close|forward|backward|up|upward|down|downward|left|leftward|right|rightward))\s*\).*')
        match = pattern.match(aline)
        if match:
            #print('match')
            self.Var = match.group('Var')
            self.StN = match.group('StN')
            self.ZN = match.group('ZN')
            self.ZName = match.group('ZName')
            self.Motion = match.group('Motion')
            # if re.compile(r'^up|down|left|right$').match(self.Motion):
            #    self.Motion = self.Motion+'ward'
            # obj = re.compile(r'up|down|left|right')
            # if obj.match(self.Motion):
            #     print('match')
            #     self.Motion = obj.subn('ward',self.Motion)[0]
            self.Motion = re.sub(r'^(up|down|left|right)$',r'\1ward', self.Motion)
            isgrippermatch = re.compile(r'.*(open|close).*').match(aline)
            if isgrippermatch:
                print('is gripper?')
                print(aline)
                self.Ztype = 'gripper'
                print(self.ZName)
            else:
                self.Ztype = 'not gripper'

    def display(self):
        print(self.Var)

class Zouts:
    def __init__(self):
        self.elements = []

    def search(self, StN, ZN, Motion):
        for elem in self.elements:
            # print('elem:')
            # print(str(type(elem.StN)) + str(type(StN)))
            # print(elem.StN + '->' + StN + ':' + str(elem.StN == StN))
            # print(elem.BN + '->' + BN + ':' + str(elem.BN == BN))
            # print(elem.Motion + '->' + ':' + str(elem.Motion == Motion))
            if elem.StN == StN and elem.ZN == ZN and elem.Motion == Motion:
                return elem
        return None

    def add(self, zout):
        self.elements.append(zout)

    def display(self):
        for elem in self.elements:
            print(elem.Var)