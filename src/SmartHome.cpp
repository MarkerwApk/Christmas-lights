/*
 * Start.cpp
 *
 *  Created on: 5 mar 2015
 *      Author: marek
 */
#include "SmartHome.hpp"

#include <pthread.h>
#include <map>
#include <errno.h>

using namespace std;

SmartHome::SmartHome() {
	warningCount = 0;

	serial = new Serial();
	gpio = new Gpio();
	oneWire = new OneWire();
	christmasLightsManager = new ChristmasLightsManager();
	santaClausLightsManager = new SantaClausLightsManager();
}

void SmartHome::start() {
	//wiringPiSetupGpio();
	preparePins();
	runThread();

}

void SmartHome::preparePins() {

}

void SmartHome::runThread() {

	//christmasLightsManager->start();

	pthread_t christmas_lights_thread;

	if (pthread_create(&(christmas_lights_thread), NULL,
			&SmartHome::christmasLightsThreadFunction,
			(void *) &(christmas_lights_thread)) != 0) {
		printf("CHristmas Lights thread not started");
	}

	pthread_t santa_claus_lights_thread;

	if (pthread_create(&(santa_claus_lights_thread), NULL,
			&SmartHome::santaClausLightsThreadFunction,
			(void *) &(santa_claus_lights_thread)) != 0) {
		printf("Santa Claus Lights thread not started");
	}

	while (true) {

		if (warningCount > 10) {
			warningGpioMode();
		}
		//	printf("BeforeSendData\n");
		fflush(stdout);
		readThreadGpio_function();

		usleep(1000 * 100);

		readThreadSerial_function();

		usleep(1000 * 100); //microsecounds

		readThreadChristamsLights_function();

		usleep(1000 * 100);

		readThreadSerial_function();

		usleep(1000 * 100);

		printf("AfterFunction\n");
		fflush(stdout);

	}
}
void *SmartHome::christmasLightsThreadFunction() {
	Gpio* testGpio = new Gpio();

	int* offset = new int();
	int* state = new int();
	*state = STATE_START;

	int* blinkPosition = new int();
	int* blinkStatus = new int();
	int* blinkAcceleration = new int();

	*blinkAcceleration = BLINK_ACCELERATION_START;

	while (true) {
		usleep(1000 * CHRISTMAS_LIGHTS_THREAD_SPEED);
		christmasLightsManager->christmasLightsThread_function(testGpio, offset,
				state, blinkPosition, blinkStatus, blinkAcceleration);
	}
	return NULL;
}
void *SmartHome::santaClausLightsThreadFunction() {
	Gpio* testGpio = new Gpio();

	int* offset = new int();
	int* state = new int();
	*state = STATE_START;
	int* blinkStatus = new int();

	while (true) {
		usleep(1000 * SANTA_CLAUS_LIGHTS_THREAD_SPEED);
		santaClausLightsManager->santaClausLightsThread_function(testGpio,
				offset, state,blinkStatus);
	}
	return NULL;
}

void *SmartHome::readThreadChristamsLights_function() {

	int count = INPUTS_COUNT;

	int data[5 + count * 2];

	int offset = 0;
	data[offset++] = 'w';
	data[offset++] = 'l';
	data[offset++] = 'h';

	data[offset++] = TYPE_GET_CHRISTMAS_LIGHTS_STATUS;

	data[offset++] = Serial::calcCrc(data, offset);

	serial->sendData(data, offset);

	return NULL;

}

void *SmartHome::readThreadGpio_function() {

	int count = INPUTS_COUNT;

	int data[6 + count * 2];

	int offset = 0;
	data[offset++] = 'w';
	data[offset++] = 'l';
	data[offset++] = 'h';

	data[offset++] = TYPE_GET_ALL_STATUS;
	data[offset++] = count;

	data[offset++] = Serial::calcCrc(data, offset - 1);

	serial->sendData(data, offset);

	return NULL;

}

void *SmartHome::readThreadSerial_function() {
	int count = 0;

	if ((count = serial->getDataCount()) > 0) {

		/*printf("Data size > 0\n");
		 fflush(stdout);*/

		byte* buffer = new byte[count];
		serial->readSerialData(buffer, count);

		warningCount = 0;

		int offset = 0;
		if (buffer[offset++] == 'w') {
			if (buffer[offset++] == 'l') {
				if (buffer[offset++] == 'h') {
					int type = buffer[offset++];

					switch (type) {
					case TYPE_GET_ALL_STATUS: {
						printf("Read GET_ALL_STATUS\n");
						break;
					}
					case TYPE_CHANGE_STATUS: {
						int port = buffer[offset++];
						int value = buffer[offset++];
						if (Serial::checkCrc(buffer, offset)) {
							setPortValue(port, value);
						}
						break;
					}

					case TYPE_SET_ALL_STATUS: {
						int count = buffer[offset++];
						map<int, int> statusMap;
						int firstkey = -1;
						for (int i = 0; i < count; i++) {
							int key = buffer[offset++];

							if (firstkey == -1) {
								firstkey = key;
							}

							statusMap[key] = buffer[offset++];
						}
						if (Serial::checkCrc(buffer, offset)) {
							for (map<int, int>::iterator it = statusMap.begin();
									it != statusMap.end(); ++it) {

								setPortValue(it->first, it->second);
							}
						}

						break;
					}

					case TYPE_SET_CHRISTMAS_LIGHTS_STATUS: {
						int lightsOn = buffer[offset++];

						if (Serial::checkCrc(buffer, offset)) {

							christmasLightsManager->setWorking(lightsOn == 1);
						}

						break;
					}

					}
				}
			}
		}
	} else {
		warningCount++;

		/*printf("Data size == 0\n");
		 fflush(stdout);*/
	}

	return NULL;
}

void SmartHome::setPortValue(int port, int value) {
	gpio->setValue(port, value);
}

int SmartHome::charToInt(char c) {
	return c - '0';
}

void SmartHome::warningGpioMode() {
	christmasLightsManager->setWorking(true);

}

