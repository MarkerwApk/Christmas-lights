/*
 * ChristmasLightsManager.hpp
 *
 *  Created on: 16 gru 2015
 *      Author: marek
 */

#ifndef SRC_SANTACLAUSLIGHTSMANAGERMANAGER_HPP_
#define SRC_SANTACLAUSLIGHTSMANAGERMANAGER_HPP_

#include <stdio.h>
#include "Gpio.hpp"

#define STATE_START 0
#define STATE_ROAD 1
#define STATE_STARS 2
#define STATE_ALL 3
#define STATE_BLINKING_ROAD_AND_START 4
#define STATE_ROAD_OFF 5
#define STATE_STARS_OFF 6
#define STATE_SANTA_CLAUS_OFF 7

#define SANTA_CLAUS_LIGHTS_THREAD_SPEED 100

#define START_OFFSET 1000/SANTA_CLAUS_LIGHTS_THREAD_SPEED

#define ROAD_TIME 300/SANTA_CLAUS_LIGHTS_THREAD_SPEED

#define STARS_TIME ROAD_TIME

#define ALL_TIME 3000/SANTA_CLAUS_LIGHTS_THREAD_SPEED

#define BLINKING_ROAD_AND_STARS_TIME 10000/SANTA_CLAUS_LIGHTS_THREAD_SPEED

#define ROAD_OFF_TIME ROAD_TIME

#define STARS_OFF_TIME 2000/SANTA_CLAUS_LIGHTS_THREAD_SPEED

#define SANTA_CLAUS_OFF_TIME 2000/SANTA_CLAUS_LIGHTS_THREAD_SPEED

class SantaClausLightsManager {
public:
	SantaClausLightsManager();
	void * setWorking(bool working);
	void * santaClausLightsThread_function(Gpio* testGpio, int* offset,
			int* state, int*blinkStatus);
private:
	static bool working;

	void* setAllLightsStatus(Gpio* gpio, int status);

	void * setRoadStatus(Gpio* gpio, int status);

	void * setStarsStatus(Gpio* gpio, int status);

	void * setSantaClausStatus(Gpio* gpio, int status);
};

#endif /* SRC_CHRISTMASLIGHTSMANAGER_HPP_ */
