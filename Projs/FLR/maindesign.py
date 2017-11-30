# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'maindesign.ui'
#
# Created by: PyQt5 UI code generator 5.9.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(2053, 1470)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.FButton = QtWidgets.QPushButton(self.centralwidget)
        self.FButton.setGeometry(QtCore.QRect(910, 890, 131, 111))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(22)
        self.FButton.setFont(font)
        self.FButton.setObjectName("FButton")
        self.textEdit = QtWidgets.QTextEdit(self.centralwidget)
        self.textEdit.setGeometry(QtCore.QRect(910, 30, 1121, 821))
        self.textEdit.setObjectName("textEdit")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(250, 310, 181, 181))
        self.label.setText("")
        self.label.setPixmap(QtGui.QPixmap("res/up.png"))
        self.label.setObjectName("label")
        self.LButton = QtWidgets.QPushButton(self.centralwidget)
        self.LButton.setGeometry(QtCore.QRect(1050, 890, 131, 111))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(22)
        self.LButton.setFont(font)
        self.LButton.setObjectName("LButton")
        self.RButton = QtWidgets.QPushButton(self.centralwidget)
        self.RButton.setGeometry(QtCore.QRect(1190, 890, 131, 111))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(22)
        self.RButton.setFont(font)
        self.RButton.setObjectName("RButton")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 2053, 38))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.FButton.setText(_translate("MainWindow", "F"))
        self.LButton.setText(_translate("MainWindow", "L"))
        self.RButton.setText(_translate("MainWindow", "R"))

