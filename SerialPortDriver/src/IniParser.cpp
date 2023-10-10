/**
 * @file IniParser.cpp 
 * @author Bilge Kağan ÖZKAN
 */

#include "IniParser.h"
#include "IniParserConfig.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

/**
 * @brief This function initialize failCode variable.
 * @param N/A
 * @return N/A
 */
IniParser::IniParser()
{
    failCode = INIPARSER_OK;
}

/**
 * @brief This function start the reading and parsing processes.
 * @param N/A
 * @return N/A
 */
void IniParser::startParsing()
{
    boost::property_tree::ptree pt;
    
    try
    {
        boost::property_tree::ini_parser::read_ini("./config/config.ini", pt);
    }
    catch(const boost::wrapexcept<boost::property_tree::ini_parser::ini_parser_error>& e)
    {
        FAILCODE_SET_AND_EXIT(failCode, INI_FILE_CANNOT_OPEN);
    }
    
    try
    {
        serialPortConfig.portName = pt.get<std::string>("SerialConfig.SC_PORT_NAME");
        serialPortConfig.baudRate = pt.get<int>("SerialConfig.SC_BAUDRATE");
        serialPortConfig.dataBit = pt.get<int>("SerialConfig.SC_DATABIT");
        serialPortConfig.stopBit = pt.get<int>("SerialConfig.SC_STOPBIT");
        serialPortConfig.parityBit = pt.get<std::string>("SerialConfig.SC_PARITYBIT");

        mqttClientConfig.serverAdress = pt.get<std::string>("MqttConfig.MQTT_ADDRESS");
        mqttClientConfig.port = pt.get<int>("MqttConfig.MQTT_PORT");
        mqttClientConfig.topic1 = pt.get<std::string>("MqttConfig.MQTT_TOPIC_1");
        mqttClientConfig.topic2 = pt.get<std::string>("MqttConfig.MQTT_TOPIC_2");
        mqttClientConfig.topic3 = pt.get<std::string>("MqttConfig.MQTT_TOPIC_3");
        mqttClientConfig.topic4 = pt.get<std::string>("MqttConfig.MQTT_TOPIC_4");
        mqttClientConfig.id = pt.get<std::string>("MqttConfig.MQTT_ID");
        mqttClientConfig.qos = pt.get<int>("MqttConfig.MQTT_QOS");

        messageConfig.startCharacters = pt.get<std::string>("MessageFormat.MF_START_CHARACTERS");
        messageConfig.seperatorCharacters = pt.get<std::string>("MessageFormat.MF_SEPERATOR_CHARACTERS");
        messageConfig.endCharacters = pt.get<std::string>("MessageFormat.MF_END_CHARACTERS");
        messageConfig.seperatedDataCount = pt.get<int>("MessageFormat.MF_SEPERATED_DATA_COUNT");
    }
    catch(const boost::wrapexcept<boost::property_tree::ptree_bad_data>& e)
    {
        FAILCODE_SET_AND_EXIT(failCode, PARSING_ERROR);
    }
}

/**
 * @brief This function return the Serial Port Config Data.
 * @param N/A
 * @return IniParserSerialPortConfig
 */
IniParserSerialPortConfig& IniParser::getSerialPortConfigData()
{
    return serialPortConfig;
}

/**
 * @brief This function return the MQTT Client Config Data.
 * @param N/A
 * @return IniParserMqttClientConfig
 */
IniParserMqttClientConfig& IniParser::getMqttClientConfigData()
{
    return mqttClientConfig;
}

/**
 * @brief This function return the Message Config Data.
 * @param N/A
 * @return IniParserMessageConfig
 */
IniParserMessageConfig& IniParser::getMessageConfigData()
{
    return messageConfig;
}
