import re

class Input:
    def __init__(self,eline):
        self.StN = 0
        self.SensorN = 0
        self.SensorName = ''
        self.A = 0
        self.Points = 0
        self.Type = ''

        self.gettype(eline)

        if self.Type == 'Cylinder Sensor':
            self.tozin(eline)
        if self.Type == 'Normal Sensor':
            self.tobin(eline)
        if self.Type == 'Normal Input':
            print('normalinput')


    def gettype(self, eline):
        zbpattern = re.compile(r'.*_B\d+_[24].*')
        nbpattern = re.compile(r'.*_B\d+_\w.*')
        if zbpattern.match(eline):
            self.Type = 'Cylinder Sensor'
        elif nbpattern.match(eline):
            self.Type = 'Normal Sensor'
        else:
            self.Type = 'Normal Input'


    def tozin(self,eline):
        """transform station statement to Inputs struct"""
        # "E_St201_B4_WPC_InPosition					    = Eing(A42,7);
        #pattern = re.compile(r'.*St(?P<StN>\d+).*_B(?P<SensorN>\d+)_\d_'
        #                     r'(?P<SensorName>\w+)(_in_front|_back|_up|_down)'
        #                     r'.*=.*\(A(?P<A>\d+).*\,(?P<Points>\d+)')
        pattern = re.compile(r'.*St(?P<StN>\d+).*_B(?P<SensorN>\d+)_\d_'
                             r'(?P<SensorName>\w+)'
                             r'.*=.*\(A(?P<A>\d+).*\,(?P<Points>\d+)')
        match = pattern.match(eline)
        if match:
            self.StN = match.group('StN')
            self.SensorN = match.group('SensorN')

            self.SensorName = match.group('SensorName')
            self.A = match.group('A')
            self.Points = match.group('Points')
            self.Type='Cylinder Sensor'


    def tobin(self, eline):
        """transform station statement to Inputs struct"""
        # "E_St201_B4_WPC_InPosition					    = Eing(A42,7);
        pattern = re.compile(r'.*St(?P<StN>\d+).*_B(?P<SensorN>\d+)_'
                             r'(?P<SensorName>\w+)'
                             r'.*=.*\(A(?P<A>\d+).*\,(?P<Points>\d+)')
        match = pattern.match(eline)
        if match:
            self.StN = match.group('StN')
            self.SensorN = match.group('SensorN')

            self.SensorName = match.group('SensorName')
            self.A = match.group('A')
            self.Points = match.group('Points')
            self.Type='Normal Sensor'


    def display(self):
        if self.Type == 'Cylinder Sensor':
            print("St"+self.StN+" B"+self.SensorN+" SensorName:"+self.SensorName+" A"+self.A+"."+self.Points)
        if self.Type == 'Normal Sensor':
            print("St"+self.StN+" B"+self.SensorN+" SensorName:"+self.SensorName+" A"+self.A+"."+self.Points)
        if self.Type == 'Normal Input':
            print(self.Type)


class Inputs:
    def __init__(self):
        self.list = []

    def getcount(self):
        return len(self.list)

    def add(self, input):
        self.list.append(input)

    def stsort(self):
        self.list.sort(key=lambda o:(int(o.A), int(o.Points), int(o.StN), int(o.SensorN)))

    def display(self):
        for elems in self.list:
            elems.display()
