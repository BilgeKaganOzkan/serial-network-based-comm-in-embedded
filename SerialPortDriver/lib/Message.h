#pragma once
#include "MessageConfig.h"
#include <iostream>
#include "IniParserConfig.h"
#include <vector>

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
    void reset();
public:
    void createMessageFormat(IniParserMessageConfig& iniParserMessageConfig);
    bool acquireData(char& data);
    void prepareData();
    std::vector<std::string>& getParsedMessage();
};