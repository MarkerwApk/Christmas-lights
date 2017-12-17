/*
 * SmartHome.hpp
 *
 *  Created on: 5 mar 2015
 *      Author: marek
 */

#ifndef SMARTHOME_HPP_
#define SMARTHOME_HPP_

#include "Serial.hpp"

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <unistd.h>

#include "SmartHome.hpp"
#include "Pins.hpp"
#include "Gpio.hpp"
#include "OneWire.hpp"
#include "ChristmasLightsManager.hpp"
#include "SantaClausLightsManager.hpp"

class SmartHome {

public:
	SmartHome();
	void start();

private:
	void preparePins();

	Serial* serial;
	Gpio* gpio;
	OneWire* oneWire;
	ChristmasLightsManager* christmasLightsManager;
	SantaClausLightsManager* santaClausLightsManager;

	int warningCount;

	void runThread();

	static void * christmasLightsThreadFunction(void * context) {
		return ((SmartHome*) context)->christmasLightsThreadFunction();
	}

	static void * santaClausLightsThreadFunction(void * context) {
			return ((SmartHome*) context)->santaClausLightsThreadFunction();
		}

	static void * readThreadSerial_helper(void * context) {
		return ((SmartHome*) context)->readThreadSerial_function();
	}

	void * christmasLightsThreadFunction();
	void * santaClausLightsThreadFunction();
	void * readThreadGpio_function();
	void * readThreadSerial_function();
	void * readThreadChristamsLights_function();
	void * christmasLightsThread_function();

	void warningGpioMode();

	void setPortValue(int port, int value);

	int charToInt(char c);

};
#endif /* SMARTHOME_HPP_ */
