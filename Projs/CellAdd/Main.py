#!/usr/bin/python
# -*- coding: UTF-8 -*-

import tkinter,socket,threading
import time
from tkinter.scrolledtext import ScrolledText

import logging
import logging.handlers

LOG_FILE = 'cell4.log'

handler = logging.handlers.RotatingFileHandler(LOG_FILE, maxBytes=1024 * 1024, backupCount=5)  # 实例化handler
fmt = '%(asctime)s - %(filename)s:%(lineno)s - %(name)s - %(message)s'

formatter = logging.Formatter(fmt)  # 实例化formatter
handler.setFormatter(formatter)  # 为handler添加formatter

logger = logging.getLogger('tst')  # 获取名为tst的logger
logger.addHandler(handler)  # 为logger添加handler
logger.setLevel(logging.DEBUG)

logger.info('start logging')

def currenttime():
    return  time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))


def send(str):
    socketobj.sendall(bytes(str, encoding="utf-8"))

def doConnect(host,port):
    sock=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
    sock.setblocking(0)
    sock.settimeout(1)
    try:
        sock.connect((host,port))
    except:
        pass
    return sock

def receivemessage():

    global socketobj
    print("start--------")
    msgstr=currenttime()+":\n"+"start\n"
    messagetextbox.insert(tkinter.END,msgstr )
    logger.info(msgstr)
    while 1:
        try:
            ret_bytes = socketobj.recv(1024)
            if ret_bytes.strip():
                ret_str = str(ret_bytes, encoding="utf-8")
                print(ret_str)

                msgstr = currenttime()+":\n"+ret_str+"\n"
                messagetextbox.insert(tkinter.END,msgstr)
                messagetextbox.see(tkinter.END)
                logger.info(msgstr)
            else:
                print("reconnect")
                time.sleep(1)
                socketobj=doConnect("192.168.10.40", 50002)
        except:
            #print("exception")
            pass


def canceltask():
    send("Cancel Current Task")


def clearbuffer():
    send("Clear Product Buffer")

def readbuffer():
    send("Read Product Buffer")

def clearrfid():
    send("Clear WPC RFID")


def readrfid():
    send("Read WPC RFID")

def test():
    print("send ddd")
    send("ddd")


root = tkinter.Tk()
root.title("CELL4")
root.geometry('700x505')
frm=tkinter.Frame(root)
frm_L=tkinter.Frame(frm)
frm_R=tkinter.Frame(frm)
messagetextbox=ScrolledText(frm_R,width=80,height=33.5,font=('Consolas', 10),background='#ffffff')
#messagetextbox = tkinter.Text(frm_R, width=50, height=20)

socketobj=doConnect("192.168.10.40", 50002)

messagetextbox.pack(expand=1, fill="both")
tkinter.Button(frm_L, height=6,width=20,text="读夹具RFID",command=readrfid).pack(side=tkinter.TOP)

tkinter.Button(frm_L, height=6,width=20,text="清空夹具RFID",command=clearrfid).pack(side=tkinter.TOP)

tkinter.Button(frm_L, height=6,width=20,text="取消当前MES任务",command=canceltask).pack(side=tkinter.TOP)

tkinter.Button(frm_L, height=6,width=20,text="读取库存记录",command=readbuffer).pack(side=tkinter.TOP)

tkinter.Button(frm_L, height=6,width=20,text="清空库存记录",command=clearbuffer).pack(side=tkinter.TOP)


frm_L.pack(side=tkinter.LEFT)
frm_R.pack(side=tkinter.RIGHT)
frm.pack()
t1=threading.Thread(target=receivemessage)
t1.setDaemon(True)
t1.start()

root.mainloop()

