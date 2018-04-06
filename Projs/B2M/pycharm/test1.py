# -*- coding: utf-8 -*-

import pandas as pd
import pymysql
import time
## 加上字符集参数，防止中文乱码
while True:
    try:
        dbconn = pymysql.connect(
            host="123.206.125.181",
            database="TEST",
            user="root",
            password="terentny",
            port=3306,
            charset='utf8'
        )

        print('connected!')
        break
    except Exception as e:
        time.sleep(0.5)
        print("connection cannot establised")
        print(e)


while True:
    # sql语句
    sqlcmd = "select test_count from test ORDER BY  test_time DESC LIMIT 1"

    cursor = dbconn.cursor()
    # 执行mysql语句，并返回执行的结果
    try:
        cursor.execute(sqlcmd)
        res = cursor.fetchall()

        # 打印执行的结果
        s = ''
        print(res)
        for r in res:
            for r1 in r:
                s = s+str(r1)+' '
                print(r1)

        print(s)
        # 把要执行的语句提交，否则无法保存新建或者修改数据

        dbconn.commit()

        # 关闭游标
        cursor.close()
    except Exception as e:
        print("except 1")
        print(e)
        cursor.close()

        try:
            dbconn = pymysql.connect(
                host="123.206.125.181",
                database="TEST",
                user="root",
                password="terentny",
                port=3306,
                charset='utf8'
            )
            #print("connected")

        except Exception as e:
            time.sleep(0.5)
            print("except 2")
            print(e)
    time.sleep(0.5)

    break;