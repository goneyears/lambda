import re

class Output:
    def __init__(self, aline):
        self.StN = 999
        self.CylinderN = 999
        self.CylinderName = ''
        self.OutName = ''
        self.A = 0
        self.Points = 0
        self.Type = ''

        self.gettype(aline)
        if self.Type == 'Cylinder Output':
            self.tozout(aline)
        if self.Type == 'Normal Station Output':
            self.tonstout(aline)
        if self.Type == 'Normal Output':
            self.tonout(aline)



    def gettype(self, eline):
        zopattern = re.compile(r'.*_Y\d+_[24].*')
        nstopattern = re.compile(r'.*_St\d+_.*')
        if zopattern.match(eline):
            self.Type = 'Cylinder Output'
        elif nstopattern.match(eline):
            self.Type = 'Normal Station Output'
        else:
            self.Type = 'Normal Output'


    def tozout(self, aline):
        """transform station statement to Cylinder Outputs struct"""
        # SetAusg(A120,5,A.St201_Y1_2_SwivelUnit_backward);
        #pattern = re.compile(r'.*\(A(?P<A>\d+).*,(?P<Points>\d+).*St(?P<StN>\d+).*_Y(?P<CylinderN>\d+).*_\d_'
        #                     r'(?P<CylinderName>\w+)(_upward|_downward|_forward|_backward)')
        pattern = re.compile(r'.*\(A(?P<A>\d+).*,(?P<Points>\d+).*St(?P<StN>\d+).*_Y(?P<CylinderN>\d+).*_\d_'
                             r'(?P<CylinderName>\w+)')
        match = pattern.match(aline)
        if match:
            self.A = match.group('A')
            self.Points = match.group('Points')
            self.StN = match.group('StN')
            self.CylinderN = match.group('CylinderN')
            self.CylinderName = match.group('CylinderName')

    def tonstout(self, aline):
        """transform station statement to Normal Outputs struct"""
        # SetAusg(A120,5,A.St201_Y1_2_SwivelUnit_backward);
        pattern = re.compile(r'.*\(A(?P<A>\d+).*,(?P<Points>\d+).*St(?P<StN>\d+)_(?P<OutName>\w*).*\)');
        match = pattern.match(aline)
        if match:
            self.A = match.group('A')
            self.Points = match.group('Points')
            self.StN = match.group('StN')
            self.OutName = match.group('OutName')


    def tonout(self, aline):
        """transform station statement to Normal Outputs struct"""
        # SetAusg(A120,1,A_MainAir[2]);
        pattern = re.compile(r'.*\(A(?P<A>\d+).*,(?P<Points>\d+).*(?P<OutName>A\w*).*\)');
        match = pattern.match(aline)
        if match:
            self.A = match.group('A')
            self.Points = match.group('Points')
            self.OutName = match.group('OutName')

    def display(self):
        if self.Type == 'Cylinder Output':
            print("St"+self.StN+" Y"+self.CylinderN+" CylinderName:"+self.CylinderName+" A"+self.A+","+self.Points)
        if self.Type == 'Normal Station Output':
            print("St"+self.StN+" StationOutputName:"+self.OutName+" A"+self.A+","+self.Points)
        if self.Type == 'Normal Output':
            print(" NormalOutputName:"+self.OutName+" A"+self.A+","+self.Points)

class Outputs:
    def __init__(self):
        self.list=[]

    def getcount(self):
        return len(self.list)

    def add(self, output):
        self.list.append(output)


    def stsort(self):
        self.list.sort(key=lambda o:(int(o.A), int(o.Points), int(o.StN), int(o.CylinderN)))

    def display(self):
        for elems in self.list:
            elems.display()