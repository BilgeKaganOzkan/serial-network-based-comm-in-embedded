/** \addtogroup MqttComm
 * @{
 * @author Bilge Kağan ÖZKAN
 * @file MqttComm.h
 * @defgroup MqttComm
 * @brief This module includes SerialComm class.
 * @verbatim
 * MqttComm class connects to the MQTT Server and publishes prepared data to topics as MQTT messages.
 * @endverbatim
 */

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
 * @brief MqttComm class connects to the MQTT Server and publishes prepared message to topics as MQTT messages.
 */
class MqttComm
{
private:
    bool isConnected;                    ///< This variable keeps whether connected to the MQTT server or not.
    mqtt::client* mqttClient;            ///< This pointer keeps mqtt::client address from paho mqtt library.
    MqttConfig mqttConfig;               ///< This variable keeps the Mqtt configurations.
    FailCode<MqttFailCodeType> failCode; ///< This variable keeps objectified FailCode class with MqttFailCodeType enum.

    /**
     * @brief This function converts IniParserMqttClientConfig Structure type to MqttConfig Structure type.
     * @param[in] mqttConfigData: IniParser MQTT Client Configuration Structure.
     * @return throw MQTT_QOS_IS_INVALID: QOS from IniParserMqttClientConfig is not matching with any value in QOS enum.
     */
    void convertIniParserDataToMqttConfig(IniParserMqttClientConfig& mqttConfigData);
    
public:
    /**
     * @brief This function initializes the isConnect, failCode variables and mqttClient pointer.
     * @param N/A
     * @return N/A
     */
    MqttComm();

    /**
     * @brief This function deletes mqttClient pointer.
     * @param N/A
     * @return N/A
     */
    ~MqttComm();

    /**
     * @brief This function connects to the MQTT server.
     * @param[in] mqttConfigData: IniParser MQTT Client Configuration Structure.
     * @return N/A
     */
    void connectServer(IniParserMqttClientConfig& mqttConfigData);

    /**
     * @brief This function publishes prepared message to topics as MQTT messages.
     * @param message: Message object reference.
     * @return N/A
     */
    void publishMessage(Message& message);
};

/**@}*/
