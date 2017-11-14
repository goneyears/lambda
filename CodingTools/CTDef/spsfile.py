import re
from binputs import *
from zoutputs import *

class SpsFile:
    def __init__(self, spshfile):
        self.stlines = self.filetolinelist(spshfile)
        self.nbins = self.getnbin()
        self.zbins = self.getzbin()
        self.zouts = self.getzout()

    def selstline(self,line):
        """check the single line if it contains a station input or output"""
        pattern = re.compile(
            r'^(?!((\s*//)|(.*->.*)))\s*(?P<st>((.*?[sS]t\d.*?Eing).*?;)|((.*?SetAusg.*?([sS]t)\d.*?;)))')
        match = pattern.match(line)
        if match:
            return match.group('st')
        else:
            return None

    def filetolinelist(self, filename):
        """filter the input and output of the station from the file
        and convert them into a list"""
        fstream = open(filename, encoding='utf-8', errors='ignore')

        matchlinelist = []
        while True:
            line = fstream.readline()
            if not line:
                break

            res = self.selstline(line)
            if res:
                matchlinelist.append(res)

        fstream.close()

        return matchlinelist

    def printlist(lst):
        """print list line by line"""
        elem = ''
        for elem in lst:
            print(elem)

    def getnbin(self):
        nbins = NBins()

        pattern = re.compile(r'\s*E_[sS]t\d+_B\d+_[^24].*')
        for stl in self.stlines:
            match = pattern.match(stl)
            if match:
                nbins.add(NBin(stl))
        return nbins

    def getzbin(self):
        zbins = ZBins()

        pattern = re.compile(r'\s*E_[sS]t\d+_B\d+_[24].*')
        for stl in self.stlines:
            match = pattern.match(stl)
            if match:
                print('bbbbbb:'+stl)
                zbins.add(ZBin(stl))
        return zbins

    def getzout(self):
        """	SetAusg(A2,0,A.St10_Y1_4_good_parts_ejector_forward);"""
        zouts = Zouts()

        pattern = re.compile(r'.*[sS]t\d+_Y\d+_[24].*')
        for stl in self.stlines:
            match = pattern.match(stl)
            if match:
                zouts.add(Zout(stl))
        return zouts

# f=SpsFile('sps.h')
# # f.nbins.display()
# # f.zbins.display()
# f.zouts.display()
# print('--------')
# f.zouts.search('10','1','forward').display()




