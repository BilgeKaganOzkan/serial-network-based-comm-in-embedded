#include <iostream>
#include <mqtt/client.h>
#include "MqttComm.h"
#include "FailCode.h"
#include "IniParserConfig.h"
#include <vector>
#include "Message.h"

MqttComm::MqttComm()
{
    isConnected = false;
    failCode = MQTT_OK;
}

MqttComm::~MqttComm()
{
    delete client;
}

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

void MqttComm::ConnectServer(IniParserMqttClientConfig& mqttConfigData)
{
    convertIniParserDataToMqttConfig(mqttConfigData);

    client = new mqtt::client(mqttConfig.serverAdress, mqttConfigData.id, mqtt::create_options(MQTTVERSION_5));

    client->connect();

    if (client->is_connected() == false)
    {
        FAILCODE_SET_AND_EXIT<MqttFailCodeType>(failCode, MQTT_CONNECTION_ERROR);
    }

    isConnected = true;
}

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

    client->publish(messagePointer1);
    client->publish(messagePointer2);
    client->publish(messagePointer3);
    client->publish(messagePointer4);
}