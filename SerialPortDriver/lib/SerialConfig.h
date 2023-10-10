#pragma once
#include <iostream>

/* Serial Port Baudrate Types Definitions */
enum BaudRate
{
	BAUDRATE_9600 = 0, // This indicates that baudrate is 9600 bit/second.
	BAUDRATE_38400 = 1, // This indicates that baudrate is 38400 bit/second.
	BAUDRATE_57600 = 2, // This indicates that baudrate is 57600 bit/second.
	BAUDRATE_115200 = 3 // This indicates that baudrate is 115200 bit/second.
};

/* Serial Port Data Bits Types Definitions */
enum DataBit
{
	DATABIT_5 = 0, // This indicates that data bits are 5 bits.
	DATABIT_6 = 1, // This indicates that data bits are 6 bits.
	DATABIT_7 = 2, // This indicates that data bits are 7 bits.
	DATABIT_8 = 3  // This indicates that data bits are 8 bits.
};

/* Serial Port Stop Bits Types Definitions */
enum StopBit
{
	STOPBIT_1 = 0, // This indicates that stop bit is 1 bit.
	STOPBIT_2 = 1  // This indicates that stop bits are 2 bits.
};

/* Serial Port Parity Bit Types Definitions */
enum ParityBit
{
	PARITYBIT_NONE = 0, // This indicates that parity bit is none.
	PARITYBIT_EVEN = 1, // This indicates that parity bit is even.
	PARITYBIT_ODD = 2 // This indicates that parity bit is odd.
};

/* Serial Port Failcode Types */
enum SerialFailCodeType
{
	SERIAL_OK = 0, // This indicates that the process was successful.
	NAME_IS_INVALID = 1, // This indicates that the port name is invalid.
	BAUDRATE_OUT_OF_RANGE = 2, // This indicates that baudrate is not BaudRate enum type.
	DATABIT_OUT_OF_RANGE = 3, // This indicates that data bits is not DataBit enum type.
	PARITYBIT_OUT_OF_RANGE = 4, // This indicates that parity bit is not ParityBit enum type.
	STOPBIT_OUT_OF_RANGE = 5, // This indicates that stop bits is not StopBit enum type.
	SERIALPORT_COULD_NOT_OPENED  = 6, // This indicates that serial port could not opened.
	NOT_OBTAINED_SERIALPORT_STATUS = 7, // This indicates that serial port status could not abtained.
	PORTNAME_IS_NONE = 8, // This indicates that serial port name is none.
	READING_ERROR = 9, // This indicates that an reading error was occured.
	SERIALPORT_COULD_NOT_CLOSED = 10, // This indicates that serial port was not closed.
	COMMUNICATION_NOT_STARTED = 11, // This indicates that communication was not started.
	COMMUNICATION_NOT_CLOSED = 12, // This indicates that communication was not closed.
	COMMUNICATION_ALREADY_STOPPED = 13, // This indicates that communication was already stopped.
	COMMUNICATION_ALREADY_STARTED = 14 // This indicates that communication was already started.
};

/*Serial Port Configuration Structure */
struct SerialPortConfig
{
	std::string portName; // This indicates serial port name.
	BaudRate baudRate; // This indicates baudrate.
	DataBit dataBit; // This indicates data bit length.
	StopBit stopBit; // This indicates stop bit length.
	ParityBit parityBit; // This indicates parity bit type.
};
