/** \addtogroup Main
 * @{
 * @author Bilge Kağan ÖZKAN
 * @file main.cpp
 * @brief This file is main file.
 */

#include <string>
#include <iostream>
#include "MqttComm.h"
#include "FailCode.h"
#include "IniParser.h"
#include "IniParserConfig.h"
#include <vector>
#include "Message.h"
#include "SerialComm.h"

/**
 * @brief This function prints the SerialComm class fail code.
 * @param[in] failCode: SerialFailCodeType reference.
 * @return N/A
 */
void printSerialFailCode(SerialFailCodeType& failCode)
{
    switch (failCode)
    {
    case SERIALPORT_BAUDRATE_OUT_OF_RANGE:
        std::cout << "ERROR: The baudrate is out of range!!!" << std::endl;
        std::cout << "Please chech the config.ini file";
        break;
    case SERIALPORT_DATABIT_OUT_OF_RANGE:
        std::cout << "ERROR: The data bit is out of range!!!" << std::endl;
        std::cout << "Please chech the config.ini file";
        break;
    case SERIALPORT_PARITYBIT_OUT_OF_RANGE:
        std::cout << "ERROR: The parity bit is out of range!!!" << std::endl;
        std::cout << "Please chech the config.ini file";
        break;
    case SERIALPORT_STOPBIT_OUT_OF_RANGE:
        std::cout << "ERROR: The stop bit is out of range!!!" << std::endl;
        std::cout << "Please chech the config.ini file";
        break;
    case SERIALPORT_PORTNAME_IS_NONE:
        std::cout << "ERROR: Serial Port name is NONE!!!" << std::endl;
        std::cout << "Please chech the config.ini file";
        break;
    case SERIALPORT_READING_ERROR:
        std::cout << "ERROR: An error occured while reading from serial port!!!";
        break;
    case SERIALPORT_COULD_NOT_OPENED:
        std::cout << "ERROR: The serial port was not opened!!!";
        break;
    case SERIALPORT_COULD_NOT_CLOSED:
        std::cout << "ERROR: The serial port was not opened!!!";
        break;
    default:
        std::cout << "ERROR: " << failCode;
        break;
    }

    std::cout << std::endl << "The program is closing..." << std::endl;
}

/**
 * @brief This function prints the MqttComm class fail code.
 * @param[in] failCode: MqttFailCodeType reference.
 * @return N/A
 */
void printMqttFailCode(MqttFailCodeType& failCode)
{
    switch (failCode)
    {
    case MQTT_CONNECTION_ERROR:
        std::cout << "ERROR: An connection error occured.!!!" << std::endl;
        std::cout << "Please check server ip, port in the config.ini file and your internet connection";
        break;
    case MQTT_QOS_IS_INVALID:
        std::cout << "ERROR: QOS is invalid!!!" << std::endl;
        std::cout << "Please chech the config.ini file";
    default:
        std::cout << "ERROR: " << failCode;
        break;
    }

    std::cout << std::endl << "The program is closing..." << std::endl;
}

/**
 * @brief This function prints the IniParser class fail code.
 * @param[in] failCode: IniParserFailCode reference.
 * @return N/A
 */
void printIniParserFailCode(IniParserFailCode& failCode)
{
    switch (failCode)
    {
    case INIPARSER_INI_FILE_COULD_NOT_OPENED:
        std::cout << "ERROR: The  config.ini file can not opened!!!" << std::endl;
        std::cout << "Please check the config/config.ini path";
        break;
    case INIPARSER_PARSING_ERROR:
        std::cout << "ERROR: An convertation error occured.!!!" << std::endl;
        std::cout << "Please check contents of the config.ini file";
        break;
    default:
        std::cout << "ERROR: " << failCode;
        break;
    }

    std::cout << std::endl << "The program is closing..." << std::endl;
}

/**
 * @brief This function is main function of programme.
 * @param N/A
 * @return N/A
 */
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
        mqtt.connectServer(mqttClientConfigData);
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
        return -1;
	}
    catch(FailCode<SerialFailCodeType>& failCode)
    {
        printSerialFailCode(failCode.getValue());
        return -1;
    }
    catch(FailCode<MqttFailCodeType>& failCode)
    {
        printMqttFailCode(failCode.getValue());
        return -1;
    }
    catch(FailCode<IniParserFailCode>& failCode)
    {
        printIniParserFailCode(failCode.getValue());
        return -1;
    }
    catch(...)
    {
        std::cout << "unexpected and undefined error occured" << std::endl;
        return -1;
    }

    return 0;
}
