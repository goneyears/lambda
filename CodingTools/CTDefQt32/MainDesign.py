# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'MainDesign.ui'
#
# Created by: PyQt5 UI code generator 5.9.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(883, 596)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.updateButton = QtWidgets.QPushButton(self.centralwidget)
        self.updateButton.setGeometry(QtCore.QRect(270, 250, 81, 51))
        self.updateButton.setObjectName("updateButton")
        self.editbox = QtWidgets.QTextEdit(self.centralwidget)
        self.editbox.setGeometry(QtCore.QRect(10, 20, 251, 531))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(10)
        self.editbox.setFont(font)
        self.editbox.setObjectName("editbox")
        self.displaybox = QtWidgets.QTextEdit(self.centralwidget)
        self.displaybox.setGeometry(QtCore.QRect(360, 20, 501, 531))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(10)
        self.displaybox.setFont(font)
        self.displaybox.setLineWrapMode(QtWidgets.QTextEdit.NoWrap)
        self.displaybox.setObjectName("displaybox")
        self.onlineInsertButton = QtWidgets.QPushButton(self.centralwidget)
        self.onlineInsertButton.setGeometry(QtCore.QRect(270, 180, 75, 51))
        self.onlineInsertButton.setObjectName("onlineInsertButton")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 883, 21))
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
        self.updateButton.setText(_translate("MainWindow", "GenCode"))
        self.editbox.setHtml(_translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Consolas\'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:\'MS Shell Dlg 2\'; font-size:8.25pt;\"><br /></p></body></html>"))
        self.onlineInsertButton.setText(_translate("MainWindow", "OnlineVar"))

