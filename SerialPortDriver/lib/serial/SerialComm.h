/** \addtogroup SerialComm
 * @{
 * @author Bilge Kağan ÖZKAN
 * @file SerialComm.h
 * @defgroup SerialComm
 * @brief This module includes SerialComm class.
 * @verbatim
 * SerialComm class connects the serial port, starts the communication and reads the data from serial port.
 * @endverbatim
 */

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include "MqttComm.h"
#include "SerialConfig.h"
#include "IniParserConfig.h"
#include "SerialComm.h"

/**
 * @class SerialComm
 * @brief SerialComm class connects the serial port, starts the communication and reads the data from serial port.
 */
class SerialComm
{
private:
	boost::asio::serial_port* serialPort;  ///< This pointer keeps boost::asio::serial_port address from boost library.
	bool isStarted;                        ///< This variable keeps wheather serial communication was started or not.
	FailCode<SerialFailCodeType> failCode; ///< This variable keeps objectified FailCode class with SerialFailCodeType enum.
	SerialPortConfig serialPortConfig;     ///< This variable keeps the serial port configurations.

	/**
	 * @brief This function converts IniParserMqttClientConfig Structure type to SerialPortConfig Structure type.
	 * @param[in] iniParserSerialPortConfigData: IniParser Serial Port Configuration Structure.
	 * @return throw SERIALPORT_PORTNAME_IS_NONE: if port name is none.
	 * 		   throw SERIALPORT_BAUDRATE_OUT_OF_RANGE: baudRate from IniParserSerialPortConfig is not matching with any value in BaudRate enum.
	 * 		   throw SERIALPORT_DATABIT_OUT_OF_RANGE: dataBit from IniParserSerialPortConfig is not matching with any value in DataBit enum.
	 * 		   throw SERIALPORT_STOPBIT_OUT_OF_RANGE: stopBit from IniParserSerialPortConfig is not matching with any value in StopBit enum.
	 * 		   throw SERIALPORT_PARITYBIT_OUT_OF_RANGE: parityBit from IniParserSerialPortConfig is not matching with any value in ParityBit enum.
	 */
	void convertIniParserDataToSerialConfig(IniParserSerialPortConfig& iniParserSerialPortConfigData);

	/**
	 * @brief This function configures the serial port.
	 * @param N/A
	 * @return N/A
	 */
	void assignSerialParams();

public:
	/**
	 * @brief This function initializes the isStarted, failCode variables and serialPort pointer.
	 * @param N/A
	 * @return N/A
	 */
	SerialComm();

	/**
	 * @brief This function deletes the serialPort pointer.
	 * @param N/A
	 * @return N/A
	 */
	~SerialComm();

	/**
	 * @brief This function starts the serial communication.
	 * @param[in] iniParserSerialPortConfigData: IniParserSerialPortConfig Structure reference.
 	 * @param[in] mqtt: MqttComm object reference. 
	 * @return throw SERIALPORT_COMMUNICATION_ALREADY_STARTED: if communication was already started.
	 * 		   throw SERIALPORT_COULD_NOT_OPENED: if serial port can not open.
	 */
	void startCommunication(IniParserSerialPortConfig& iniParserSerialPortConfigData, MqttComm& mqtt);

	/**
	 * @brief This function stops the serial communication.
	 * @param N/A
	 * @return throw SERIALPORT_COMMUNICATION_ALREADY_STOPPED: if communication was already stopped.
	 * 		   throw SERIALPORT_COULD_NOT_CLOSED: ifserial port can not closed.
	 */
	void stopCommunication();

	/**
	 * @brief This function reads data from serial port.
	 * @param[in] message: Message object reference.
	 * @return N/A
	 */
	void readDataFromSerial(Message& message);
};

/**@}*/
