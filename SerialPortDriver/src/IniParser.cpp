/**
 * @file IniParser.cpp 
 * @author Bilge Kağan ÖZKAN
 */

#include "IniParser.h"
#include "IniParserConfig.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

/**
 * @brief This constructor initializes the failCode object.
 * @param N/A
 * @return N/A
 */
IniParser::IniParser()
{
    failCode = INIPARSER_OK;
}

/**
 * @brief This function starts the reading and parsing processes.
 * @param N/A
 * @return throw INIPARSER_INI_FILE_COULD_NOT_OPENED: if config.ini file can not open.
 *         throw INIPARSER_PARSING_ERROR: if the content of config.ini file is wrong.
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
        FAILCODE_SET_AND_EXIT(failCode, INIPARSER_INI_FILE_COULD_NOT_OPENED);
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
        mqttClientConfig.username = pt.get<std::string>("MqttConfig.MQTT_USERNAME");
        mqttClientConfig.password = pt.get<std::string>("MqttConfig.MQTT_PASSWORD");
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
        FAILCODE_SET_AND_EXIT(failCode, INIPARSER_PARSING_ERROR);
    }
}

/**
 * @brief This function returns the Serial Port Config Data.
 * @param N/A
 * @return IniParserSerialPortConfig reference.
 */
IniParserSerialPortConfig& IniParser::getSerialPortConfigData()
{
    return serialPortConfig;
}

/**
 * @brief This function returns the MQTT Client Config Data.
 * @param N/A
 * @return IniParserMqttClientConfig reference.
 */
IniParserMqttClientConfig& IniParser::getMqttClientConfigData()
{
    return mqttClientConfig;
}

/**
 * @brief This function returns the Message Config Data.
 * @param N/A
 * @return IniParserMessageConfig reference.
 */
IniParserMessageConfig& IniParser::getMessageConfigData()
{
    return messageConfig;
}
