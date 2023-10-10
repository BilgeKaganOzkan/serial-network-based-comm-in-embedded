/** \addtogroup Message
 * @{
 * @author Bilge Kağan ÖZKAN
 * @file MessageConfig.h
 * @brief This file have Message Structure for IniParser class.
 */

#pragma once
#include <iostream>

/** @struct MessageConfig
 *  @brief Message Structure To Be Send To The MQTT Server
 */
struct MessageConfig
{
    std::string startCharacters; // This indicates start characters of the message structure.
	std::string seperatorCharacters; // This indicates seperator characters of the message structure.
	std::string endCharacters; // This indicates end characters of the message structure.
    int seperatedDataCount; // This indicates that how many data will be acquired after parsing the reveived message.
};

/**@}*/
