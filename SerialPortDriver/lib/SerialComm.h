#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include "MqttComm.h"
#include "SerialConfig.h"
#include "IniParserConfig.h"
#include "SerialComm.h"

class SerialComm
{
private:
	boost::asio::serial_port *serial;
	bool isStarted;
	FailCode<SerialFailCodeType> failCode;
	SerialPortConfig serialPortConfig;
	void convertIniParserDataToSerialConfig(IniParserSerialPortConfig& configData);
	void assignSerialParams(boost::asio::serial_port* serial);

public:
	SerialComm();
	~SerialComm();
	void startCommunication(IniParserSerialPortConfig& configData, MqttComm& mqtt);
	void stopCommunication();
	void readDataFromSerial(Message& message);
};
