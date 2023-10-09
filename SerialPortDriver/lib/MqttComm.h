#pragma once
#include <mqtt/client.h>
#include <iostream>
#include "FailCode.h"
#include "MqttConfig.h"
#include "IniParserConfig.h"
#include <vector>
#include "Message.h"

class MqttComm
{
private:
    bool isConnected;
    mqtt::client* client;
    MqttConfig mqttConfig;
    FailCode<MqttFailCodeType> failCode;
    void convertIniParserDataToMqttConfig(IniParserMqttClientConfig& mqttConfigData);
public:
    MqttComm();
    ~MqttComm();
    void ConnectServer(IniParserMqttClientConfig& mqttConfigData);
    void publishMessage(Message& message);
};