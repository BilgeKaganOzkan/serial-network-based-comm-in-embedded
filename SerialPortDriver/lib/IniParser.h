#pragma once
#include "IniParserConfig.h"
#include "FailCode.h"

/**
 * @class IniParser
 * @brief IniParser class read "config.ini" file and parse to create Serial Port Config Data,
 * MQTT Client Config Data and Message Config Data, which types are respectively IniParserSerialPortConfig,
 * IniParserMqttClientConfig and IniParserMessageConfig.
 */
class IniParser
{
private:
    /**
     * @brief This variable keep ......
     */
    FailCode<IniParserFailCode> failCode;

    /**
     * @brief This variable keep Serial Port Config Data.
     */
    IniParserSerialPortConfig serialPortConfig;

    /**
     * @brief This variable keep MQTT Client Config Data.
     */
    IniParserMqttClientConfig mqttClientConfig;

    /**
     * @brief This variable keep Message Config Data.
     */
    IniParserMessageConfig messageConfig;
public:
    /**
     * @brief This function initialize all variables.
     * @param N/A
     * @return N/A
     */
    IniParser();

    /**
     * @brief This function start the reading and parsing processes.
     * @param N/A
     * @return N/A
     */
    void startParsing();

    /**
     * @brief This function return the Serial Port Config Data.
     * @param N/A
     * @return IniParserSerialPortConfig
     */
    IniParserSerialPortConfig& getSerialPortConfigData();

    /**
     * @brief This function return the MQTT Client Config Data.
     * @param N/A
     * @return IniParserMqttClientConfig
     */
    IniParserMqttClientConfig& getMqttClientConfigData();

    /**
     * @brief This function return the Message Config Data.
     * @param N/A
     * @return IniParserMessageConfig
     */
    IniParserMessageConfig& getMessageConfigData();
};
