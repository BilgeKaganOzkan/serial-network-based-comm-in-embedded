"""!
\addtogroup MainWindow
@{
@author Bilge Kağan ÖZKAN
@file MainWindow.py
@defgroup MainWindow
@brief This module includes MainWindow and MqttSettingsWindow classes
@verbatim
MainWindow class provides an interface to show the system state, the led 1 pin state, 
the led 2 pin state and the button press counter visually.

MqttSettingsWindow class provides user an interface to configure mqtt connection settings.
And, it saves all configurations to mqttConfig.ini file when users press connection button and
get configurations and shows it to users when this class object is called. Also, after press the connect button,
this class connect to the MQTT server using MQTT class.
@endverbatim
"""

from PyQt5.QtWidgets import (
    QMainWindow, QApplication,
    QLabel, QAction, QStatusBar, 
    QWidget, QVBoxLayout, 
    QGridLayout, QDialog, QLineEdit, 
    QPushButton, QMessageBox, QStyle
)
from PyQt5.QtGui import QFont, QIcon
from PyQt5.QtCore import (Qt, pyqtSignal)
import configparser
from .Mqtt import Mqtt
import time

class MainWindow(QMainWindow):
    """! This class provides an interface to show the system state, the led 1 pin state, 
    the led 2 pin state and the button press counter visually. 
    """
    changeLabelsAndLightsSignal = pyqtSignal(dict) # ///< This variable indicates the signal to change system state by means of calling changeLabelsAndLights function

    def __init__(self) -> None:
        """! This function initializes all variables, creates objects from Mqtt and MqttSettingsWindow classes.
        Also, it prepares GUI.
        @param N/A
        @return N/A
        """
        super().__init__()
        
        self.mqtt = Mqtt(self)

        self.isMqttConnected = False

        windowWidth = 800
        windowHeight = 600

        labelPositionX = 585
        labelPositionY = 30
        labelPositionYSlide = 20
        labelWidth = 200
        labelHeight = 30

        self.setWindowTitle("Kuartis Project")
        self.setFixedSize(windowWidth, windowHeight)
        self.setStyleSheet("background-image: url('./designs/systemState0.png');")

        screenGeometry = QApplication.desktop().screenGeometry()

        windowX = (screenGeometry.width() - windowWidth) // 2
        windowY = (screenGeometry.height() - windowHeight) // 2

        self.setGeometry(windowX, windowY, windowWidth, windowHeight)

        labelsFont = QFont()
        labelsFont.setPointSize(12)
        labelsFont.setFamily('Aptos')

        statusPanelFont = QFont()
        statusPanelFont.setPointSize(14)
        statusPanelFont.setFamily('Aptos')
        statusPanelFont.setBold(True)

        container = QWidget()

        statusPanelLabel = QLabel(container)
        statusPanelLabel.setAlignment(Qt.AlignCenter)
        statusPanelLabel.setGeometry(labelPositionX, labelPositionY - labelPositionYSlide * 2, labelWidth, labelHeight + 10)
        statusPanelLabel.setFont(statusPanelFont)
        statusPanelLabel.setText("STATUS PANEL")
        statusPanelLabel.setAttribute(Qt.WA_TranslucentBackground, True)

        self.systemStateLabel = QLabel(container)
        self.systemStateLabel.setAlignment(Qt.AlignLeft)
        self.systemStateLabel.setGeometry(labelPositionX, labelPositionY, labelWidth, labelHeight)
        self.systemStateLabel.setFont(labelsFont)
        self.systemStateLabel.setText("System State: ")
        self.systemStateLabel.setAttribute(Qt.WA_TranslucentBackground, True)

        self.led1Label = QLabel(container)
        self.led1Label.setAlignment(Qt.AlignLeft)
        self.led1Label.setGeometry(labelPositionX, labelPositionY + labelPositionYSlide, labelWidth, labelHeight)
        self.led1Label.setFont(labelsFont)
        self.led1Label.setText("Led 1 State: ")
        self.led1Label.setAttribute(Qt.WA_TranslucentBackground, True)

        self.led2Label = QLabel(container)
        self.led2Label.setAlignment(Qt.AlignLeft)
        self.led2Label.setGeometry(labelPositionX, labelPositionY + labelPositionYSlide * 2, labelWidth, labelHeight)
        self.led2Label.setFont(labelsFont)
        self.led2Label.setText("Led 2 State: ")
        self.led2Label.setAttribute(Qt.WA_TranslucentBackground, True)

        self.buttonPressCountLabel = QLabel(container)
        self.buttonPressCountLabel.setAlignment(Qt.AlignLeft)
        self.buttonPressCountLabel.setGeometry(labelPositionX, labelPositionY + labelPositionYSlide * 3, labelWidth, labelHeight)
        self.buttonPressCountLabel.setFont(labelsFont)
        self.buttonPressCountLabel.setText("Button Press Count: ")
        self.buttonPressCountLabel.setAttribute(Qt.WA_TranslucentBackground, True)

        gridLayout = QGridLayout()

        gridLayout.addWidget(self.systemStateLabel)
        gridLayout.addWidget(self.led1Label)
        gridLayout.addWidget(self.led2Label)
        gridLayout.addWidget(self.buttonPressCountLabel)

        self.setCentralWidget(container)

        buttonAction = QAction("&MQTT Settings", self)
        buttonAction.triggered.connect(self.mqttSettingsButtonClick)

        self.setStatusBar(QStatusBar(self))

        menu = self.menuBar()

        settingsMenu = menu.addMenu("&Settings")
        settingsMenu.addAction(buttonAction)

        self.changeLabelsAndLightsSignal.connect(self.changeLabelsAndLights)

        buttonAction.trigger()

    def mqttSettingsButtonClick(self, s:bool) -> None:
        """! This function is a callback function. It calls after MQTT Settings button was clicked.
        Also, this function objectifies MqttSettingsWindow class and triggers show event of MqttSettingsWindow object.
        @param[in] s: This variable indicates that whether their connection was triggered or not.
        @return N/A
        """
        mqttSettingsWindow = MqttSettingsWindow(self.mqtt)
        mqttSettingsWindow.exec_()
    
    def changeLabelsAndLights(self, receivedMessageDict: dict) -> None:
        """! This function changes system state and show users received message visually.
        @param[in] receivedMessageDict: This variable indicates received message from mqtt topics.
        @return N/A
        """
        isMessageContentRight = False
        sytemState = 0
        backGround = "background-image: url('./designs/systemState0.png');"

        if (receivedMessageDict["systemState"] == "0" and receivedMessageDict["led1Status"] == "Off" and receivedMessageDict["led2Status"] == "Off"):
            isMessageContentRight = True
            systemState = int(receivedMessageDict["systemState"])
            backGround = "background-image: url('./designs/systemState0.png');"
        elif (receivedMessageDict["systemState"] == "1" and receivedMessageDict["led1Status"] == "Off" and receivedMessageDict["led2Status"] == "On"):
            isMessageContentRight = True
            systemState = int(receivedMessageDict["systemState"])
            backGround = "background-image: url('./designs/systemState1.png');"
        elif (receivedMessageDict["systemState"] == "2" and receivedMessageDict["led1Status"] == "On" and receivedMessageDict["led2Status"] == "Off"):
            isMessageContentRight = True
            systemState = int(receivedMessageDict["systemState"])
            backGround = "background-image: url('./designs/systemState2.png');"
        elif (receivedMessageDict["systemState"] == "3" and receivedMessageDict["led1Status"] == "On" and receivedMessageDict["led2Status"] == "On"):
            isMessageContentRight = True
            systemState = int(receivedMessageDict["systemState"])
            backGround = "background-image: url('./designs/systemState3.png');"
        else:
            pass

        if (isMessageContentRight == True):
            self.setStyleSheet(backGround)
            self.systemStateLabel.setText("System State: " + receivedMessageDict["systemState"])
            self.led1Label.setText("Led 1 State: " + receivedMessageDict["led1Status"])
            self.led2Label.setText("Led 2 State: " + receivedMessageDict["led2Status"])
            self.buttonPressCountLabel.setText("Button Press Count: " + receivedMessageDict["buttonPressCount"])

class MqttSettingsWindow(QDialog):
    """! This class provides an user interface to configure mqtt connection settings visually.
    And, it saves all configurations to mqttConfig.ini file when users press connection button and
    get configurations and shows it to users when this class object call. Also, after press the connect button,
    this class connect to the MQTT server using MQTT class.
    """

    def __init__(self, mqtt: Mqtt) -> None:
        """! This function initializes all variables. Also, it prepares GUI for MQTT configuration.
        @param[in] mqtt: This variable indicates Mqtt class object.
        @return N/A
        """
        super().__init__()

        self.mqtt = mqtt

        self.mqttSettingsDict = {
            "serverAddress": "",
            "port": 0,
            "username": "",
            "password": "",
            "systemStateTopic": "",
            "led1StateTopic": "",
            "led2StateTopic": "",
            "buttonPressCountTopic": ""
            }

        self.iniFilePath = "config/mqttConfig.ini"
        self.showPasswordIcon = QIcon('icons/showPasswordIcon.png')
        self.hidePasswordIcon = QIcon('icons/hidePasswordIcon')

        self.config = configparser.ConfigParser()

        self.mqttConnected = False

        windowWidth = 400
        windowHeight = 420

        labelPositionX = 10
        labelPositionY = 30
        labelPositionYSlide = 40
        labelWidth = 170
        labelHeight = 30

        self.setWindowTitle("MQTT Settings")
        self.setFixedSize(windowWidth, windowHeight)
        self.setStyleSheet("background-color:white")

        screenGeometry = QApplication.desktop().screenGeometry()

        windowX = (screenGeometry.width() - windowWidth) // 2
        windowY = (screenGeometry.height() - windowHeight) // 2

        self.setGeometry(windowX, windowY, windowWidth, windowHeight)

        font = QFont()
        font.setPointSize(12)
        font.setFamily('Times New Roman')

        container = QWidget()

        serverAddressLabel = QLabel(container)
        serverAddressLabel.setText("MQTT Server Adress")
        serverAddressLabel.setFont(font)
        serverAddressLabel.setGeometry(labelPositionX, labelPositionY, labelWidth - 20, labelHeight)

        portLabel = QLabel(container)
        portLabel.setText("MQTT Port")
        portLabel.setFont(font)
        portLabel.setGeometry(labelPositionX, labelPositionY + labelPositionYSlide, labelWidth, labelHeight)

        usernameLabel = QLabel(container)
        usernameLabel.setText("MQTT Username")
        usernameLabel.setFont(font)
        usernameLabel.setGeometry(labelPositionX,labelPositionY + labelPositionYSlide * 2, labelWidth, labelHeight)

        passwordLabel = QLabel(container)
        passwordLabel.setText("MQTT Password")
        passwordLabel.setFont(font)
        passwordLabel.setGeometry(labelPositionX,labelPositionY + labelPositionYSlide * 3, labelWidth, labelHeight)

        systemStateTopicLabel = QLabel(container)
        systemStateTopicLabel.setText("System State Topic")
        systemStateTopicLabel.setFont(font)
        systemStateTopicLabel.setGeometry(labelPositionX, labelPositionY + labelPositionYSlide * 4, labelWidth, labelHeight)

        led1StateTopicLabel = QLabel(container)
        led1StateTopicLabel.setText("Led 1 State Topic")
        led1StateTopicLabel.setFont(font)
        led1StateTopicLabel.setGeometry(labelPositionX, labelPositionY + labelPositionYSlide * 6, labelWidth, labelHeight)

        led2StateTopicLabel = QLabel(container)
        led2StateTopicLabel.setText("Led 2 State Topic")
        led2StateTopicLabel.setFont(font)
        led2StateTopicLabel.setGeometry(labelPositionX, labelPositionY + labelPositionYSlide * 7, labelWidth, labelHeight)

        buttonPressCountTopicLabel = QLabel(container)
        buttonPressCountTopicLabel.setText("Button Press Count Topic")
        buttonPressCountTopicLabel.setFont(font)
        buttonPressCountTopicLabel.setGeometry(labelPositionX, labelPositionY + labelPositionYSlide * 5, labelWidth, labelHeight)

        self.serverAddressTextbox = QLineEdit(container)
        self.serverAddressTextbox.setGeometry(labelPositionX + labelWidth, labelPositionY, labelWidth, labelHeight)

        self.portTextbox = QLineEdit(container)
        self.portTextbox.setGeometry(labelPositionX + labelWidth ,labelPositionY + labelPositionYSlide, labelWidth, labelHeight)

        self.usernameTextbox = QLineEdit(container)
        self.usernameTextbox.setGeometry(labelPositionX + labelWidth ,labelPositionY + labelPositionYSlide * 2, labelWidth, labelHeight)

        self.passwordTextbox = QLineEdit(container)
        self.passwordTextbox.setGeometry(labelPositionX + labelWidth ,labelPositionY + labelPositionYSlide * 3, labelWidth, labelHeight)
        self.passwordTextbox.setEchoMode(QLineEdit.Password)

        self.systemStateTextbox = QLineEdit(container)
        self.systemStateTextbox.setGeometry(labelPositionX + labelWidth, labelPositionY + labelPositionYSlide * 4, labelWidth, labelHeight)

        self.led1StateTextbox = QLineEdit(container)
        self.led1StateTextbox.setGeometry(labelPositionX + labelWidth, labelPositionY + labelPositionYSlide * 5, labelWidth, labelHeight)

        self.led2StateTextbox = QLineEdit(container)
        self.led2StateTextbox.setGeometry(labelPositionX + labelWidth, labelPositionY + labelPositionYSlide * 6, labelWidth, labelHeight)

        self.buttonPressCountTextbox = QLineEdit(container)
        self.buttonPressCountTextbox.setGeometry(labelPositionX + labelWidth, labelPositionY + labelPositionYSlide * 7, labelWidth, labelHeight)

        self.setSettingsButton = QPushButton(container)
        self.setSettingsButton.setGeometry(270, 360, 100, 30)
        self.setSettingsButton.setText("Connect")
        self.setSettingsButton.clicked.connect(self.setMqttSettings)

        self.showPasswordButton = QPushButton(container)
        self.showPasswordButton.setGeometry(labelPositionX + labelWidth * 2 + 7, labelPositionY + labelPositionYSlide * 3 + 6, 20, 20)
        self.showPasswordButton.clicked.connect(self.showOrHidePassword)
        self.showPasswordButton.setIcon(self.showPasswordIcon)
        self.showPasswordButton.setIconSize(self.showPasswordIcon.actualSize(self.showPasswordButton.size()))
        self.showPasswordButton.setStyleSheet('background-color:white; border: none;')

        self.layout = QVBoxLayout()
        self.layout.addWidget(container)
        self.setLayout(self.layout)

        self.readIniFile()
    
    def readIniFile(self) -> None:
        """! This function reads mqttConfig.ini file and shows users visually.
        @param N/A
        @return N/A
        """
        try:
            self.config.read(self.iniFilePath)

            self.mqttSettingsDict["serverAddress"] = self.config.get('MQTT_Settings', 'serverAddress')
            self.mqttSettingsDict["port"] = self.config.getint('MQTT_Settings', 'port')
            self.mqttSettingsDict["username"] = self.config.get('MQTT_Settings', 'username')
            self.mqttSettingsDict["password"] = self.config.get('MQTT_Settings', 'password')
            self.mqttSettingsDict["systemStateTopic"] = self.config.get('MQTT_Settings', 'systemStateTopic')
            self.mqttSettingsDict["led1StateTopic"] = self.config.get('MQTT_Settings', 'led1StateTopic')
            self.mqttSettingsDict["led2StateTopic"] = self.config.get('MQTT_Settings', 'led2StateTopic')
            self.mqttSettingsDict["buttonPressCountTopic"] = self.config.get('MQTT_Settings', 'buttonPressCountTopic')

            self.serverAddressTextbox.setText(self.mqttSettingsDict["serverAddress"])
            self.portTextbox.setText(str(self.mqttSettingsDict["port"]))
            self.usernameTextbox.setText(self.mqttSettingsDict["username"])
            self.passwordTextbox.setText(self.mqttSettingsDict["password"])
            self.systemStateTextbox.setText(self.mqttSettingsDict["systemStateTopic"])
            self.led1StateTextbox.setText(self.mqttSettingsDict["led1StateTopic"])
            self.led2StateTextbox.setText(self.mqttSettingsDict["led2StateTopic"])
            self.buttonPressCountTextbox.setText(self.mqttSettingsDict["buttonPressCountTopic"])

        except:
            self.mqttSettingsDict = {
            "serverAddress": "",
            "port": 0,
            "username": "",
            "password": "",
            "systemStateTopic": "",
            "led1StateTopic": "",
            "led2StateTopic": "",
            "buttonPressCountTopic": ""
            }

            self.serverAddressTextbox.setText("")
            self.portTextbox.setText("")
            self.usernameTextbox.setText("")
            self.passwordTextbox.setText("")
            self.systemStateTextbox.setText("")
            self.led1StateTextbox.setText("")
            self.led2StateTextbox.setText("")
            self.buttonPressCountTextbox.setText("")
    
    def setMqttSettings(self) -> None:
        """! This function is a callback function. It is called after connect button was clicked.
        It connects to the MQTT server using Mqtt class object.
        @param N/A
        @return N/A
        """
        checkedSuccess = self.checkTextBoxes()

        if (checkedSuccess):       
            self.mqttSettingsDict["serverAddress"] = self.serverAddressTextbox.text()
            self.mqttSettingsDict["port"] = int(self.portTextbox.text())
            self.mqttSettingsDict["username"] = self.usernameTextbox.text()
            self.mqttSettingsDict["password"] = self.passwordTextbox.text()
            self.mqttSettingsDict["systemStateTopic"] = self.systemStateTextbox.text()
            self.mqttSettingsDict["led1StateTopic"] = self.led1StateTextbox.text()
            self.mqttSettingsDict["led2StateTopic"] = self.led2StateTextbox.text()
            self.mqttSettingsDict["buttonPressCountTopic"] = self.buttonPressCountTextbox.text()

            self.config.remove_section("MQTT_Settings")
            self.config.add_section("MQTT_Settings")
            self.config.set("MQTT_Settings", "serverAddress", self.mqttSettingsDict["serverAddress"])
            self.config.set("MQTT_Settings", "port", str(self.mqttSettingsDict["port"]))
            self.config.set("MQTT_Settings", "username", self.mqttSettingsDict["username"])
            self.config.set("MQTT_Settings", "password", self.mqttSettingsDict["password"])
            self.config.set("MQTT_Settings", "systemStateTopic", self.mqttSettingsDict["systemStateTopic"])
            self.config.set("MQTT_Settings", "led1StateTopic", self.mqttSettingsDict["led1StateTopic"])
            self.config.set("MQTT_Settings", "led2StateTopic", self.mqttSettingsDict["led2StateTopic"])
            self.config.set("MQTT_Settings", "buttonPressCountTopic", self.mqttSettingsDict["buttonPressCountTopic"])

            with open(self.iniFilePath, 'w') as configfile:
                self.config.write(configfile)

            self.mqtt.mqttSettingsDict = self.mqttSettingsDict
            self.mqtt.connectServer()

            self.setSettingsButton.setDisabled(True)

            self.mqttConnected = False

            self.setSettingsButton.update()
            
            for i in range(0, 30):
                time.sleep(0.1)

                if self.mqtt.client.is_connected() == True:
                    self.mqttConnected = True
                    break
            
            self.setSettingsButton.setDisabled(False)

            if (self.mqttConnected == True):
                self.close()
            else:
                QMessageBox.critical(self, "Error", self.mqtt.errorMessage)
    
    def showOrHidePassword(self) -> None:
        """! This function display or hide password in password text box when user click password button.
        @param N/A
        @return N/A
        """
        if self.passwordTextbox.echoMode() == QLineEdit.Password:
            self.passwordTextbox.setEchoMode(QLineEdit.Normal)
            self.showPasswordButton.setIcon(self.hidePasswordIcon)
            self.showPasswordButton.setIconSize(self.hidePasswordIcon.actualSize(self.showPasswordButton.size()))
        else:
            self.passwordTextbox.setEchoMode(QLineEdit.Password)
            self.showPasswordButton.setIcon(self.showPasswordIcon)
            self.showPasswordButton.setIconSize(self.showPasswordIcon.actualSize(self.showPasswordButton.size()))

            
    def checkTextBoxes(self) -> bool:
        """! This function checks configurations from getting user.
        @param N/A
        @return TRUE: if all textboxes are valid.
                FALSE: any textbox is invalid.
        """
        errorMessages = ""

        if (self.serverAddressTextbox.text() == ""):
            errorMessages += "--MQTT Server Address can not be empty!\n\n"
        
        if(self.portTextbox.text() == ""):
            errorMessages += "--Port can not be empty!\n\n"
        
        if(self.usernameTextbox.text() == ""):
            errorMessages += "--Username can not be empty!\n\n"

        if(self.passwordTextbox.text() == ""):
            errorMessages += "--Pasword can not be empty!\n\n"
        
        if(self.systemStateTextbox.text() == ""):
            errorMessages += "--System State Topic can not be empty!\n\n"
        
        if(self.led1StateTextbox.text() == ""):
            errorMessages += "--Led 1 State Topic can not be empty!\n\n"
        
        if(self.led2StateTextbox.text() == ""):
            errorMessages += "--Led 2 State Topic can not be empty!\n\n"
        
        if(self.buttonPressCountTextbox.text() == ""):
            errorMessages += "--Button Press Count Topic can not be empty!\n\n"
        
        try:
            temp = int(self.portTextbox.text())
        except:
            errorMessages += "Port have to be integer!\n\n"

        if (errorMessages != ""):
            message = QMessageBox.critical(self, "Error", errorMessages)
            return False
        else:
            return True
    
    def closeEvent(self, event) -> None:
        """! This function is a callback function. It is called after close event triggered.
        Also, mqtt client not connect to the MQTT server, this function ignores the close event.
        @param event: This variable indicates close event object.
        @return N/A
        """
        if self.mqttConnected == True:
            event.accept()
        else:
            event.ignore()

# @}