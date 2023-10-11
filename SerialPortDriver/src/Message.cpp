/**
 * @file Message.cpp
 * @author Bilge Kağan ÖZKAN
 */

#include "Message.h"
#include "IniParserConfig.h"
#include <vector>

/**
 * @brief This function resets counter variables and message variable.
 * @param N/A.
 * @return N/A
 */
void Message::reset()
{
    startCharacterCounter = 0;
    seperatorCharacterCounter = 0;
    endCharacterCounter = 0;
    seperatedDataCounter = 0;

    message.clear();
}

/**
 * @brief This function creates message format according to iniParserMessageConfig enum to check the data will be collected.
 * @param iniParserMessageConfig: This is message configuration reference whose type is IniParserMessageConfig enum.
 * @return N/A
 */
void Message::createMessageFormat(IniParserMessageConfig& iniParserMessageConfig)
{
    messageConfig.startCharacters = iniParserMessageConfig.startCharacters;
    messageConfig.seperatorCharacters = iniParserMessageConfig.seperatorCharacters;
    messageConfig.endCharacters = iniParserMessageConfig.endCharacters;
    messageConfig.seperatedDataCount = iniParserMessageConfig.seperatedDataCount;

    lenStartCharacter = messageConfig.startCharacters.length();
    lenSeperatorCharacter = messageConfig.seperatorCharacters.length();
    lenEndCharacter = messageConfig.endCharacters.length();

    startCharacterCounter = 0;
    seperatorCharacterCounter = 0;
    endCharacterCounter = 0;
    seperatedDataCounter = 0;

    message = "";
}

/**
 * @brief This function collects the data and check it.
 * @param data: This is to be collected data.
 * @return TRUE: If the data to be prepared is ready.
 * @return FALSE: If the data to be prepared is not ready.
 */
bool Message::acquireData(char& data)
{
    if ((startCharacterCounter < lenStartCharacter) && (seperatorCharacterCounter == 0) && (endCharacterCounter == 0) && (seperatedDataCounter == 0))
    {
        if (data == static_cast<char>(messageConfig.startCharacters[startCharacterCounter]))
        {
            ++startCharacterCounter;
        }
        else
        {
            reset();
        }
    }
    else if ((startCharacterCounter == lenStartCharacter) && ((seperatorCharacterCounter <= lenSeperatorCharacter)) && (endCharacterCounter == 0) && (seperatedDataCounter < messageConfig.seperatedDataCount))
    {
        if ((seperatorCharacterCounter < lenSeperatorCharacter) && (data == messageConfig.seperatorCharacters[seperatorCharacterCounter]))
        {
            message += data;
            ++seperatorCharacterCounter;

            if (seperatorCharacterCounter == lenSeperatorCharacter)
            {
                ++seperatedDataCounter;
                seperatorCharacterCounter = 0;
            }
        }
        else if ((seperatorCharacterCounter != 0) && (data != messageConfig.seperatorCharacters[seperatorCharacterCounter]))
        {
            reset();
        }
        else
        {
            if ((endCharacterCounter == 0) && (data == messageConfig.endCharacters[endCharacterCounter]))
            {
                ++seperatedDataCounter;
                ++endCharacterCounter;
            }
            else
            {
                message += data;
            }
        }
    }
    else if ((startCharacterCounter == lenStartCharacter) && (seperatorCharacterCounter == 0) && (endCharacterCounter < lenEndCharacter) && (seperatedDataCounter == messageConfig.seperatedDataCount))
    {
        if (data == messageConfig.endCharacters[endCharacterCounter])
        {
            ++endCharacterCounter;
        }
        else
        {
            reset();
        }

        if (endCharacterCounter == lenEndCharacter)
        {
            parsedMessage.clear();
            prepareMessage();
            reset();
            return true;
        }
    }
    else
    {
        reset();
    }

    return false;
}

/**
 * @brief This function prepares the message which will be send to the MQTT server.
 * @param N/A
 * @return N/A
 */
void Message::prepareMessage()
{
    int pos = 0;
    std::string subMessage;

    while (pos != std::string::npos) 
    {
        pos = message.find(messageConfig.seperatorCharacters);
        subMessage = message.substr(0, pos);
        parsedMessage.push_back(subMessage);
        message.erase(0, pos + lenSeperatorCharacter);
    }
}

/**
 * @brief This function returns the prepared message which will be send to the MQTT server.
 * @param N/A
 * @return std::vector<std::string>&: Prepared message vector reference.
 */
std::vector<std::string>& Message::getParsedMessage()
{
    return parsedMessage;
}
