#pragma once
#include <mqtt/client.h>
#include <iostream>
#include "FailCode.h"
#include "MqttConfig.h"
#include "IniParserConfig.h"
#include <vector>
#include "Message.h"

/**
 * @class MqttComm
 * @brief MqttComm class connect MQTT Server and publish prepared data to topics as MQTT messages.
 */
class MqttComm
{
private:
    bool isConnected;
    mqtt::client* client;
    MqttConfig mqttConfig;
    FailCode<MqttFailCodeType> failCode;

    /**
     * @brief This function convert IniParserMqttClientConfig Structure type to MqttConfig Structure type.
     * @param[in] mqttConfigData: IniParser MQTT Client Configuration Structure.
     * @return N/A
     */
    void convertIniParserDataToMqttConfig(IniParserMqttClientConfig& mqttConfigData);
public:
    /**
     * @brief This function initialize the isConnect variable and failCode pointer.
     * @param N/A
     * @return N/A
     */
    MqttComm();

    /**
     * @brief This function delete failCode pointer.
     * @param N/A
     * @return N/A
     */
    ~MqttComm();

    /**
     * @brief This function connect to the MQTT server.
     * @param[in] mqttConfigData: IniParser MQTT Client Configuration Structure.
     * @return N/A
     */
    void ConnectServer(IniParserMqttClientConfig& mqttConfigData);

    /**
     * @brief This function publish prepared data to topics as MQTT messages.
     * @param message: Message object referance.
     * @return N/A
     */
    void publishMessage(Message& message);
};
