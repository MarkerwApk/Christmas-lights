/*
 * Serial.hpp
 *
 *  Created on: 5 mar 2015
 *      Author: marek
 */
#include <iostream>
#ifndef SERIAL_HPP_
#define SERIAL_HPP_

#define SERIAL_HEADER "wlh"

#define TYPE_GET_ALL_STATUS 0
#define TYPE_CHANGE_STATUS 1
#define TYPE_SET_ALL_STATUS 2
#define TYPE_GET_CHRISTMAS_LIGHTS_STATUS 3
#define TYPE_SET_CHRISTMAS_LIGHTS_STATUS 4

typedef unsigned char byte;
class Serial {

public:
	Serial();
	static int calcCrc(int data[], int len);
	static bool checkCrc(byte* data, int offset);
	void sendData(int data[], int len);

	int getDataCount();

	byte* readSerialData(byte* &data, int count);

private:
	int fd;

	void connect();
	int serialOpen(const char* path);

};

#endif /* SERIAL_HPP_ */
