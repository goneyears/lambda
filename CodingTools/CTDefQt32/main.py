import sys
import MainDesign

import re
from zline import *
from spsfile import *
from spshelper import *

from PyQt5.QtWidgets import QApplication, QMainWindow




def read_editbox():
    return str(ui.editbox.toPlainText())


def write_displaybox(str):
    ui.displaybox.append(str)

def clear_displaybox():
    ui.displaybox.setText('')

def update_button_click():

    #form1.write_editbox('c3 st10 z1 forward z1 back f2 \nc4 st5 z1 up ')
    zcode = read_editbox().strip('\r\n')
    zcode_lines = re.split('\n', zcode)

    clear_displaybox()
    for ln in zcode_lines:
        ln = ln.lower()
        if re.compile('.*st?.*(z\d+|b\d+).*\w+.*').match(ln):
            zl = ZLine(ln)
            try:
                write_displaybox(zl.formatted_code(zbins, nbins, zouts))
            except:
                write_displaybox(ln + '--->can not find this object or action\n\n')

        elif re.compile('^\s*$').match(ln):
            write_displaybox('\n')
        else:
            write_displaybox(ln+ '--->format needs to be like this:[cx] s[t]x zx action [fx] or [cx] stx bx on/off [fx]\n')


def online_insert_button_click():
    varstrs = read_editbox().strip('\r\n')
    varstrlines = re.split('\n', varstrs)
    print(varstrlines)
    for ln in varstrlines:
        print(ln)
        try:
            write_displaybox(insertonlinevardef(ln.strip()))
        except:
            write_displaybox(ln.strip()+' can not be inserted')



if __name__ =='__main__':
    app = QApplication(sys.argv)
    MainWindow = QMainWindow()
    ui = MainDesign.Ui_MainWindow()
    ui.setupUi(MainWindow)
    ui.updateButton.clicked.connect(update_button_click)
    ui.onlineInsertButton.clicked.connect(online_insert_button_click)
    MainWindow.show()

    sps_h_file = SpsFile('sps.h')
    zbins = sps_h_file.zbins
    nbins = sps_h_file.nbins
    zouts = sps_h_file.zouts
    sps_h_file.zouts.display()

    sys.exit(app.exec_())
