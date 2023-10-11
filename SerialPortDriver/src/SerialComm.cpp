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
 * @brief This function converts IniParserMqttClientConfig Structure type to SerialPortConfig Structure type.
 * @param[in] iniParserSerialPortConfigData: IniParser Serial Port Configuration Structure.
 * @return throw SERIALPORT_PORTNAME_IS_NONE: if port name is none.
 * 		   throw SERIALPORT_BAUDRATE_OUT_OF_RANGE: baudRate from IniParserSerialPortConfig is not matching with any value in BaudRate enum.
 * 		   throw SERIALPORT_DATABIT_OUT_OF_RANGE: dataBit from IniParserSerialPortConfig is not matching with any value in DataBit enum.
 * 		   throw SERIALPORT_STOPBIT_OUT_OF_RANGE: stopBit from IniParserSerialPortConfig is not matching with any value in StopBit enum.
 * 		   throw SERIALPORT_PARITYBIT_OUT_OF_RANGE: parityBit from IniParserSerialPortConfig is not matching with any value in ParityBit enum.
 */
void SerialComm::convertIniParserDataToSerialConfig(IniParserSerialPortConfig& iniParserSerialPortConfigData)
{
	if (iniParserSerialPortConfigData.portName == "")
	{
		FAILCODE_SET_AND_EXIT(failCode, SERIALPORT_PORTNAME_IS_NONE);
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
		FAILCODE_SET_AND_EXIT(failCode, SERIALPORT_BAUDRATE_OUT_OF_RANGE);
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
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_DATABIT_OUT_OF_RANGE);
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
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_STOPBIT_OUT_OF_RANGE);
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
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_PARITYBIT_OUT_OF_RANGE);
	}
}

/**
 * @brief This function configures the serial port.
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
 * @brief This function initializes the isStarted, failCode variables and serialPort pointer.
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
 * @brief This function deletes the serialPort pointer.
 * @param N/A
 * @return N/A
 */
SerialComm::~SerialComm()
{
	delete serialPort;
}

/**
 * @brief This function starts the serial communication.
 * @param[in] iniParserSerialPortConfigData: IniParserSerialPortConfig Structure reference.
 * @param[in] mqtt: MqttComm object reference. 
 * @return throw SERIALPORT_COMMUNICATION_ALREADY_STARTED: if communication was already started.
 * 		   throw SERIALPORT_COULD_NOT_OPENED: if serial port can not open.
 */
void SerialComm::startCommunication(IniParserSerialPortConfig& iniParserSerialPortConfigData, MqttComm& mqtt)
{
	if (isStarted == true)
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_COMMUNICATION_ALREADY_STARTED);
	}

	if ((serialPort != nullptr) && (serialPort->is_open() == true))
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_COMMUNICATION_NOT_CLOSED);
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
 * @brief This function stops the serial communication.
 * @param N/A
 * @return throw SERIALPORT_COMMUNICATION_ALREADY_STOPPED: if communication was already stopped.
 * 		   throw SERIALPORT_COULD_NOT_CLOSED: ifserial port can not closed.
 */
void SerialComm::stopCommunication()
{
	if (isStarted == false)
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_COMMUNICATION_ALREADY_STOPPED);
	}

	serialPort->close();

	if (serialPort->is_open() == true)
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_COULD_NOT_CLOSED);
	}

	isStarted = false;
}

/**
 * @brief This function reads data from serial port.
 * @param[in] message: Message object reference.
 * @return N/A
 */
void SerialComm::readDataFromSerial(Message& message)
{
	char data{};
	bool isCommunicationContinue{false};

	if (isStarted == false)
	{
		FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_COMMUNICATION_NOT_STARTED);
	}

	while(!isCommunicationContinue)
	{
		try
		{
			boost::asio::read(*serialPort, boost::asio::buffer(&data, 1));
		}
		catch(std::exception& e)
		{
			std::cout << e.what() << std::endl;
			FAILCODE_SET_AND_EXIT<SerialFailCodeType>(failCode, SERIALPORT_READING_ERROR);
		}

		isCommunicationContinue = message.acquireData(data);
		std::cout << data;
	}

	std::cout << " data was received" << std::endl;
}
