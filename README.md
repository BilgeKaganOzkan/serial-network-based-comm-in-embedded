# Serial and Network Based Communication in Embedded Systems Project

The main ideas of the project are to change system state, share system state using MQTT protocole and display it to users.

The project consists of 3 parts:
 - Embedded System
 - Serial Port Driver
 - GUI

*NOTE1: All the system only available for **linux***.
&nbsp;

<a id="install"></a> 
### Installation The Project
You can install the project and install Serial Port Driver and GUI part dependencies using following commands:
```
git clone https://github.com/BilgeKaganOzkan/serial-network-based-comm-in-embedded.git
cd serial-network-based-comm-in-embedded/
sudo sh install.sh
```
NOTE: If **installations/** folder was not removed automatically, you can delete it.

### Testing The Project
To test the project you have to have [Mosquitto](https://mosquitto.org/). If you don't have, you can instal using following commands:
```
sudo apt-get update
sudo apt-get install -y mosquitto
sudo apt-get install -y mosquitto-clients
sudo systemctl start mosquitto
sudo systemctl enable mosquitto
```
After this, if you want to using to the mosquitto only with user name and password, please follow the instructions:

First, you have to define username and password in passwd file using following command:
```
mosquitto_passwd -c /etc/mosquitto/passwd your_username
```
Second, you have to configure **mosquitto.conf** file using following command:
```
sudo nano /etc/mosquitto/mosquitto.conf
```
Third, you have to paste command below to end of the file. **IMPORTANT NOTE: There have to be new line characters between all words and  must not any space character end of line in mosquitto.conf file** 
```
allow_anonymous false

password_file /etc/mosquitto/mosquitto.conf
```
Finally, you have to save and exit this file and restart the mosquitto service using following command:
```
sudo systemctl restart mosquitto
```
**NOTE2: For Serial Port Driver and GUI part dependencies, you only need to run install.sh file.**
## Embedded System Part

The main ideas of the embedded system part are to change system state whenever button is pressed and display these changes via 2 leds (led 1 is red, led 2 is green). Also, to send system status, led 1 status, led 2 status and button press counter in a specific message format using UART. The specific message format is defined as **$$SystemState,LedState1,LedState2,ButtonPressCount**** Example for a message: **$$1,Off,On,5****

System status is given below as a table.

**System State Table:**
| System State | LED 1 | LED 2 |
|:------------:|:-----:|:-----:|
| 0            | Off   | Off   |
| 1            | Off   | On    |
| 2            | On    | Off   |
| 3            | On    | On    |


Message format also is given below as a table.

**Message Format Table:**
| Character Type       | Characters|
|:--------------------:|:---------:|
| Start Characters     | $$        |
| Seperator Characters | ,         |
| End Characters       | **        |
| Data Characters      | On \ Off  |


While project was realizing, **ESP32 Dev Board** was used for microcontrollers, **Bare Metal C** code style for programming. Also to catch the button press, **interrupt** method was used.

### Installation
Embedded systems codes are in EmbeddedApplication folder. To build and upload the codes to your own ESP32 Dev module:

#### First
You have to have Arduino IDE. If you don't have, please run following commands:
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
- Open **File** -> **Preferences** tabs.
Paste the URL below to the **Additional boards manager URLs** text box
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
 - Click OK button.
 - Open **Tools** -> **Board** -> **Boards Manager**
 - Search **esp32**
 - Install **esp32 by Espressive System**
 - Open **Tools** -> **Board** -> **esp32** -> **ESP32 Dev Module**
 - Connect your own ESP32 Dev Module to your computer using USB port.
 - Open **Tools** -> **Port**
 - Select the port which ESP32 Dev Module was connected.

You are ready to build and upload EmbeddedApplication program to your own ESP32 Dev Board.

### Using
if you want to change the default configuration the Embedded Application Project, you can make changes in **Configuration.h** file. More details are in **EmbeddedApplication/Configuration.h** file.

## Serial Port Driver Part
The main ideas of Serial port driver are catch the messages from embedded system using serial port, parse messages as 4 data and send each data in different topic using MQTT protocol.
This part coding using **C++ language**.
While project was realizing, [Boost](https://www.boost.org/) and [Paho Mqtt C++](https://github.com/eclipse/paho.mqtt.cpp) libraries were used.

### Installation
Your only need is [Installation](#install) or [Installation Without install.sh](#without-install) 

### Using
To build and run this part, you only need to run runSerialPortDriver.sh with following command
```
sudo sh runSerialPortDriver.sh
```
After this command, program was created in **bin/SerialPortDriver** path and the build folder will be deleted.

If you don't want to script file you can use following commands to build and run Serial Port:
```
cmake -S . -B build/
cmake --build build/
sudo ./bin/SerialPortDriver
```

All configurations are in **config/config.ini/** file. By changing these you can connect to your port whose embedded system was connected. By changing this file you can also change the serial port configurations, mqtt configurations and message format to be received. Also, thanks to changing config.ini file features, you don't have to rebuild the codes.

## GUI Part
The main ideas of GUI are connect MQTT server and user defined 4 topics, collect the message from topics and show the messages to users visually.
This part was realized via **Python language** and [PyQt5](https://pypi.org/project/PyQt5/) library.
### Installation
Your only need is [Installation](#install) or [Installation Without install.sh](#without-install)

### Using
To run this part, you only need to run runGUI.sh with following command:
```
sh runGUI.sh
```
If you don't want to script file you can use following commang to run GUI:
```
sudo python3 main.py
```
After this, A window will be opened. In this window, user is able to set mqtt configurations. After click the connect button in this window, A main window will be opened and messages will be displayed to users visually.

# Documentation
**Documents/GUI_Documents/** and **Documents/SerialPortDriver_Documents/** folders were created by doxygen to learn more code details and code connections. You can see doxygen outputs using run **Documents/<part_name>_Documents/html/index.html** in a web browser

If you change codes, you can use **doxygen** to generate new doxygen outputs and using the commands below in <part_name> folder
```
doxygen Doxyfile
```
After this, **<part_name>_Documents/** folder will be created. You can display the **<part_name>_Documents/index.html** document in a web browser.

Also, system diagram, esp32 circuit diagram and real life photos are in the **Documents** folder.

NOTE: **GUI/DoxygenFiles/** and **SerialPortDriver/DoxygenFiles/** only use for doxygen.

<a id="without-install"></a> 
# Installation Without Using install.sh
If you receive an error after using install.sh or when you run the programs about libraries, please apply following instructions.
At first for all downloads to be downloaded, run commands below. Thanks to this step, you can access all downloaded files from **installations**.
```
sudo mkdir installations/
cd installations/
```
*NOTE: After installation all steps, you can delete installations/ folder*
## Boost Library installation
First, you have to install dependencies using following commands
```
sudo apt update -y && sudo apt upgrade -y
sudo apt-get install -y build-essential g++ python3-dev autotools-dev libicu-dev libbz2-dev libboost-all-dev
```

Second, you have to download Boost library version 1.80.0 and extract it using following commands:
```
sudo wget https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.gz
sudo tar xvf boost_1_80_0.tar.gz
```
Third, you have to go to boost_1_80_0 directrory and built it using following commands:
```
cd boost_1_80_0
sudo ./bootstrap.sh --prefix=/usr/
```
After this commands, if all instructions above were successfully completed, **b2 file must be created**.

Finally, you have to run **b2** file using following command:
```
sudo ./b2 install
```
In this step, if it was successfully completed, boost library must be installed. You should go to the parent folder directory for another installation steps using following command:
```
cd ..
```

## Paho Mqtt C++ Library Installation
[Paho Mqtt C++](https://github.com/eclipse/paho.mqtt.cpp) have a dependency on [Paho Mqtt C](https://github.com/eclipse/paho.mqtt.c) library. Therefore, before installing Paho Mqtt C++ library, you have to install Paho Mqtt C library using following steps.

### Paho Mqtt C Library Installation
First, you have to install dependencies using following commands
```
sudo apt-get install -y libssl-dev
sudo apt-get install -y build-essential gcc make cmake cmake-gui cmake-curses-gui
sudo apt-get install -y doxygen graphviz
```

Second, you have to download Paho Mqtt C library and go to paho.mqtt.c directrory using following command:
```
sudo git clone https://github.com/eclipse/paho.mqtt.c.git
cd paho.mqtt.c
```

Third, you have to prepare cmake files in build folder using following command:
```
cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
```
Finally, you have to build and install the library using following commands:
```
cmake --build build/ --target install
sudo ldconfig
```
You should go to the parent folder directory for another installation steps using following command:
```
cd ..
```

### Paho Mqtt C++ Library Installation
First, you have to download Paho Mqtt C++ library and go to paho.mqtt.cpp directrory using following command:
```
sudo git clone https://github.com/eclipse/paho.mqtt.cpp
cd paho.mqtt.cpp
```

Second, you have to prepare cmake files in build folder using following command:
```
cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON \
    -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
```
Finally, you have to build and install the library using following commands:
```
cmake --build build/ --target install
sudo ldconfig
```
You should go to the parent folder directory for another installation steps using following command:
```
cd ..
```

## Python3 Libraries Installation
First, you have to install pip3 for python3 using following command:
```
sudo apt install -y python3-pip
```
And then, you have to install all libraries for GUI part using following command:
```
sudo apt install -y python3-pip
sudo apt install -y pyqt5-dev-tools pyqt5-dev
pip3 install paho-mqtt
pip3 install pyserial
pip3 install get-mac
```

