/*
 * OneWire.cpp
 *
 *  Created on: 15 mar 2015
 *      Author: markerwapk
 */
#include "OneWire.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <sstream>

using namespace std;
int OneWire::readValue(std::string id) {
	string path = "";
	path += ONE_WIRE_BEGIN_PATH;

	stringstream ss;
	ss << id;

	path += ss.str();

	path += ONE_WIRE_BEGIN_VALUE;
	const char *fname = path.c_str();

	FILE* file = fopen(fname, "r");
	if (file != NULL) {
		char* value = new char[200];
		fgets(value, 200, file); //Pierwsza linia nieużyteczna

		fgets(value, 200, file);

		strtok(value, "\n");

		string s(value);

		s = s.substr(s.find('=') + 1, 100);
		fflush(file);
		fclose(file);
		return atoi(s.c_str()) / 1000;
	}

	return -300;

}

int OneWire::writeToFile(int value) {
	string path = "";
	path += ONE_WIRE_VALUE_PATH;

	const char *fname = path.c_str();

	FILE* file = fopen(fname, "w+");
	if (file != NULL) {

		fprintf(file, "%d", value);

		fflush(file);
		fclose(file);
		return 0;
	} else {
		return -1;
	}
}

int OneWire::getValue() {
	string path = "";
	path += ONE_WIRE_VALUE_PATH;

	const char *fname = path.c_str();

	FILE* file = fopen(fname, "r");
	if (file != NULL) {
		char value[20];
		fgets(value, 20, file);
		strtok(value, "\n");

		fflush(file);
		fclose(file);

		int i = atoi(value);
		return i / 1000;
	} else {
		return -300;
	}
}

