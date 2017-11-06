#!/usr/bin/python
# -*- coding: UTF-8 -*-

import tkinter,socket,threading, sys
import time
from tkinter.scrolledtext import ScrolledText

class Form:
    def __init__(self):
        t2 = threading.Thread(target=self.windowinit)
        t2.setDaemon(False)
        t2.start()

        print('true')
        self.UpdateButtonEvent = []
        self.CloseWindowEvent = []
        #self.windowinit()



    def windowinit(self):
        print('2')
        self.root = tkinter.Tk()
        #self.root.protocol("WM_DELETE_WINDOW", self.windowclose)
        self.root.title("CTDef")
        self.root.geometry('700x505')
        frm=tkinter.Frame(self.root)
        frm_L=tkinter.Frame(frm)
        frm_R=tkinter.Frame(frm)

        editbox=ScrolledText(frm_R, width=40, height=33.5, font=('Consolas', 10), background='#ffffff')
        displaybox=ScrolledText(frm_R, width=40, height=33.5, font=('Consolas', 10), background='#ffffff')


        editbox.pack(expand=1, fill="both", side=tkinter.LEFT)
        displaybox.pack(expand=1, fill="both", side=tkinter.RIGHT)
        tkinter.Button(frm_L, height=6, width=20, text="更新", command=self.updatebuttonclick).pack(side=tkinter.TOP)

        frm_L.pack(side=tkinter.LEFT)
        frm_R.pack(side=tkinter.RIGHT)
        frm.pack()

        self.root.mainloop()

    def windowclose(self):
        #[m() for m in self.CloseWindowEvent]
        print('mainwindow exit')

        self.root.quit()

    def updatebuttonclick(self):
        [n() for n in self.UpdateButtonEvent]



    def test(self):
        print('test print')



