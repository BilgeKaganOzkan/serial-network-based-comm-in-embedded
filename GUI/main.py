"""!
\addtogroup main
@{
@author Bilge Kağan ÖZKAN
@file main.py
@defgroup main
@brief This module main module of the project.
@verbatim
This module objectifies MainWindow class and show user the MainWindow object visually.
@endverbatim
"""

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

# @}
