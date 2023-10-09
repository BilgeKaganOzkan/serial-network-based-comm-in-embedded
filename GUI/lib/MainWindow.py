from PyQt5.QtWidgets import (
    QMainWindow, QApplication,
    QLabel, QAction, QStatusBar, 
    QWidget, QVBoxLayout, 
    QGridLayout, QDialog, QLineEdit, 
    QPushButton, QMessageBox
)
from PyQt5.QtGui import QFont
from PyQt5.QtCore import (Qt, pyqtSignal)
import configparser
from .Mqtt import Mqtt
import time

class MainWindow(QMainWindow):
    changeLabelsAndLightsSignal = pyqtSignal(dict)

    def __init__(self) -> None:
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

    def mqttSettingsButtonClick(self, s) -> None:
        mqttSettingsWindow = MqttSettingsWindow(self.mqtt)
        mqttSettingsWindow.exec_()
    
    def changeLabelsAndLights(self, messageDict: dict) -> None:
        isMessageContentRight = False
        sytemState = 0
        backGround = "background-image: url('./designs/systemState0.png');"

        if (messageDict["systemState"] == "0" and messageDict["led1Status"] == "Off" and messageDict["led2Status"] == "Off"):
            isMessageContentRight = True
            systemState = int(messageDict["systemState"])
            backGround = "background-image: url('./designs/systemState0.png');"
        elif (messageDict["systemState"] == "1" and messageDict["led1Status"] == "Off" and messageDict["led2Status"] == "On"):
            isMessageContentRight = True
            systemState = int(messageDict["systemState"])
            backGround = "background-image: url('./designs/systemState1.png');"
        elif (messageDict["systemState"] == "2" and messageDict["led1Status"] == "On" and messageDict["led2Status"] == "Off"):
            isMessageContentRight = True
            systemState = int(messageDict["systemState"])
            backGround = "background-image: url('./designs/systemState2.png');"
        elif (messageDict["systemState"] == "3" and messageDict["led1Status"] == "On" and messageDict["led2Status"] == "On"):
            isMessageContentRight = True
            systemState = int(messageDict["systemState"])
            backGround = "background-image: url('./designs/systemState3.png');"
        else:
            pass

        if (isMessageContentRight == True):
            self.setStyleSheet(backGround)
            self.systemStateLabel.setText("System State: " + messageDict["systemState"])
            self.led1Label.setText("Led 1 State: " + messageDict["led1Status"])
            self.led2Label.setText("Led 2 State: " + messageDict["led2Status"])
            self.buttonPressCountLabel.setText("Button Press Count: " + messageDict["buttonPressCount"])

class MqttSettingsWindow(QDialog):
    def __init__(self, mqtt: Mqtt):
        super().__init__()

        self.mqtt = mqtt

        self.mqttSettingsDict = {
            "serverAddress": "",
            "port": 0,
            "systemStateTopic": "",
            "led1StateTopic": "",
            "led2StateTopic": "",
            "buttonPressCountTopic": ""
        }

        self.iniFilePath = "config/mqttConfig.ini"

        self.config = configparser.ConfigParser()

        self.mqttConnected = False

        windowWidth = 400
        windowHeight = 360

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
        portLabel.setGeometry(labelPositionX,labelPositionY + labelPositionYSlide, labelWidth, labelHeight)

        systemStateTopicLabel = QLabel(container)
        systemStateTopicLabel.setText("System State Topic")
        systemStateTopicLabel.setFont(font)
        systemStateTopicLabel.setGeometry(labelPositionX, labelPositionY + labelPositionYSlide * 2, labelWidth, labelHeight)

        led1StateTopicLabel = QLabel(container)
        led1StateTopicLabel.setText("Led 1 State Topic")
        led1StateTopicLabel.setFont(font)
        led1StateTopicLabel.setGeometry(labelPositionX, labelPositionY + labelPositionYSlide * 3, labelWidth, labelHeight)

        led2StateTopicLabel = QLabel(container)
        led2StateTopicLabel.setText("Led 2 State Topic")
        led2StateTopicLabel.setFont(font)
        led2StateTopicLabel.setGeometry(labelPositionX, labelPositionY + labelPositionYSlide * 4, labelWidth, labelHeight)

        buttonPressCountTopicLabel = QLabel(container)
        buttonPressCountTopicLabel.setText("Button Press Count Topic")
        buttonPressCountTopicLabel.setFont(font)
        buttonPressCountTopicLabel.setGeometry(labelPositionX, labelPositionY + labelPositionYSlide * 5, labelWidth, labelHeight)

        self.serverAddressTextbox = QLineEdit(container)
        self.serverAddressTextbox.setGeometry(labelPositionX + labelWidth, labelPositionY, labelWidth, labelHeight)

        self.portTextbox = QLineEdit(container)
        self.portTextbox.setGeometry(labelPositionX + labelWidth ,labelPositionY + labelPositionYSlide, labelWidth, labelHeight)

        self.systemStateTextbox = QLineEdit(container)
        self.systemStateTextbox.setGeometry(labelPositionX + labelWidth, labelPositionY + labelPositionYSlide * 2, labelWidth, labelHeight)

        self.led1StateTextbox = QLineEdit(container)
        self.led1StateTextbox.setGeometry(labelPositionX + labelWidth, labelPositionY + labelPositionYSlide * 3, labelWidth, labelHeight)

        self.led2StateTextbox = QLineEdit(container)
        self.led2StateTextbox.setGeometry(labelPositionX + labelWidth, labelPositionY + labelPositionYSlide * 4, labelWidth, labelHeight)

        self.buttonPressCountTextbox = QLineEdit(container)
        self.buttonPressCountTextbox.setGeometry(labelPositionX + labelWidth, labelPositionY + labelPositionYSlide * 5, labelWidth, labelHeight)

        self.setSettingsButton = QPushButton(container)
        self.setSettingsButton.setGeometry(270, 300, 100, 30)
        self.setSettingsButton.setText("Connect")
        self.setSettingsButton.clicked.connect(self.setMqttSettings)

        self.layout = QVBoxLayout()
        self.layout.addWidget(container)
        self.setLayout(self.layout)

        self.readIniFile()
    
    def readIniFile(self):
        try:
            self.config.read(self.iniFilePath)

            self.mqttSettingsDict["serverAddress"] = self.config.get('MQTT_Settings', 'serverAddress')
            self.mqttSettingsDict["port"] = self.config.getint('MQTT_Settings', 'port')
            self.mqttSettingsDict["systemStateTopic"] = self.config.get('MQTT_Settings', 'systemStateTopic')
            self.mqttSettingsDict["led1StateTopic"] = self.config.get('MQTT_Settings', 'led1StateTopic')
            self.mqttSettingsDict["led2StateTopic"] = self.config.get('MQTT_Settings', 'led2StateTopic')
            self.mqttSettingsDict["buttonPressCountTopic"] = self.config.get('MQTT_Settings', 'buttonPressCountTopic')

            self.serverAddressTextbox.setText(self.mqttSettingsDict["serverAddress"])
            self.portTextbox.setText(str(self.mqttSettingsDict["port"]))
            self.systemStateTextbox.setText(self.mqttSettingsDict["systemStateTopic"])
            self.led1StateTextbox.setText(self.mqttSettingsDict["led1StateTopic"])
            self.led2StateTextbox.setText(self.mqttSettingsDict["led2StateTopic"])
            self.buttonPressCountTextbox.setText(self.mqttSettingsDict["buttonPressCountTopic"])

        except:
            self.mqttSettingsDict = {
            "serverAddress": "",
            "port": 0,
            "systemStateTopic": "",
            "led1StateTopic": "",
            "led2StateTopic": "",
            "buttonPressCountTopic": ""
            }

            self.serverAddressTextbox.setText("")
            self.portTextbox.setText("")
            self.systemStateTextbox.setText("")
            self.led1StateTextbox.setText("")
            self.led2StateTextbox.setText("")
            self.buttonPressCountTextbox.setText("")
    
    def setMqttSettings(self):
        checkedSuccess = self.checkTextBoxes()

        if (checkedSuccess):       
            self.mqttSettingsDict["serverAddress"] = self.serverAddressTextbox.text()
            self.mqttSettingsDict["port"] = int(self.portTextbox.text())
            self.mqttSettingsDict["systemStateTopic"] = self.systemStateTextbox.text()
            self.mqttSettingsDict["led1StateTopic"] = self.led1StateTextbox.text()
            self.mqttSettingsDict["led2StateTopic"] = self.led2StateTextbox.text()
            self.mqttSettingsDict["buttonPressCountTopic"] = self.buttonPressCountTextbox.text()

            self.config.remove_section("MQTT_Settings")
            self.config.add_section("MQTT_Settings")
            self.config.set("MQTT_Settings", "serverAddress", self.mqttSettingsDict["serverAddress"])
            self.config.set("MQTT_Settings", "port", str(self.mqttSettingsDict["port"]))
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
            
    
    def checkTextBoxes(self) -> bool:
        errorMessages = ""

        if (self.serverAddressTextbox.text() == ""):
            errorMessages += "--MQTT Server Address can not be empty!\n\n"
        
        if(self.portTextbox.text() == ""):
            errorMessages += "--Port can not be empty!\n\n"
        
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
    
    def closeEvent(self, event):
        if self.mqttConnected == True:
            event.accept()
        else:
            event.ignore()