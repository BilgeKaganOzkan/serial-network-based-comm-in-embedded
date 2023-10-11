/** \addtogroup IniParser
 * @{
 * @author Bilge Kağan ÖZKAN
 * @file IniParserConfig.h
 * @brief This file includes the ini parser 'failCode' types and configuration structures for IniParser class.
 */

#pragma once

#include <iostream>
#include "SerialConfig.h"

/** @brief Failcode Types
 */
enum IniParserFailCode
{
    INIPARSER_OK = 0,                        ///< This indicates that the process was successful.
    INIPARSER_INI_FILE_COULD_NOT_OPENED = 1, ///< This indicates that config.ini file could not opened.
    INIPARSER_PARSING_ERROR = 2              ///< This indicates that an parsing error occured. For example, config.ini file is corrupt.
};

/** @struct IniParserSerialPortConfig
 *  @brief Serial Port Configuration Structure
 */
struct IniParserSerialPortConfig
{
	std::string portName;  ///< This indicates serial port name.
	int baudRate;          ///< This indicates baudrate.
	int dataBit;           ///< This indicates data bit length.
	int stopBit;           ///< This indicates stop bit length.
	std::string parityBit; ///< This indicates parity bit type.
};

/** @struct IniParserMqttClientConfig
 *  @brief MQTT Client Configuration Structure
 */
struct IniParserMqttClientConfig
{
    std::string serverAdress; ///< This indicates MQTT Server ip adress.
    int port;                 ///< This indicates MQTT Server port number.
    std::string topic1;       ///< This indicates first MQTT topic.
    std::string topic2;       ///< This indicates second MQTT topic.
    std::string topic3;       ///< This indicates third MQTT topic.
    std::string topic4;       ///< This indicates fourth MQTT topic.
    std::string id;           ///< This indicates unique id for connect MQTT server.
    int qos;                  ///< This indicates QOS number.
};

/** @struct IniParserMessageConfig
 *  @brief Message Structure To Be Send To The MQTT Server
 */
struct IniParserMessageConfig
{
    std::string startCharacters;     ///< This indicates start characters of the message structure.
	std::string seperatorCharacters; ///< This indicates seperator characters of the message structure.
	std::string endCharacters;       ///< This indicates end characters of the message structure.
    int seperatedDataCount;          ///< This indicates that how much data will be acquired after parsing the received message.
};

/**@}*/
