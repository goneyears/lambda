import re

str = 'E_St1_B3_4_housing_separator_driver_forward		       = Eing(A50,0);'

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
        pattern = re.compile(r'\s*(?P<Var>E_[sS]t(?P<StN>\d+)_B(?P<BN>\d+)_[24]_(?P<BName>\w+(?P<Motion>front|forward|back|up|down|left|right)))\s*')
        match = pattern.match(eline)
        if match:
            self.Var = match.group('Var')
            self.StN = match.group('StN')
            self.BN = match.group('BN')
            self.BName = match.group('BName')
            self.Motion = match.group('Motion')
            if self.Motion == 'forward': self.Motion = 'front'

    def display(self):
        print(self.Var)
st1 z1 up
st1 z2 down
st1 z3 forward
st041 b1 on
st043 b1 off

zbin = ZBin(str)
print(zbin.Var)