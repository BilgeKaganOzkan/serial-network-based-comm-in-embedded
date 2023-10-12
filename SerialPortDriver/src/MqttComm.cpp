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
 * @brief This function converts IniParserMqttClientConfig Structure type to MqttConfig Structure type.
 * @param[in] mqttConfigData: IniParser MQTT Client Configuration Structure.
 * @return throw MQTT_QOS_IS_INVALID: QOS from IniParserMqttClientConfig is not matching with any value in QOS enum.
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
    mqttConfig.username = mqttConfigData.username;
    mqttConfig.password = mqttConfigData.password;

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
        FAILCODE_SET_AND_EXIT<MqttFailCodeType>(failCode, MQTT_QOS_IS_INVALID);
        break;
    }  
}

/**
 * @brief This function initializes the isConnect,failCode variables and mqttClient pointer.
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
 * @brief This function deletes mqttClient pointer.
 * @param N/A
 * @return N/A
 */
MqttComm::~MqttComm()
{
    delete mqttClient;
}

/**
 * @brief This function connects to the MQTT server.
 * @param[in] mqttConfigData: IniParser MQTT Client Configuration Structure.
 * @return N/A
 */
void MqttComm::connectServer(IniParserMqttClientConfig& mqttConfigData)
{
    convertIniParserDataToMqttConfig(mqttConfigData);

    if (mqttClient != nullptr)
    {
        mqttClient->disconnect();
        delete mqttClient;
    }

    mqttClient = new mqtt::client(mqttConfig.serverAdress, mqttConfigData.id);
    
    mqtt::connect_options connectionOptions;
    connectionOptions.set_clean_session(true);
    connectionOptions.set_user_name(mqttConfig.username);
    connectionOptions.set_password(mqttConfig.password);
    connectionOptions.set_keep_alive_interval(20);

    mqtt::ssl_options sslOptions;
    sslOptions.set_ssl_version(MQTT_SSL_VERSION_TLS_1_2);
    sslOptions.set_verify(false);
    connectionOptions.set_ssl(sslOptions);

    try
    {
        mqttClient->connect(connectionOptions);
    }
    catch(const std::exception& e)
    {
        FAILCODE_SET_AND_EXIT<MqttFailCodeType>(failCode, MQTT_CONNECTION_ERROR);
    }
    
    

    if (mqttClient->is_connected() == false)
    {
        FAILCODE_SET_AND_EXIT<MqttFailCodeType>(failCode, MQTT_CONNECTION_ERROR);
    }

    std::cout << "MQTT Client connect to the MQTT Server successfully." << std::endl;

    isConnected = true;
}

/**
 * @brief This function publishes prepared message to topics as MQTT messages.
 * @param message: Message object reference.
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
