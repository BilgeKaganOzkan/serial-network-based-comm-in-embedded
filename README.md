# Serial and Network Based Communication in Embedded Systems Project

The main ideas of the project are to change system satate, share system state using MQTT protocole and display it to users.

The project consists of 3 parts:
 - Embedded System
 - Serial Port Driver
 - GUI

*NOTE1: All the system only available for **linux***.
&nbsp;

<a id="note-2"></a> 
*NOTE2: For Serial Port Driver and GUI part dependencies, you only need to run install.sh file with the command below*
```
sudo sh install.sh
```
## Embedded System Part

The main ideas of the embedded system are to change system state whenever button is pressed and display these changes via 2 leds (led 1 is red, led 2 is green). Also, to send system status, led 1 status, led 2 status and button press counter in a specific message format using UART.

System status is given below as a table.

**System State Table:**
| System State | LED 1 | LED 2 |
|:------------:|:-----:|:-----:|
| 0            | Off   | Off   |
| 1            | Off   | On    |
| 2            | On    | Off   |
| 3            | On    | On    |

&nbsp;

Message format defined as following format:


**$$SystemState,LedState1,LedState2,ButtonPressCount****
  

Message format also is given below as a table.

**Message Format Table:**
| SCharacter Table     | Character |
|:--------------------:|:---------:|
| Start Characters     | $$        |
| Seperator Characters | ,         |
| End Characters       | **        |
| Data Characters      | On \ Off  |

Example for a message: **$$1,Off,On,5****

While project was realizing, **ESP32 Dev Board** was used for microcontrollers, **Bare Metal C** code style for programming. Also to catch the button press, **interrupt** method was used.

### Installation
Embedded systems codes are in EmbeddedApplication folder. To build and upload the codes to your own ESP32 Dev module:

#### First
You have to have Arduino IDE. If you don't have please run following commands:
```
sudo apt install zip
wget https://downloads.arduino.cc/arduino-ide/arduino-ide_2.2.1_Linux_64bit.zip
unzip arduino-ide_2.2.1_Linux_64bit.zip
cd arduino-ide_2.2.1_Linux_64bit
./arduino-ide
```
Arduino IDE should be opened .

#### Second

You have to esp32 library for Arduino IDE. If you don't have please follow the instructions:
- Open **File** -> **Prefarances** tabs.
Paste the URL below to **Additional boards manager URLs**
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
 - Click OK button.
 - Open **Tools** -> **Board** -> **Boards Manager**
 - Search **esp32**
 - Install **esp32 by Espressive System**
 - Open **Tools** -> **Board** -> **esp32** -> **ESP32 Dev Module**
 - Connect your own ESP32 Dev Module
 - Open **Tools** -> **Port**
 - Select the port which ESP32 DevModule was connected.

You are ready to build and upload EmbeddedApplication program to your own ESP32 Dev Boards.

### Using
if you want to change the default configuration the Embedded Application Project, you can make changes in **Configuration.h** file. More details are in **EmbeddedApplication/Configuration.h** file.

## Serial Port Drıver Part
The main ideas of Serial port driver are catch the messages from embedded system using serial port, parse messages as 4 data and send each data in different topic using MQTT protocol.
This part coding using **C++ language**.
While project was realizing, [Boost](#https://www.boost.org/) and [Paho Mqtt C++](#https://www.boost.org/) libraries were used.

### Installation
Your only need [NOTE 2](#note-2) 

### Using
To build and run this part, you only need to run runSerialPortDriver.sh with following command
```
sudo sh runSerialPortDriver.sh
```

All configurations are in **config/config.ini/** file. By changing these you can connect to your port whose embedded system was connected. By changing this file you can also changing serial port configurations, mqtt configurations and message format to be received.

## GUI Part
The main ideas of GUI are connect MQTT server and user defined 4 topics, collect the message from topics and show the messages to users visually.
This part was realized **python programming language** and [PyQt5](#https://pypi.org/project/PyQt5/) library.
### Installation
Your only need [NOTE 2](#note-2) 

### Using
To run this part, you only need to run runGUI.sh with following command
```
sudo sh runGUI.sh
```
After this, A window will be opened. in this window, user is able to set mqtt configurations. After click the connect button in this window, A main window will be opened and messages will be displayed to users visually.