/** \addtogroup Message
 * @{
 * @author Bilge Kağan ÖZKAN
 * @file Message.h
 * @defgroup Message
 * @brief This module includes Message class.
 * @verbatim
 * Message class collects the data which given to it, checks the collected data format and 
 * prepares the data which will be send to the MQTT server.
 * @endverbatim
 */

#pragma once

#include "MessageConfig.h"
#include <iostream>
#include "IniParserConfig.h"
#include <vector>

/**
 * @class Message
 * @brief Message class collects the data which given to it, checks the collected data format and 
 * prepares the data which will be send to the MQTT server.
 */
class Message
{
private:
    MessageConfig messageConfig;            ///< This variable keeps the MQTT message format.
    int lenStartCharacter;                  ///< This variable keeps the length of message format of start characters.
    int lenSeperatorCharacter;              ///< This variable keeps the length of message format of seperator characters.
    int lenEndCharacter;                    ///< This variable keeps the length of message format of end characters.
    int startCharacterCounter;              ///< This variable keeps the number of received start characters.
    int seperatorCharacterCounter;          ///< This variable keeps the number of received seperator characters.
    int endCharacterCounter;                ///< This variable keeps the number of received end characters.
    int seperatedDataCounter;               ///< This variable keeps how much raw data will be acquired after parsing to prepare message.
    std::string message;                    ///< This variable keeps the all received and not parsed data.
    std::vector<std::string> parsedMessage; ///< This variable keeps the parsed message.

    /**
     * @brief This function resets counter variables and message variable.
     * @param N/A.
     * @return N/A
     */
    void reset();
    
public:
    /**
     * @brief This is default constructor.
     * @param N/A
     * @return N/A
     */
    Message() = default;

    /**
     * @brief This is default destructor.
     * @param N/A
     * @return N/A
     */
    ~Message() = default;

    /**
     * @brief This function creates message format according to iniParserMessageConfig enum to check be collecting data.
     * @param iniParserMessageConfig: This is message configuration reference whose type is IniParserMessageConfig enum.
     * @return N/A
     */
    void createMessageFormat(IniParserMessageConfig& iniParserMessageConfig);

    /**
     * @brief This function collects the data and check it.
     * @param data: This is to be collected data.
     * @return TRUE: If the data to be prepared is ready.
     * @return FALSE: If the data to be prepared is not ready.
     */
    bool acquireData(char& data);

    /**
     * @brief This function prepares the message which will be send to the MQTT server.
     * @param N/A
     * @return N/A
     */
    void prepareMessage();

    /**
     * @brief This function returns the prepared message which will be send to the MQTT server.
     * @param N/A
     * @return std::vector<std::string>&: Prepared message vector reference.
     */
    std::vector<std::string>& getParsedMessage();
};

/**@}*/
