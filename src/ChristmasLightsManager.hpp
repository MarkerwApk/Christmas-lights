/*
 * ChristmasLightsManager.hpp
 *
 *  Created on: 16 gru 2015
 *      Author: marek
 */

#ifndef SRC_CHRISTMASLIGHTSMANAGER_HPP_
#define SRC_CHRISTMASLIGHTSMANAGER_HPP_

#include <stdio.h>
#include "Gpio.hpp"

#define STATE_START 0
#define STATE_BLINK_SINGLY 1
#define STATE_BLINK_PARITY 2
#define STATE_BLINK_NEXT 3
#define STATE_BLINK_NEXT_OFF 4
#define STATE_BLINK_INSIDE 5

#define CHRISTMAS_LIGHTS_THREAD_SPEED 100
#define STATE_TIME 10*1000
#define BLINK_SPEED 500

#define NEXT_HOP STATE_TIME/CHRISTMAS_LIGHTS_THREAD_SPEED
#define NEXT_BLINK_STATUS BLINK_SPEED/CHRISTMAS_LIGHTS_THREAD_SPEED

#define BLINK_ACCELERATION_START 15
#define CHRISTMAS_LIGHTS_COUNT 3

class ChristmasLightsManager {
public:
	ChristmasLightsManager();
	void * setWorking(bool working);
	void * christmasLightsThread_function(Gpio* testGpio, int* offset,
			int* state, int* blinkPosition, int*blinkStatus,
			int* blinkAcceleration);
private:

	static bool working;

	void* setBlinkStatus(Gpio* gpio, int position, int status);
	void* setBlinkStatusOff(Gpio* gpio, int position, int status);
	void* setBlinkInside(Gpio* gpio, int position);
	void* setBlinkParityStatus(Gpio* gpio, int position, int status);
	void* setAllLightsStatus(Gpio* gpio, int status);

	int getPortByPosition(int position);
	static int blinkTime;
};

#endif /* SRC_CHRISTMASLIGHTSMANAGER_HPP_ */
