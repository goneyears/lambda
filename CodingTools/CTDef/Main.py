import re

str = ' c332 st123  z132  up  f1200 '
#case1 st1 z1 up f2, z2 forward f3
#case2 st2 z3 down f4, z4 left f5
#case4
StN = ''
CylinderN = ''
Motion = ''
Fehler = ''
Case = ''
pattern = re.compile(r'.*st(?P<StN>\d+)\s+z(?P<CylinderN>\d+)\s+(?P<Motion>\w+)')
match = pattern.match(str)

if match:
    StN = match.group('StN')
    CylinderN = match.group('CylinderN')
    Motion = match.group('Motion')

    patternfehler = re.compile(r'.*f(ehler)?\s*(?P<Fehler>\d+)')
    match = patternfehler.match(str)
    if patternfehler.match(str):
        Fehler = match.group('Fehler')

    patterntimer = re.compile(r'.*c(ase)?\s*(?P<Case>\d+)')
    match = patterntimer.match(str)
    if patterntimer.match(str):
        Case = match.group('Case')

def formatcode():
    cstr1='case' + Case +':'
    cstr2='   St' + StN + ' Z' + CylinderN +' '+ Motion
    cstr3='f:' + Fehler
    return cstr1 + '\n' + cstr2 + '\n' + cstr3 + '\n'

print(formatcode())