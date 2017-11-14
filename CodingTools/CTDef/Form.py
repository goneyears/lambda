#!/usr/bin/python
# -*- coding: UTF-8 -*-

import tkinter, threading, sys
import time
from tkinter.scrolledtext import ScrolledText


class Form:
    def __init__(self):
        t1 = threading.Thread(target=self.window_init)
        t1.setDaemon(False)
        t1.start()

        #print('true')
        self.UpdateButtonEvent = []
        self.ImportButtonEvent = []
        self.CloseWindowEvent = []
        # self.window_init()

    def window_init(self):
        print('2')
        self.root = tkinter.Tk()
        self.root.protocol("WM_DELETE_WINDOW", self.window_close)
        self.root.title("CTDef")
        self.root.geometry('1400x505')
        frm = tkinter.Frame(self.root)
        frm__l = tkinter.Frame(frm)
        frm__i = tkinter.Frame(frm)
        frm__r = tkinter.Frame(frm)

        self.editbox=ScrolledText(frm__r, width=40, height=33.5, font=('Consolas', 10), background='#ffffff')
        self.displaybox=ScrolledText(frm__r, width=140, height=33.5, font=('Consolas', 10), background='#ffffff')

        self.editbox.pack(expand=1, fill="both", side=tkinter.LEFT)
        self.displaybox.pack(expand=1, fill="both", side=tkinter.RIGHT)

        tkinter.Button(frm__r, height=3, width=10, text="get->", command=self.update_button_click).pack(side=tkinter.LEFT)

        frm__l.pack(side=tkinter.LEFT)
        frm__i.pack(side=tkinter.RIGHT)
        frm__r.pack(side=tkinter.RIGHT)
        frm.pack()

        self.root.mainloop()

    def window_close(self):
        #[m() for m in self.CloseWindowEvent]
        print('main window exit')

        self.root.quit()

    def update_button_click(self):
        [n() for n in self.UpdateButtonEvent]

    def import_button_click(self):
        [n() for n in self.ImportButtonEvent]

    def read_editbox(self):
        return self.editbox.get('1.0', tkinter.END)

    def write_editbox(self, str):
        self.editbox.insert(tkinter.END, str)

    def write_displaybox(self, str):
        self.displaybox.insert(tkinter.END, str)

    def clear_displaybox(self):
        self.displaybox.delete('1.0', tkinter.END)






