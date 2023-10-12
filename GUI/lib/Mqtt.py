"""!
\addtogroup Mqtt
@{
@author Bilge Kağan ÖZKAN
@file Mqtt.py
@defgroup Mqtt
@brief This module includes Mqtt class.
@verbatim
Mqtt class receives the message, parses the message and update the Main Window.
@endverbatim
"""

from paho.mqtt import client as mqtt
import getmac

class Mqtt:
    """! This class receives the message, parses the message and update the Main Window."""

    def __init__(self, mainWindow) -> None:
        """! This function initialize all variables and create client object from paho mqtt library.
        @param mainWindow: This variable indicates MainWindow object.
        @return N/A
        """
        super().__init__()

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
        self.errorMessage = ""

        macAddress = getmac.get_mac_address()
        cleanMacAddress = macAddress.replace(":", "").replace("-", "").lower()

        self.id = "mqtt_client_" + cleanMacAddress

        self.client = mqtt.Client(self.id)
        self.client.on_connect = self.onConnect
        self.client.on_disconnect = self.onDisConnect
        self.client.on_message = self.onMessage

        self.mainWindow = mainWindow

        self.receivedMessageDict = {
            "systemState": "",
            "led1Status": "",
            "led2Status": "",
            "buttonPressCount": ""
        }

        self.systemStateReceived = False
        self.led1StatusReceived = False
        self.led2StatusReceived = False
        self.buttonPressCountReceived = False
    
    def onConnect(self, client, userdata, flags, rc) -> None:
        """! This function is a callback function of client object. It calls after client connect to the MQTT server.
        @param[in] client: This variable indicates client object.
        @param[in] userdata: This variable indicates user data.
        @param[in] flags: This variable indicates transmitted connection flags from MQTT server.
        @param[in] rc: This variable indicates return code.
        @return N/A
        """
        if rc == 0:
            print("Connected to MQTT Broker!")
            self.subscribeTopics()
        else:
            errorMessage += f"Failed to connect, return code {rc}\n"
            print(f"Failed to connect, return code {rc}\n")
    
    def onDisConnect(self, client, userdata, rc) -> None:
        """! This function is a callback function of client object. It calls after client disconnect to the MQTT server.
        @param[in] client: This variable indicates client object.
        @param[in] userdata: This variable indicates user data.
        @param[in] rc: This variable indicates return code.
        @return N/A
        """
        print("Connection lost!!!")
        
        self.client.reconnect()

        if (self.client.is_connected == True):
            print("Reconnected to the MQTT server")
        else:
            print("Can not reconnected to the MQTT server")

    def onMessage(self, client, userdata, msg) -> None:
        """! This function is a callback function of client object. It calls after client disconnect to the MQTT server.
        @param[in] client: This variable indicates client object.
        @param[in] userdata: This variable indicates user data.
        @param[in] rc: This variable indicates return code.
        @return N/A
        """
        receivedMessage = msg.payload.decode()

        if (msg.topic == self.mqttSettingsDict["systemStateTopic"]):
            self.receivedMessageDict["systemState"] = receivedMessage
            self.systemStateReceived = True
        elif (msg.topic == self.mqttSettingsDict["led1StateTopic"]):
            self.receivedMessageDict["led1Status"] = receivedMessage
            self.led1StatusReceived = True
        elif (msg.topic == self.mqttSettingsDict["led2StateTopic"]):
            self.receivedMessageDict["led2Status"] = receivedMessage
            self.led2StatusReceived = True
        elif (msg.topic == self.mqttSettingsDict["buttonPressCountTopic"]):
            self.receivedMessageDict["buttonPressCount"] = receivedMessage
            self.buttonPressCountReceived = True
        else:
            pass

        if ((self.systemStateReceived == True) 
            and (self.led1StatusReceived == True) 
            and (self.led2StatusReceived == True) 
            and (self.buttonPressCountReceived == True)
            ):
            
            self.resetReceivedControls()

            print("All messages were received successfully.\nSystem state is changing.")

            self.mainWindow.changeLabelsAndLightsSignal.emit(self.receivedMessageDict)

            print("System state was changed successfully.")
            print(f"New system state {self.receivedMessageDict['systemState']} led 1 status {self.receivedMessageDict['led1Status']} led 2 status {self.receivedMessageDict['led2Status']} button press counter {self.receivedMessageDict['buttonPressCount']}.\n\n")

            self.receivedMessageDict = {
                "systemState": "",
                "led1Status": "",
                "led2Status": "",
                "buttonPressCount": ""
            }
    
    def resetReceivedControls(self) -> None:
        """! This function reset all received control variables.
        @param N/A
        @return N/A
        """
        self.systemStateReceived = False
        self.led1StatusReceived = False
        self.led2StatusReceived = False
        self.buttonPressCountReceived = False

    def connectServer(self) -> None:
        """! This function connect to the MQTT server.
        @param N/A
        @return N/A
        """
        try:
            self.errorMessage = ""
            self.client.username_pw_set(self.mqttSettingsDict["username"], self.mqttSettingsDict["password"])
            self.client.connect(self.mqttSettingsDict["serverAddress"], self.mqttSettingsDict["port"])
            self.subscribeTopics()
        except Exception as e:
            self.errorMessage = "An error occured. Please check MQTT Server Address, Port and your internet connection\n" + str(e) + "\n"
            print("An error occured. Please check MQTT Server Address, Port and your internet connection\n" + str(e))
    
    def subscribeTopics(self) -> None:
        """! This function subscribe all topics which are in mqttConfig.ini file and start the communication loop.
        @param N/A
        @return N/A
        """
        self.client.subscribe([(self.mqttSettingsDict["systemStateTopic"], 0), (self.mqttSettingsDict["led1StateTopic"], 0), (self.mqttSettingsDict["led2StateTopic"], 0), (self.mqttSettingsDict["buttonPressCountTopic"], 0)])
        self.client.loop_start()

# @}
