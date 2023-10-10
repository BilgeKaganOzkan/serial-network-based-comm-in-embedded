/**
 * @file SerialComm.cpp 
 * @author Bilge Kağan ÖZKAN
 */

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

/**
 * @brief This function initialize the isStarted variable, failCode and serial pointers.
 * @param N/A
 * @return N/A
 */
SerialComm::SerialComm()
{
	isStarted = false;
	failCode = SERIAL_OK;
	serialPort = nullptr;
}

/**
 * @brief This function delete the serial pointers.
 * @param N/A
 * @return N/A
 */
SerialComm::~SerialComm()
{
	delete serialPort;
}

/**
 * @brief This function convert IniParserMqttClientConfig Structure type to SerialPortConfig Structure type.
 * @param[in] iniParserSerialConfigData: IniParser Serial Port Configuration Structure.
 * @return N/A
 */
void SerialComm::convertIniParserDataToSerialConfig(IniParserSerialPortConfig& iniParserSerialPortConfigData)
{
	if (iniParserSerialPortConfigData.portName == "")
	{
		FAILCODE_SET_AND_EXIT(failCode, PORTNAME_IS_NONE);
	}
	else
	{
		serialPortConfig.portName = iniParserSerialPortConfigData.portName;
	}

	switch (iniParserSerialPortConfigData.baudRate)
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

	switch (iniParserSerialPortConfigData.dataBit)
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

	switch (iniParserSerialPortConfigData.stopBit)
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

	if (iniParserSerialPortConfigData.parityBit == "NONE")
	{
		serialPortConfig.parityBit = PARITYBIT_NONE;
	}
	else if (iniParserSerialPortConfigData.parityBit == "EVEN")
	{
		serialPortConfig.parityBit = PARITYBIT_ODD;
	}
	else if (iniParserSerialPortConfigData.parityBit == "ODD")
	{
		serialPortConfig.parityBit = PARITYBIT_EVEN;
	}
	else
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, PARITYBIT_OUT_OF_RANGE);
	}
}

/**
 * @brief This function configure the serial port.
 * @param N/A
 * @return N/A
 */
void SerialComm::assignSerialParams()
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

    serialPort->set_option(boost::asio::serial_port_base::character_size(dataBit));
	serialPort->set_option(boost::asio::serial_port_base::baud_rate(baudRate));
    serialPort->set_option(boost::asio::serial_port_base::parity(parityBit));
    serialPort->set_option(boost::asio::serial_port_base::stop_bits(stopBit));
}

/**
 * @brief This function start the serial communication.
 * @param[in] iniParserSerialPortConfigData: IniParserSerialPortConfig Structure referance.
 * @param[in] mqtt: MqttComm object referance. 
 * @return N/A
 */
void SerialComm::startCommunication(IniParserSerialPortConfig& iniParserSerialPortConfigData, MqttComm& mqtt)
{
	if (isStarted == true)
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, COMMUNICATION_ALREADY_STARTED);
	}

	convertIniParserDataToSerialConfig(iniParserSerialPortConfigData);

	try
	{
		if (serialPort != nullptr)
		{
			serialPort->close();
			delete serialPort;
		}

		boost::asio::io_service ioService;
		serialPort = new boost::asio::serial_port{ioService, static_cast<std::string>(serialPortConfig.portName)};

		if (serialPort->is_open() == false)
		{
			FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_COULD_NOT_OPENED);
		}

		std::cout << "Serial communication was started successfully." << std::endl;

		assignSerialParams();

		isStarted = true;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_COULD_NOT_OPENED);
	}
}

/**
 * @brief This function stop the serial communication.
 * @param N/A
 * @return N/A
 */
void SerialComm::stopCommunication()
{
	if (isStarted == false)
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, COMMUNICATION_ALREADY_STOPPED);
	}

	serialPort->close();

	if (serialPort->is_open() == true)
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_COULD_NOT_CLOSED);
	}
}

/**
 * @brief This function read data from serial port.
 * @param[in] message: Message object referance.
 * @return N/A
 */
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
		boost::asio::read(*serialPort, boost::asio::buffer(&data, 1));
		isCommunicationContinue = message.acquireData(data);
		std::cout << data;
	}

	std::cout << " data was received" << std::endl;
}
