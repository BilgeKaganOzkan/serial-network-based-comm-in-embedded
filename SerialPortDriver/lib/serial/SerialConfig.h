/** \addtogroup SerialComm
 * @{
 * @author Bilge Kağan ÖZKAN
 * @file SerialConfig.h
 * @brief This file includes BaudRate, DataBit, StopBit, ParityBit, SerialFailCodeType types and SerialPortConfig structure.
 */

#pragma once
#include <iostream>

/** @brief Serial Port Baudrate Types Definitions  
 */
enum BaudRate
{
	BAUDRATE_9600 = 0,  ///< This indicates that baudrate is 9600 bit/second.
	BAUDRATE_38400 = 1, ///< This indicates that baudrate is 38400 bit/second.
	BAUDRATE_57600 = 2, ///< This indicates that baudrate is 57600 bit/second.
	BAUDRATE_115200 = 3 ///< This indicates that baudrate is 115200 bit/second.
};

/** @brief Serial Port Data Bits Types Definitions 
 */
enum DataBit
{
	DATABIT_5 = 0, ///< This indicates that data bits are 5 bits.
	DATABIT_6 = 1, ///< This indicates that data bits are 6 bits.
	DATABIT_7 = 2, ///< This indicates that data bits are 7 bits.
	DATABIT_8 = 3  ///< This indicates that data bits are 8 bits.
};

/** @brief Serial Port Stop Bits Types Definitions 
 */
enum StopBit
{
	STOPBIT_1 = 0, ///< This indicates that stop bit is 1 bit.
	STOPBIT_2 = 1  ///< This indicates that stop bits are 2 bits.
};

/** @brief Serial Port Parity Bit Types Definitions 
 */
enum ParityBit
{
	PARITYBIT_NONE = 0, ///< This indicates that parity bit is none.
	PARITYBIT_EVEN = 1, ///< This indicates that parity bit is even.
	PARITYBIT_ODD = 2   ///< This indicates that parity bit is odd.
};

/** @brief Serial Port Failcode Types 
 */
enum SerialFailCodeType
{
	SERIAL_OK = 0,                                 ///< This indicates that the process was successful.
	SERIALPORT_BAUDRATE_OUT_OF_RANGE = 1,          ///< This indicates that the baudrate is not in BaudRate enum type.
	SERIALPORT_DATABIT_OUT_OF_RANGE = 2,           ///< This indicates that the data bits are not in DataBit enum type.
	SERIALPORT_PARITYBIT_OUT_OF_RANGE = 3,         ///< This indicates that the parity bit is not in ParityBit enum type.
	SERIALPORT_STOPBIT_OUT_OF_RANGE = 4,           ///< This indicates that the stop bits are not in StopBit enum type.
	SERIALPORT_PORTNAME_IS_NONE = 5,               ///< This indicates that the serial port name is none.
	SERIALPORT_COULD_NOT_OPENED  = 6,              ///< This indicates that the serial port could not opened.
	SERIALPORT_COULD_NOT_CLOSED = 7,               ///< This indicates that the serial port was not closed.
	SERIALPORT_READING_ERROR = 8,                  ///< This indicates that a reading error was occured.
	SERIALPORT_COMMUNICATION_NOT_STARTED = 9,      ///< This indicates that the communication was not started.
	SERIALPORT_COMMUNICATION_NOT_CLOSED = 10,      ///< This indicates that the communication was not closed.
	SERIALPORT_COMMUNICATION_ALREADY_STARTED = 11, ///< This indicates that the communication was already started.
	SERIALPORT_COMMUNICATION_ALREADY_STOPPED = 12  ///< This indicates that the communication was already stopped.
};

/** @struct SerialPortConfig
 *  @brief Serial Port Configuration Structure 
 */
struct SerialPortConfig
{
	std::string portName; ///< This indicates the serial port name.
	BaudRate baudRate; ///< This indicates the baudrate.
	DataBit dataBit; ///< This indicates the data bit length.
	StopBit stopBit; ///< This indicates the stop bit length.
	ParityBit parityBit; ///< This indicates the parity bit type.
};

/**@}*/
