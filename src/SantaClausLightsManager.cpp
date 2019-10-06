#include "SantaClausLightsManager.hpp"
#include <pthread.h>
#include <unistd.h>
#include <cmath>
#include <time.h>
#include "Pins.hpp"

bool SantaClausLightsManager::working = true;
SantaClausLightsManager::SantaClausLightsManager() {

}

void *SantaClausLightsManager::setWorking(bool working) {
	this->working = working;

	return NULL;
}

void *SantaClausLightsManager::santaClausLightsThread_function(Gpio* testGpio,
		int* offset, int* state) {

	if (!working) {
		*offset = 0;
		*state = STATE_START;

		setAllLightsStatus(testGpio, 0);
	} else {

		switch (*state) {
		case STATE_START: {
			setAllLightsStatus(testGpio, 0);

			if (*offset < START_OFFSET)
				(*offset)++;
			else {
				*offset = 0;
				*state = STATE_ROAD;
			}

			break;
		}
		case STATE_ROAD: {
			setRoadStatus(testGpio, 1);

			if (*offset < ROAD_TIME)
				(*offset)++;
			else {
				*offset = 0;
				*state = STATE_STARS;
			}

			break;
		}
		case STATE_STARS: {
			setStarsStatus(testGpio, 1);

			if (*offset < STARS_TIME)
				(*offset)++;
			else {
				*offset = 0;
				*state = STATE_ALL;
			}

			break;
		}
		case STATE_ALL: {
			setAllLightsStatus(testGpio, 1);

			if (*offset < ALL_TIME)
				(*offset)++;
			else {
				*offset = 0;
				*state = STATE_ROAD_OFF;
			}

			break;
		}

		case STATE_ROAD_OFF: {
			setRoadStatus(testGpio, 0);
			setStarsStatus(testGpio, 1);

			if ((*offset) < ROAD_OFF_TIME) {
				(*offset)++;

			} else {
				*offset = 0;

				*state = STATE_STARS_OFF;
			}

			break;
		}
		case STATE_STARS_OFF: {
			setStarsStatus(testGpio, 0);

			if ((*offset) < STARS_OFF_TIME) {
				(*offset)++;
			} else {
				*offset = 0;
				*state = STATE_SANTA_CLAUS_OFF;
			}

			break;
		}
		case STATE_SANTA_CLAUS_OFF: {
			setSantaClausStatus(testGpio, 1);

			if ((*offset) < SANTA_CLAUS_OFF_TIME) {
				(*offset)++;

			} else {
				*offset = 0;

				*state = STATE_START;
			}

			break;
		}
		}

	}

	//printf("Thread All status sfter sleep\n");
	fflush(stdout);

	return NULL;
}

void * SantaClausLightsManager::setAllLightsStatus(Gpio* gpio, int status) {
	//printf("Thread All status\n");
	fflush(stdout);

	gpio->setValue(OUTPUT_CHRISTMAS_LIGHTS_SANTA_CLAUS_ROAD, status);
	gpio->setValue(OUTPUT_CHRISTMAS_LIGHTS_SANTA_CLAUS, status);

	return NULL;
}
void * SantaClausLightsManager::setRoadStatus(Gpio* gpio, int status) {
	//printf("Thread All status\n");
	fflush(stdout);

	gpio->setValue(OUTPUT_CHRISTMAS_LIGHTS_SANTA_CLAUS_ROAD, status);

	return NULL;
}
void * SantaClausLightsManager::setStarsStatus(Gpio* gpio, int status) {
	//printf("Thread All status\n");
	fflush(stdout);

	//gpio->setValue(OUTPUT_CHRISTMAS_LIGHTS_SANTA_CLAUS_STARS, status);

	return NULL;
}
void * SantaClausLightsManager::setSantaClausStatus(Gpio* gpio, int status) {
	//printf("Thread All status\n");
	fflush(stdout);

	gpio->setValue(OUTPUT_CHRISTMAS_LIGHTS_SANTA_CLAUS, status);

	return NULL;
}
