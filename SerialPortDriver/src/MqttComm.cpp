/**
 * @file MqttComm.cpp
 * @author Bilge Kağan ÖZKAN
 */

#include <iostream>
#include <mqtt/client.h>
#include "MqttComm.h"
#include "FailCode.h"
#include "IniParserConfig.h"
#include <vector>
#include "Message.h"

/**
 * @brief This function initialize the isConnect variable and failCode pointer.
 * @param N/A
 * @return N/A
 */
MqttComm::MqttComm()
{
    isConnected = false;
    failCode = MQTT_OK;
    mqttClient = nullptr;
}

/**
 * @brief This function delete failCode pointer.
 * @param N/A
 * @return N/A
 */
MqttComm::~MqttComm()
{
    delete mqttClient;
}

/**
 * @brief This function convert IniParserMqttClientConfig Structure type to MqttConfig Structure type.
 * @param[in] mqttConfigData: IniParser MQTT Client Configuration Structure.
 * @return N/A
 */
void MqttComm::convertIniParserDataToMqttConfig(IniParserMqttClientConfig& mqttConfigData)
{
    std::string serverAdress = mqttConfigData.serverAdress + ":" + std::to_string(mqttConfigData.port);

    mqttConfig.serverAdress = serverAdress;
    mqttConfig.id = mqttConfigData.id;
    mqttConfig.topic1 = mqttConfigData.topic1;
    mqttConfig.topic2 = mqttConfigData.topic2;
    mqttConfig.topic3 = mqttConfigData.topic3;
    mqttConfig.topic4 = mqttConfigData.topic4;

    switch (mqttConfigData.qos)
    {
    case 0:
        mqttConfig.qos = QOS_0;
        break;
    case 1:
        mqttConfig.qos = QOS_1;
        break;
    case 2:
        mqttConfig.qos = QOS_2;
        break;
    default:
        FAILCODE_SET_AND_EXIT<MqttFailCodeType>(failCode, QOS_IS_INVALID);
        break;
    }
    
}

/**
 * @brief This function connect to the MQTT server.
 * @param[in] mqttConfigData: IniParser MQTT Client Configuration Structure.
 * @return N/A
 */
void MqttComm::ConnectServer(IniParserMqttClientConfig& mqttConfigData)
{
    convertIniParserDataToMqttConfig(mqttConfigData);

    if (mqttClient != nullptr)
    {
        mqttClient->disconnect();
        delete mqttClient;
    }

    mqttClient = new mqtt::client(mqttConfig.serverAdress, mqttConfigData.id);

    mqttClient->connect();

    if (mqttClient->is_connected() == false)
    {
        FAILCODE_SET_AND_EXIT<MqttFailCodeType>(failCode, MQTT_CONNECTION_ERROR);
    }

    std::cout << "MQTT Client connect to the MQTT Server successfully." << std::endl;

    isConnected = true;
}

/**
 * @brief This function publish prepared data to topics as MQTT messages.
 * @param message: Message object referance.
 * @return N/A
 */
void MqttComm::publishMessage(Message& message)
{
    int qos{0};
    std::vector<std::string> parsedMessage;

    if (isConnected == false)
    {
        FAILCODE_SET_AND_EXIT<MqttFailCodeType>(failCode, MQTT_NOT_CONNECTED);
    }

    switch (mqttConfig.qos)
    {
    case QOS_0:
        qos = 0;
        break;
    case QOS_1:
        qos = 1;
        break;
    case QOS_2:
        qos = 2;
        break;
    default:
        break;
    }

    parsedMessage = message.getParsedMessage();

    mqtt::const_message_ptr messagePointer1{mqtt::make_message(mqttConfig.topic1, parsedMessage[0], qos, false)};
    mqtt::const_message_ptr messagePointer2{mqtt::make_message(mqttConfig.topic2, parsedMessage[1], qos, false)};
    mqtt::const_message_ptr messagePointer3{mqtt::make_message(mqttConfig.topic3, parsedMessage[2], qos, false)};
    mqtt::const_message_ptr messagePointer4{mqtt::make_message(mqttConfig.topic4, parsedMessage[3], qos, false)};

    mqttClient->publish(messagePointer1);
    mqttClient->publish(messagePointer2);
    mqttClient->publish(messagePointer3);
    mqttClient->publish(messagePointer4);

    std::cout << "Prepared data was sent successfully." << std::endl << std::endl;
}
