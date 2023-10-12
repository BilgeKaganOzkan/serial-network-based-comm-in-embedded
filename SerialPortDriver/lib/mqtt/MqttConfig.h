/** \addtogroup MqttComm
 * @{
 * @author Bilge Kağan ÖZKAN
 * @file MqttConfig.h
 * @brief This file includes MqttFailCodeType, QOS types and MqttConfig structure.
 */

#pragma once

/** @brief MQTT Failcode Types
 */
enum MqttFailCodeType
{
    MQTT_OK = 0,               ///< This indicates that the process was successful.
    MQTT_NOT_CONNECTED = 1,    ///< This indicates that client could not connect to the MQTT server.
    MQTT_CONNECTION_ERROR = 2, ///< This indicates that a connection error was occured.
    MQTT_QOS_IS_INVALID = 3    ///< This indicates that QOS number is invalid.
};

/** @brief QOS Types 
 */
enum QOS
{
    QOS_0 = 0, ///< This indicates QOS 0
    QOS_1 = 1, ///< This indicates QOS 1
    QOS_2 = 2  ///< This indicates QOS 2
};


/** @struct MqttConfig
 *  @brief MQTT Client Configuration Structure
 */
struct MqttConfig
{
    std::string serverAdress; ///< This indicates the MQTT Server ip adress.
    std::string username;     ///< This indicates the MQTT username.
    std::string password;     ///< This indicates the MQTT password.
    std::string topic1;       ///< This indicates the first MQTT topic.
    std::string topic2;       ///< This indicates the second MQTT topic.
    std::string topic3;       ///< This indicates the third MQTT topic.
    std::string topic4;       ///< This indicates the fourth MQTT topic.
    std::string id;           ///< This indicates the unique id for connect MQTT server.
    QOS qos;                  ///< This indicates the QOS number.
};

/**@}*/
