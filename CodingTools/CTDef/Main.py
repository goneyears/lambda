
from Form import *
from Program import *


def windowclose():
    print('widows closing')
    sys.exit()

def Form_initial():
    form1 = Form()
    print('1')

    form1.UpdateButtonEvent.append(UpdateButton_Click)
    form1.CloseWindowEvent.append(windowclose)

Form_initial()


