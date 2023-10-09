#pragma once
#include "IniParserConfig.h"
#include "FailCode.h"

class IniParser
{
private:
    FailCode<IniParserFailCode> failCode;
    IniParserSerialPortConfig serialPortConfig;
    IniParserMqttClientConfig mqttClientConfig;
    IniParserMessageConfig messageConfig;
public:
    IniParser();
    void startParsing();
    IniParserSerialPortConfig& getSerialPortConfigData();
    IniParserMqttClientConfig& getMqttClientConfigData();
    IniParserMessageConfig& getMessageConfigData();
};