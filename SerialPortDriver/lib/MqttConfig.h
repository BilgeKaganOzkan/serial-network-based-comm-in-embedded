#pragma once

enum MqttFailCodeType
{
    MQTT_OK = 0,
    MQTT_NOT_CONNECTED = 1,
    MQTT_CONNECTION_ERROR = 2,
    QOS_IS_INVALID = 3
};

enum QOS
{
    QOS_0 = 0,
    QOS_1 = 1,
    QOS_2 = 2
};

struct MqttConfig
{
    std::string serverAdress;
    std::string topic1;
    std::string topic2;
    std::string topic3;
    std::string topic4;
    std::string id;
    QOS qos;
};