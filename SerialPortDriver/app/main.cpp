#include <string>
#include <iostream>
#include "MqttComm.h"
#include "FailCode.h"
#include "IniParser.h"
#include "IniParserConfig.h"
#include <vector>
#include "Message.h"
#include "SerialComm.h"

void printSerialFailCode(SerialFailCodeType& failCode)
{
    switch (failCode)
    {
    case NAME_IS_INVALID:
        std::cout << "ERROR: The port name is invalid!!!";
        break;
    case BAUDRATE_OUT_OF_RANGE:
        std::cout << "ERROR: The baudrate is out of range!!!";
        break;
    case DATABIT_OUT_OF_RANGE:
        std::cout << "ERROR: The data bit is out of range!!!";
        break;
    case PARITYBIT_OUT_OF_RANGE:
        std::cout << "ERROR: The parity bit is out of range!!!";
        break;
    case STOPBIT_OUT_OF_RANGE:
        std::cout << "ERROR: The stop bit is out of range!!!";
        break;
    case SERIALPORT_COULD_NOT_OPENED:
        std::cout << "ERROR: The serial port was not opened!!!";
        break;
    case NOT_OBTAINED_SERIALPORT_STATUS:
        std::cout << "ERROR: The serial port status was not obtained!!!";
        break;
    case PORTNAME_IS_NONE:
        std::cout << "ERROR: The port name is none!!!";
        break;
    case READING_ERROR:
        std::cout << "ERROR: An error occured while reading from serial port!!!";
        break;
    default:
        std::cout << "ERROR: " << failCode;
        break;
    }
}

void printMqttFailCode(MqttFailCodeType& failCode)
{
    switch (failCode)
    {
    case MQTT_NOT_CONNECTED:
        std::cout << "ERROR: The  MQTT Client is not connected to the server" << std::endl;
        std::cout << "Please use ConnectServer member function from MqttComm class";
        break;
    case MQTT_CONNECTION_ERROR:
        std::cout << "ERROR: An connection error occured.!!!" << std::endl;
        std::cout << "Please check server ip, port and your internet connection";
        break;
    default:
        std::cout << "ERROR: " << failCode;
        break;
    }
}

void printIniParserFailCode(IniParserFailCode& failCode)
{
    switch (failCode)
    {
    case INI_FILE_CANNOT_OPEN:
        std::cout << "ERROR: The  config.ini file can not opened!!!" << std::endl;
        std::cout << "Please check the config/config.ini path";
        break;
    case PARSING_ERROR:
        std::cout << "ERROR: An convertation error occured.!!!" << std::endl;
        std::cout << "Please check contents of the config.ini file";
        break;
    default:
        std::cout << "ERROR: " << failCode;
        break;
    }
}

int main() {   
    SerialComm serialComm;
    MqttComm mqtt;
    IniParser iniParser;
    Message message;

    IniParserSerialPortConfig serialPortConfigData;
    IniParserMqttClientConfig mqttClientConfigData;
    IniParserMessageConfig messageConfigData;

    try
	{
        iniParser.startParsing();
        
        serialPortConfigData = iniParser.getSerialPortConfigData();
        mqttClientConfigData = iniParser.getMqttClientConfigData();
        messageConfigData = iniParser.getMessageConfigData();

        serialComm.startCommunication(serialPortConfigData, mqtt);
        mqtt.ConnectServer(mqttClientConfigData);
        message.createMessageFormat(messageConfigData);

        while (true) {
            serialComm.readDataFromSerial(message);
            mqtt.publishMessage(message);
        }
	}
	catch(const std::exception& e)
	{
        std::cout << "Unexpected error occured!!!" << std::endl;
		std::cout << e.what() << std::endl;
	}
    catch(FailCode<SerialFailCodeType>& failCode)
    {
        printSerialFailCode(failCode.getValue());
    }
    catch(FailCode<MqttFailCodeType>& failCode)
    {
        printMqttFailCode(failCode.getValue());
    }
    catch(FailCode<IniParserFailCode>& failCode)
    {
        printIniParserFailCode(failCode.getValue());
    }
    catch(...)
    {
        std::cout << "unexpected and undefined error occured" << std::endl;
    }

    std::cout << std::endl << "The program is closing..." << std::endl;

    return 0;
}
