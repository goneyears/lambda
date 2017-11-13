import re


class ZBin:
    def __init__(self,eline):
        self.Str = eline
        self.Var = ''
        self.StN = ''
        self.BN = ''
        self.BName = ''
        self.Motion = ''
        self.tozin(eline)

    def tozin(self,eline):
        """transform station statement to Inputs struct"""
        # "E_St201_B4_WPC_InPosition					    = Eing(A42,7);
        pattern = re.compile(r'\s*(?P<Var>E_[sS]t(?P<StN>\d+)_B(?P<BN>\d+)_[24]_(?P<BName>\w+(?P<Motion>front|back|up|down|left|right)))\s*')
        match = pattern.match(eline)
        if match:
            self.Var = match.group('Var')
            self.StN = match.group('StN')
            self.BN = match.group('BN')
            self.BName = match.group('BName')
            self.Motion = match.group('Motion')

    def display(self):
        print(self.Var)


class NBin:
    def __init__(self,eline):
        self.Str = eline
        self.Var = ''
        self.StN = ''
        self.BN = ''
        self.BName = ''
        self.tobin(eline)

    def tobin(self, eline):
        """transform station statement to Inputs struct"""
        # E_St4_B1_4_Belt_crushing_in_front				= Eing(A51,0);
        pattern = re.compile(r'\s*(?P<Var>E_[sS]t(?P<StN>\d+)_B(?P<BN>\d+)_(?P<BName>\w+))\s*')
        match = pattern.match(eline)
        if match:
            self.Var = match.group('Var')
            self.StN = match.group('StN')
            self.BN = match.group('BN')
            self.BName = match.group('BName')

    def display(self):
        print(self.Var)

class ZBins:
    def __init__(self):
        self.elements=[]

    def search(self, StN, BN, Motion):
        dict={'forward':'front', 'backward':'back', 'upward':'up', 'downward':'down', 'leftward':'left', 'rightward':'right'}
        for key,value in dict.items():
            Motion = Motion.replace(key, value)

        for elem in self.elements:
            # print('elem:')
            # print(str(type(elem.StN)) + str(type(StN)))
            # print(elem.StN + '->' + StN + ':' + str(elem.StN == StN))
            # print(elem.BN + '->' + BN + ':' + str(elem.BN == BN))
            # print(elem.Motion + '->' + ':' + str(elem.Motion == Motion))
            if elem.StN == StN and elem.BN == BN and elem.Motion == Motion:
                return elem
        return None

    def add(self, zbin):
        self.elements.append(zbin)

    def display(self):
        for elem in self.elements:
            print(elem.Var)

class NBins:
    def __init__(self):
        self.elements = []

    def search(self, StN, BN):
        for elem in self.elements:
            if elem.StN == StN and elem.BN == BN :
                return elem
        return None

    def add(self, nbin):
        self.elements.append(nbin)

    def display(self):
        for elem in self.elements:
            print(elem.Var)