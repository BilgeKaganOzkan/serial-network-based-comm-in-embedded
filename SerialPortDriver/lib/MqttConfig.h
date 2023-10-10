#pragma once

/* MQTT Failcode Types */
enum MqttFailCodeType
{
    MQTT_OK = 0, // This indicates that the process was successful.
    MQTT_NOT_CONNECTED = 1, // This indicates that client could not connect the MQTT server.
    MQTT_CONNECTION_ERROR = 2, // This indicates that an connection error was occured.
    QOS_IS_INVALID = 3 // This indicates that QOS number is invalid.
};

/* QOS Types */
enum QOS
{
    QOS_0 = 0, // This indicates QOS 0
    QOS_1 = 1, // This indicates QOS 1
    QOS_2 = 2  // This indicates QOS 2
};

/* MQTT Client Configuration Structure */
struct MqttConfig
{
    std::string serverAdress; // This indicates MQTT Server ip adress.
    std::string topic1; // This indicates first MQTT topic.
    std::string topic2; // This indicates second MQTT topic.
    std::string topic3; // This indicates third MQTT topic.
    std::string topic4; // This indicates fourth MQTT topic.
    std::string id; // This indicates unique id for connect MQTT server.
    QOS qos; // This indicates QOS number.
};
