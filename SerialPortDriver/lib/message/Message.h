/** \addtogroup Message
 * @{
 * @author Bilge Kağan ÖZKAN
 * @file Message.h
 * @defgroup Message
 * @brief This module has Message class.
 */

#pragma once
#include "MessageConfig.h"
#include <iostream>
#include "IniParserConfig.h"
#include <vector>

/**
 * @class Message
 * @brief Message class collect the data which given to it, check the collected data format and 
 * prepare the data which will be send to the MQTT server.
 */
class Message
{
private:
    MessageConfig messageConfig;
    int lenStartCharacter;
    int lenSeperatorCharacter;
    int lenEndCharacter;
    int startCharacterCounter;
    int seperatorCharacterCounter;
    int endCharacterCounter;
    int seperatedDataCounter;
    std::string message;
    std::vector<std::string> parsedMessage;

    /**
     * @brief This function reset counter variables and message variable.
     * @param N/A.
     * @return N/A
     */
    void reset();
    
public:
    /**
     * @brief This function create message format according to iniParserMessageConfig to check be collecting data.
     * @param iniParserMessageConfig: This is message configuration referance whose type is IniParserMessageConfig.
     * @return N/A
     */
    void createMessageFormat(IniParserMessageConfig& iniParserMessageConfig);

    /**
     * @brief This function collect the data and check it.
     * @param data: This is to be collected data.
     * @return TRUE: If the data to be prepared to be ready.
     * @return FALSE: If the data to be prepared to be not ready.
     */
    bool acquireData(char& data);

    /**
     * @brief This function prepare the data which will be send to the MQTT server.
     * @param N/A
     * @return N/A
     */
    void prepareData();

    /**
     * @brief This function return the prepared the data which will be send to the MQTT server.
     * @param N/A
     * @return std::vector<std::string>&: Prepared data vector referance.
     */
    std::vector<std::string>& getParsedMessage();
};

/**@}*/
