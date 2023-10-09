#include <iostream>
#include <string>
#include "SerialComm.h"
#include <cstdlib>
#include <boost/asio.hpp>
#include "MqttComm.h"
#include "FailCode.h"
#include "IniParserConfig.h"
#include "vector"
#include "Message.h"
#include "SerialComm.h"
#include "Configuration.h"

SerialComm::SerialComm()
{
	isStarted = false;
	failCode = SERIAL_OK;
	serial = nullptr;
}

SerialComm::~SerialComm()
{
	delete serial;
}

void SerialComm::convertIniParserDataToSerialConfig(IniParserSerialPortConfig& configData)
{
	if (configData.portName == "")
	{
		FAILCODE_SET_AND_EXIT(failCode, PORTNAME_IS_NONE);
	}
	else
	{
		serialPortConfig.portName = configData.portName;
	}

	switch (configData.baudRate)
	{
	case 9600:
		serialPortConfig.baudRate = BAUDRATE_9600;
		break;
	case 38400:
		serialPortConfig.baudRate = BAUDRATE_38400;
		break;
	case 57600:
		serialPortConfig.baudRate = BAUDRATE_57600;
		break;
	case 115200:
		serialPortConfig.baudRate = BAUDRATE_115200;
		break;
	default:
		FAILCODE_SET_AND_EXIT(failCode, BAUDRATE_OUT_OF_RANGE);
		break;
	}

	switch (configData.dataBit)
	{
	case 5:
		serialPortConfig.dataBit = DATABIT_5;
		break;
	case 6:
		serialPortConfig.dataBit = DATABIT_6;
		break;
	case 7:
		serialPortConfig.dataBit = DATABIT_7;
		break;
	case 8:
		serialPortConfig.dataBit = DATABIT_8;
		break;
	default:
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, DATABIT_OUT_OF_RANGE);
		break;
	}

	switch (configData.stopBit)
	{
	case 1:
		serialPortConfig.stopBit = STOPBIT_1;
		break;
	case 2:
		serialPortConfig.stopBit = STOPBIT_2;
		break;
	default:
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, STOPBIT_OUT_OF_RANGE);
		break;
	}

	if (configData.parityBit == "NONE")
	{
		serialPortConfig.parityBit = PARITYBIT_NONE;
	}
	else if (configData.parityBit == "EVEN")
	{
		serialPortConfig.parityBit = PARITYBIT_ODD;
	}
	else if (configData.parityBit == "ODD")
	{
		serialPortConfig.parityBit = PARITYBIT_EVEN;
	}
	else
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, PARITYBIT_OUT_OF_RANGE);
	}
}

void SerialComm::assignSerialParams(boost::asio::serial_port* serial)
{
	int baudRate{0};
	int dataBit{0};
	boost::asio::serial_port_base::parity::type parityBit{boost::asio::serial_port_base::parity::none};
	boost::asio::serial_port_base::stop_bits::type stopBit{boost::asio::serial_port_base::stop_bits::one};

	switch (serialPortConfig.baudRate)
	{
	case BAUDRATE_9600:
		baudRate = 9600;
		break;
	case BAUDRATE_38400:
		baudRate = 38400;
		break;
	case BAUDRATE_57600:
		baudRate = 57600;
		break;
	case BAUDRATE_115200:
		baudRate = 115200;
		break;
	default:
		break;
	}

	switch (serialPortConfig.dataBit)
	{
	case DATABIT_5:
		dataBit = 5;
		break;
	case DATABIT_6:
		dataBit = 6;
		break;
	case DATABIT_7:
		dataBit = 7;
		break;
	case DATABIT_8:
		dataBit = 8;
		break;
	default:
		break;
	}

	switch (serialPortConfig.parityBit)
	{
	case PARITYBIT_NONE:
		parityBit = boost::asio::serial_port_base::parity::none;
		break;
	case PARITYBIT_ODD:
		parityBit = boost::asio::serial_port_base::parity::odd;
		break;
	case PARITYBIT_EVEN:
		parityBit = boost::asio::serial_port_base::parity::even;
		break;
	default:
		break;
	}

	switch (serialPortConfig.stopBit)
	{
	case STOPBIT_1:
		stopBit = boost::asio::serial_port_base::stop_bits::one;
		break;
	case STOPBIT_2:
		stopBit = boost::asio::serial_port_base::stop_bits::two;
		break;
	default:
		break;
	}

    serial->set_option(boost::asio::serial_port_base::character_size(dataBit));
	serial->set_option(boost::asio::serial_port_base::baud_rate(baudRate));
    serial->set_option(boost::asio::serial_port_base::parity(parityBit));
    serial->set_option(boost::asio::serial_port_base::stop_bits(stopBit));
}

void SerialComm::startCommunication(IniParserSerialPortConfig& configData, MqttComm& mqtt)
{
	if (isStarted == true)
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, COMMUNICATION_ALREADY_STARTED);
	}

	convertIniParserDataToSerialConfig(configData);

	try
	{
		if (serial != nullptr)
		{
			delete serial;
		}

		boost::asio::io_service ioService;
		serial = new boost::asio::serial_port{ioService, static_cast<std::string>(serialPortConfig.portName)};

		if (serial->is_open() == false)
		{
			FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_COULD_NOT_OPENED);
		}

		assignSerialParams(serial);

		isStarted = true;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_COULD_NOT_OPENED);
	}
}

void SerialComm::stopCommunication()
{
	if (isStarted == false)
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, COMMUNICATION_ALREADY_STOPPED);
	}

	serial->close();

	if (serial->is_open() == true)
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_COULD_NOT_CLOSED);
	}
}

void SerialComm::readDataFromSerial(Message& message)
{
	char data;
	bool isCommunicationContinue{false};

	if (isStarted == false)
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, COMMUNICATION_NOT_STARTED);
	}

	while(!isCommunicationContinue)
	{
		boost::asio::read(*serial, boost::asio::buffer(&data, 1));
		std::cout << data;
		isCommunicationContinue = message.acquireData(data);
	}
}
