/*
 * Gpio.cpp
 *
 *  Created on: 10 mar 2015
 *      Author: markerwapk
 */
#include "Gpio.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;
Gpio::Gpio() {

}
int Gpio::readGpio(int port) {
	string path = "";
	path += GPIO_PATH_BEGIN;

	stringstream ss;
	ss << port;

	path += ss.str();

	path += GPIO_PATH_VALUE;
	const char *fname = path.c_str();

	FILE* file = fopen(fname, "w+");
	if (file != NULL) {
		char value[20];
		fgets(value, 20, file);
		strtok(value, "\n");

		fflush(file);
		fclose(file);
		return atoi(value);
	} else {
		return -1;
	}
}

int Gpio::setActive(int port, int value) {
	string path = "";
	path += GPIO_PATH_BEGIN;

	stringstream ss;
	ss << port;

	path += ss.str();

	path += GPIO_PATH_ACTIVE;
	const char *fname = path.c_str();

	FILE* file = fopen(fname, "w+");
	if (file != NULL) {
		//char buffer[16];
		//sprintf(buffer, "%d", value);
		//fputs(buffer, file);

		fprintf(file, "%d", value);

		fflush(file);
		fclose(file);
		return 0;
	} else {
		return -1;
	}
}

int Gpio::setValue(int port, int value) {
	string path = "";
	path += GPIO_PATH_BEGIN;

	stringstream ss;
	ss << port;

	path += ss.str();

	path += GPIO_PATH_VALUE;
	const char *fname = path.c_str();

	FILE* file = fopen(fname, "w+");
	if (file != NULL) {
		//char buffer[16];
		//sprintf(buffer, "%d", value);
		//fputs(buffer, file);

		fprintf(file, "%d", value);

		fflush(file);
		fclose(file);
		return 0;
	} else {
		return -1;
	}
}

