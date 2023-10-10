#pragma once
#include <iostream>
#include "SerialConfig.h"

/*Failcode Types */
enum IniParserFailCode
{
    INIPARSER_OK = 0, // This indicates that the process was successful.
    INI_FILE_CANNOT_OPEN = 1, // This indicates that Config.ini file could not opened.
    PARSING_ERROR = 2 // This indicates that an parsing error occured. For example, config.ini file is corrupt.
};

/*Serial Port Configuration Structure */
struct IniParserSerialPortConfig
{
	std::string portName; // This indicates serial port name.
	int baudRate; // This indicates baudrate.
	int dataBit; // This indicates data bit length.
	int stopBit; // This indicates stop bit length.
	std::string parityBit; // This indicates parity bit type.
};

/* MQTT Client Configuration Structure */
struct IniParserMqttClientConfig
{
    std::string serverAdress; // This indicates MQTT Server ip adress.
    int port; // This indicates MQTT Server port number.
    std::string topic1; // This indicates first MQTT topic.
    std::string topic2; // This indicates second MQTT topic.
    std::string topic3; // This indicates third MQTT topic.
    std::string topic4; // This indicates fourth MQTT topic.
    std::string id; // This indicates unique id for connect MQTT server.
    int qos; // This indicates QOS number.
};

/* Message Structure To Be Send To The MQTT Server*/
struct IniParserMessageConfig
{
    std::string startCharacters; // This indicates start characters of the message structure.
	std::string seperatorCharacters; // This indicates seperator characters of the message structure.
	std::string endCharacters; // This indicates end characters of the message structure.
    int seperatedDataCount; // This indicates that how many data will be acquired after parsing the reveived message.
};
