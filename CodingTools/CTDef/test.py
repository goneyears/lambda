#!/usr/bin/python
# -*- coding: UTF-8 -*-

import tkinter,socket,threading, sys
import time
from tkinter.scrolledtext import ScrolledText

def test():
    print('test function')



def windowinit():
    print('2')
    root = tkinter.Tk()
    #self.root.protocol("WM_DELETE_WINDOW", self.windowclose)
    root.title("CTDef")
    root.geometry('700x505')
    frm=tkinter.Frame(root)
    frm_L=tkinter.Frame(frm)
    frm_R=tkinter.Frame(frm)

    editbox=ScrolledText(frm_R, width=40, height=33.5, font=('Consolas', 10), background='#ffffff')
    displaybox=ScrolledText(frm_R, width=40, height=33.5, font=('Consolas', 10), background='#ffffff')


    editbox.pack(expand=1, fill="both", side=tkinter.LEFT)
    displaybox.pack(expand=1, fill="both", side=tkinter.RIGHT)
    tkinter.Button(frm_L, height=6, width=20, text="更新", command=test).pack(side=tkinter.TOP)

    frm_L.pack(side=tkinter.LEFT)
    frm_R.pack(side=tkinter.RIGHT)
    frm.pack()

    root.mainloop()



print('true')
t2 = threading.Thread(target=windowinit())
t2.setDaemon(True)
t2.start()
#self.windowinit()
