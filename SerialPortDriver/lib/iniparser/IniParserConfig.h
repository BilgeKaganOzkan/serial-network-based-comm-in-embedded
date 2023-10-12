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
	std::string portName;  ///< This indicates the serial port name.
	int baudRate;          ///< This indicates the baudrate.
	int dataBit;           ///< This indicates the data bit length.
	int stopBit;           ///< This indicates the stop bit length.
	std::string parityBit; ///< This indicates the parity bit type.
};

/** @struct IniParserMqttClientConfig
 *  @brief MQTT Client Configuration Structure
 */
struct IniParserMqttClientConfig
{
    std::string serverAdress; ///< This indicates the MQTT Server ip adress.
    int port;                 ///< This indicates the MQTT Server port number.
    std::string username;     ///< This indicates the MQTT username
    std::string password;     ///< This indicates the MQTT password
    std::string topic1;       ///< This indicates the first MQTT topic.
    std::string topic2;       ///< This indicates the second MQTT topic.
    std::string topic3;       ///< This indicates the third MQTT topic.
    std::string topic4;       ///< This indicates the fourth MQTT topic.
    std::string id;           ///< This indicates the unique id for connect MQTT server.
    int qos;                  ///< This indicates the QOS number.
};

/** @struct IniParserMessageConfig
 *  @brief Message Structure To Be Send To The MQTT Server
 */
struct IniParserMessageConfig
{
    std::string startCharacters;     ///< This indicates the start characters of the message structure.
	std::string seperatorCharacters; ///< This indicates the seperator characters of the message structure.
	std::string endCharacters;       ///< This indicates the end characters of the message structure.
    int seperatedDataCount;          ///< This indicates the that how much data will be acquired after parsing the received message.
};

/**@}*/
