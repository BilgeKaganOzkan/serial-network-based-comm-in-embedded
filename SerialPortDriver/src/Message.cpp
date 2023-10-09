#include "Message.h"
#include "IniParserConfig.h"
#include <vector>

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

void Message::reset()
{
    startCharacterCounter = 0;
    seperatorCharacterCounter = 0;
    endCharacterCounter = 0;
    seperatedDataCounter = 0;

    message.clear();
}

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
            prepareData();
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

void Message::prepareData()
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

std::vector<std::string>& Message::getParsedMessage()
{
    return parsedMessage;
}