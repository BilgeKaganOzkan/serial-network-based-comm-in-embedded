#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include "MqttComm.h"
#include "SerialConfig.h"
#include "IniParserConfig.h"
#include "SerialComm.h"

/**
 * @class SerialComm
 * @brief SerialComm class connect the serial port, start the communication and read the data from serial port.
 */
class SerialComm
{
private:
	boost::asio::serial_port *serial;
	bool isStarted;
	FailCode<SerialFailCodeType> failCode;
	SerialPortConfig serialPortConfig;

	/**
         * @brief This function convert IniParserMqttClientConfig Structure type to SerialPortConfig Structure type.
         * @param[in] configData: IniParser Serial Port Configuration Structure.
         * @return N/A
         */
	void convertIniParserDataToSerialConfig(IniParserSerialPortConfig& configData);

	/**
         * @brief This function configure the serial port.
         * @param[in] serial: boost::asio::serial_port object pointer.
         * @return N/A
         */
	void assignSerialParams(boost::asio::serial_port* serial);

public:
	/**
	 * @brief This function initialize the isStarted variable, failCode and serial pointers.
	 * @param N/A
	 * @return N/A
	 */
	SerialComm();

	/**
	 * @brief This function delete the serial pointers.
	 * @param N/A
	 * @return N/A
	 */
	~SerialComm();

	/**
	 * @brief This function start the serial communication.
	 * @param[in] configData: IniParserSerialPortConfig Structure referance.
 	 * @param[in] mqtt: MqttComm object referance. 
	 * @return N/A
	 */
	void startCommunication(IniParserSerialPortConfig& configData, MqttComm& mqtt);

	/**
	 * @brief This function stop the serial communication.
	 * @param N/A
	 * @return N/A
	 */
	void stopCommunication();

	/**
	 * @brief This function read data from serial port.
	 * @param[in] message: Message object referance.
	 * @return N/A
	 */
	void readDataFromSerial(Message& message);
};
