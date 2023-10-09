#pragma once
#include <iostream>
#include "SerialConfig.h"

enum IniParserFailCode
{
    INIPARSER_OK = 0,
    INI_FILE_CANNOT_OPEN = 1,
    PARSING_ERROR = 2
};

struct IniParserSerialPortConfig
{
	std::string portName;
	int baudRate;
	int dataBit;
	int stopBit;
	std::string parityBit;
};

struct IniParserMqttClientConfig
{
    std::string serverAdress;
    int port;
    std::string topic1;
    std::string topic2;
    std::string topic3;
    std::string topic4;
    std::string id;
    int qos;
};

struct IniParserMessageConfig
{
    std::string startCharacters;
	std::string seperatorCharacters;
	std::string endCharacters;
    int seperatedDataCount;
};