# _*_ coding:utf-8 _*_
import re
from Inputs import *
from Outputs import *


def selstline(line):
    """check the single line if it contains a station input or output"""
    pattern = re.compile(
        r'^(?!((\s*//)|(.*->.*)))(((?:.*[sS]t\d.*Eing).*)|((?:.*SetAusg.*([sS]t)\d.*).*));')
    match = pattern.match(line)
    if match:
        return match.group()
    else:
        return None


def filetolinelist():
    """filter the input and output of the station from the file
    and convert them into a list"""
    fstream = open("sps.h", encoding='utf-8', errors='ignore')

    matchlinelist = []
    line = fstream.readline()

    while True:
        line = fstream.readline()
        if not line:
            break

        res = selstline(line)
        if res:
            matchlinelist.append(res)

    fstream.close()

    return matchlinelist


def printlist(lst):
    """print list line by line"""
    elem=''
    for elem in lst:
        print(elem)






iolist = filetolinelist()
Ins = Inputs()
Outs = Outputs()

elem=''
for elem in iolist:
    patternin = re.compile(r'.*Eing.*')
    patternout = re.compile(r'.*SetAusg.*')
    if patternin.match(elem):
        Ins.add(Input(elem))
    if patternout.match(elem):
        Outs.add(Output(elem))

#Ins.display()
print('\n')
Ins.stsort()
Ins.display()

#Outs.display()
print('\n')
Outs.stsort()
Outs.display()


