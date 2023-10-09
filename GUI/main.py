import sys
import os

libDir = (os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
+ '/lib/')
sys.path.append(libDir)

from PyQt5.QtWidgets import QApplication
from lib.MainWindow import MainWindow

try:
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec()
except Exception as e:
    print(e)