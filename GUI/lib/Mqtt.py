from paho.mqtt import client as mqtt
import getmac

class Mqtt:
    def __init__(self, window) -> None:
        super().__init__()

        self.mqttSettingsDict = {
            "serverAddress": "",
            "port": 0,
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

        self.window = window

        self.messageDict = {
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
        if rc == 0:
            print("Connected to MQTT Broker!")
            self.subscribeTopics()
        else:
            errorMessage += f"Failed to connect, return code {rc}\n"
            print(f"Failed to connect, return code {rc}\n")
    
    def onDisConnect(self, client, userdata, rc):
        print("Connection lost!!!")
        
        self.client.reconnect()

        if (self.client.is_connected == True):
            print("Reconnected to the MQTT server")
        else:
            print("Can not reconnected to the MQTT server")

    def onMessage(self, client, userdata, msg) -> None:
        receivedMessage = msg.payload.decode()

        if (msg.topic == "deneme1"):
            self.messageDict["systemState"] = receivedMessage
            self.systemStateReceived = True
        elif (msg.topic == "deneme2"):
            self.messageDict["led1Status"] = receivedMessage
            self.led1StatusReceived = True
        elif (msg.topic == "deneme3"):
            self.messageDict["led2Status"] = receivedMessage
            self.led2StatusReceived = True
        elif (msg.topic == "deneme4"):
            self.messageDict["buttonPressCount"] = receivedMessage
            self.buttonPressCountReceived = True
        else:
            pass

        if ((self.systemStateReceived == True) 
            and (self.led1StatusReceived == True) 
            and (self.led2StatusReceived == True) 
            and (self.buttonPressCountReceived == True)
            ):
            
            self.receivedControls()

            #self.window.changeLabelsAndLights(self.messageDict)
            self.window.changeLabelsAndLightsSignal.emit(self.messageDict)

            self.messageDict = {
                "systemState": "",
                "led1Status": "",
                "led2Status": "",
                "buttonPressCount": ""
            }

        print(receivedMessage)
    
    def receivedControls(self):
        self.systemStateReceived = False
        self.led1StatusReceived = False
        self.led2StatusReceived = False
        self.buttonPressCountReceived = False

    def connectServer(self) -> None:
        try:
            self.errorMessage = ""
            self.client.connect(self.mqttSettingsDict["serverAddress"], self.mqttSettingsDict["port"])
            self.subscribeTopics()
        except Exception as e:
            self.errorMessage = "An error occured. Please check MQTT Server Address, Port and your internet connection\n" + str(e) + "\n"
            print("An error occured. Please check MQTT Server Address, Port and your internet connection\n" + str(e))
    
    def subscribeTopics(self) -> None:
        self.client.subscribe([(self.mqttSettingsDict["systemStateTopic"], 0), (self.mqttSettingsDict["led1StateTopic"], 0), (self.mqttSettingsDict["led2StateTopic"], 0), (self.mqttSettingsDict["buttonPressCountTopic"], 0)])
        self.client.loop_start()