# -*- coding: utf-8 -*-

import pymysql

import RPi.GPIO as GPIO
import time
## 加上字符集参数，防止中文乱码
dbconn = pymysql.connect(
    host="123.206.125.181",
    database="TEST",
    user="root",
    password="terentny",
    port=3306,
    charset='utf8'
)

print('connected!')



GPIO.setmode(GPIO.BOARD)
# 输出模式
#channel = int(input("enter channel:"))
channel = 11
GPIO.setup(channel, GPIO.OUT)
GPIO.setup(13, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

print('borad set complete')

while True:
    if GPIO.input(13):
        GPIO.output(channel, GPIO.HIGH)
        print("gpio output high")

        # sql语句
        sqlcmd = "select * from TEST limit 10"

        cursor = dbconn.cursor()
        # 执行mysql语句，并返回执行的结果
        cursor.execute(sqlcmd)
        res = cursor.fetchall()
        # 打印执行的结果
        print(res)
        # 把要执行的语句提交，否则无法保存新建或者修改数据
        dbconn.commit()

        # 关闭游标
        cursor.close()
    else:
        GPIO.output(channel, GPIO.LOW)
        print("gpio output low")
    time.sleep(1)

#关闭连接
dbconn.close()






