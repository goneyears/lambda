
import re
from Form import *
from Program import *

form1 = Form()

def UpdateButton_Click():
    print("test print-----")
    form1.writedisplaybox(Zline(form1.readeditbox()).formatedcode())

def Form_Close():
    print('widows closing')
    sys.exit()

def Form_initial():

    form1.UpdateButtonEvent.append(UpdateButton_Click)
    form1.CloseWindowEvent.append(Form_Close)

Form_initial()


str = ' c332 st123  z132  up  f1200 '
#c1 st1 z1 up f2, z2 forward f3
#case2 st2 z3 down f4, z4 left f5
#c3 b1 t123
# eg.
# c3 st1 b1 t1 f7
# c4 st1 z2 down f3, z3 down f5
# c5 st1 z1 forward f1
# c6 st1 z2 up f4, z3 up f6, z1 back f6


class Zline:
    def __init__(self,_zline):
        self.Str=_zline
        self.StN = ''
        self.CylinderN = ''
        self.Motion = ''
        self.Fehler = ''
        self.Case = ''

        self.Gen(str)
    def Gen(self, str):

        pattern = re.compile(r'.*st(?P<StN>\d+)\s+z(?P<CylinderN>\d+)\s+(?P<Motion>\w+)')
        match = pattern.match(str)

        if match:
            self.StN = match.group('StN')
            self.CylinderN = match.group('CylinderN')
            self.Motion = match.group('Motion')

            patternfehler = re.compile(r'.*f(ehler)?\s*(?P<Fehler>\d+)')
            match = patternfehler.match(str)

            if patternfehler.match(str):
                self.Fehler = match.group('Fehler')

            patterntimer = re.compile(r'.*c(ase)?\s*(?P<Case>\d+)')
            match = patterntimer.match(str)
            if patterntimer.match(str):
                self.Case = match.group('Case')

    def formatedcode(self):
        cstr1='case' + self.Case +':'
        cstr2='   St' + self.StN + ' Z' + self.CylinderN +' '+ self.Motion
        cstr3='f:' + self.Fehler
        return cstr1 + '\n' + cstr2 + '\n' + cstr3 + '\n'



def ddd():
    global str
    f = open('sps.h', 'r', encoding='utf-8', errors='ignore')
    fsps = f.read()
    f.close()
    #print(fsps)
    f = open('sps.h', 'w', encoding='utf-8', errors='ignore')
    str = 'newline\n'
    f.write(str + fsps)
    f.close()




