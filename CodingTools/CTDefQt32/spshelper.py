import re

def insertlinetofile(filename,linenumber,content):
    flines = filetolines(filename)
    f = open(filename, 'w', encoding='utf-8', errors='ignore')

    flines.insert(linenumber,content+'\n')
    njfsps = ''.join(flines)
    #print(njfsps)
    str = njfsps
    f.write(str)
    f.close()


def getlinenumber(filename, regstr):
    flines = filetolines(filename)
    pattern = re.compile(regstr)
    for index,ln in enumerate(flines):
        if pattern.match(ln):
            return index

def getvartype(filename, varname):
    flines = filetolines(filename)
    pattern = re.compile('^\s*(bool|BYTE|int|WORD|LONG|float|double)\s+(\w+)')
    for index,ln in enumerate(flines):
        match = pattern.match(ln)
        if match:
            if match.group(2)==varname:
                print(ln)
                print(varname)
                return match.group(1)
    return None
def typetonumber(tp):
    switcher = {
        'bool':1,
        'BYTE':1,
        'int':2,
        'WORD':2,
        'LONG':4,
        'float':4,
        'double':8,
    }
    return switcher.get(tp,None)

def filetolines(filename):
    f = open(filename, 'r', encoding='utf-8', errors='ignore')
    flines = f.readlines()
    f.close()
    return flines

def insertonlinevardef(varstr):
    tp = getvartype('spsvar.h',varstr)
    if tp:
        tpnumber = typetonumber(tp)
    if tpnumber:
        ln = getlinenumber('spsvar.h', r'^\s*OnlineVarEintragen\("')
        insertlinetofile('spsvar.h',ln,r'    OnlineVarEintragen("'+varstr+'",'+str(tpnumber)+', &'+varstr+r');')
        return "complete!"
    return "variable not found"

