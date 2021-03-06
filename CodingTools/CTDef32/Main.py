
import re
from Form import *
from zline import *
from spsfile import *
form1 = Form()

sps_h_file = SpsFile('sps.h')
zbins = sps_h_file.zbins
nbins = sps_h_file.nbins
zouts = sps_h_file.zouts
sps_h_file.zouts.display()

def update_button_click():
    #form1.write_editbox('c3 st10 z1 forward z1 back f2 \nc4 st5 z1 up ')
    zcode = form1.read_editbox().strip('\r\n')
    zcode_lines = re.split('\n', zcode)

    form1.clear_displaybox()
    for ln in zcode_lines:
        ln = ln.lower()
        if re.compile('.*st?.*(z\d+|b\d+).*\w+.*').match(ln):
            zl = ZLine(ln)
            try:
                form1.write_displaybox(zl.formatted_code(zbins, nbins, zouts))
            except:
                form1.write_displaybox(ln + '--->can not find this object or action\n\n')

        elif re.compile('^\s*$').match(ln):
            form1.write_displaybox('\n')
        else:
            form1.write_displaybox(ln+ '--->format needs to be like this:[cx] s[t]x zx action [fx] or [cx] stx bx on/off [fx]\n')


def import_button_click():
    print("delete button pressed")
    form1.clear_displaybox()


def form_close():
    print('widows closing')
    sys.exit()


def form_initial():

    form1.UpdateButtonEvent.append(update_button_click)
    form1.ImportButtonEvent.append(import_button_click)
    form1.CloseWindowEvent.append(form_close)


form_initial()





def ddd():
    global str
    f = open('sps.h', 'r', encoding='utf-8', errors='ignore')
    fsps = f.read()
    f.close()
    f = open('sps.h', 'w', encoding='utf-8', errors='ignore')
    str = 'newline\n'
    f.write(str + fsps)
    f.close()




