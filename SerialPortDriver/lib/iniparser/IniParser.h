/** \addtogroup IniParser
 * @{
 * @author Bilge Kağan ÖZKAN
 * @file IniParser.h
 * @defgroup IniParser
 * @brief This module includes IniParser class.
 * @verbatim
 * IniParser class reads the "config.ini" file and parses to create Serial Port Config Data,
 * MQTT Client Config Data and Message Config Data, which types are respectively IniParserSerialPortConfig,
 * IniParserMqttClientConfig and IniParserMessageConfig enum.
 * @endverbatim
 */

#pragma once

#include "IniParserConfig.h"
#include "FailCode.h"

/**
 * @class IniParser
 * @brief IniParser class reads the "config.ini" file and parses to create Serial Port Config Data,
 * MQTT Client Config Data and Message Config Data, which types are respectively IniParserSerialPortConfig,
 * IniParserMqttClientConfig and IniParserMessageConfig enum.
 */
class IniParser
{
private:
    FailCode<IniParserFailCode> failCode;       ///< This variable keeps objectified FailCode class with IniParserFailCode enum.
    IniParserSerialPortConfig serialPortConfig; ///< This variable keeps Serial Port Config Data.
    IniParserMqttClientConfig mqttClientConfig; ///< This variable keeps MQTT Client Config Data.
    IniParserMessageConfig messageConfig;       ///< This variable keeps Message Config Data.
    
public:
    /**
     * @brief This constructor initializes the failCode object.
     * @param N/A
     * @return N/A
     */
    IniParser();

    /**
     * @brief This is default destructor.
     * @param N/A
     * @return N/A
     */
    ~IniParser() = default;

    /**
     * @brief This function starts the reading and parsing processes.
     * @param N/A
     * @return throw INIPARSER_INI_FILE_COULD_NOT_OPENED: if config.ini file can not open.
     *         throw INIPARSER_PARSING_ERROR: if the content of config.ini file is wrong.
     */
    void startParsing();

    /**
     * @brief This function returns the Serial Port Config Data.
     * @param N/A
     * @return IniParserSerialPortConfig reference.
     */
    IniParserSerialPortConfig& getSerialPortConfigData();

    /**
     * @brief This function returns the MQTT Client Config Data.
     * @param N/A
     * @return IniParserMqttClientConfig reference.
     */
    IniParserMqttClientConfig& getMqttClientConfigData();

    /**
     * @brief This function returns the Message Config Data.
     * @param N/A
     * @return IniParserMessageConfig reference.
     */
    IniParserMessageConfig& getMessageConfigData();
};

/**@}*/
