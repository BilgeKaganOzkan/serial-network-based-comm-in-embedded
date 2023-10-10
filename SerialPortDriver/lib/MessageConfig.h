#pragma once
#include <iostream>

/* Message Structure To Be Send To The MQTT Server*/
struct MessageConfig
{
    std::string startCharacters; // This indicates start characters of the message structure.
	std::string seperatorCharacters; // This indicates seperator characters of the message structure.
	std::string endCharacters; // This indicates end characters of the message structure.
    int seperatedDataCount; // This indicates that how many data will be acquired after parsing the reveived message.
};
