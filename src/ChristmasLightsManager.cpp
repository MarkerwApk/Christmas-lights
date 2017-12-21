/*
 * ChristmasLightsManager.cpp
 *
 *  Created on: 16 gru 2015
 *      Author: marek
 */

#include "ChristmasLightsManager.hpp"
#include <pthread.h>
#include <unistd.h>
#include <cmath>
#include <time.h>
#include "Pins.hpp"

bool ChristmasLightsManager::working = true;
int ChristmasLightsManager::blinkTime = NEXT_BLINK_STATUS; //Must be static for modulo operation
ChristmasLightsManager::ChristmasLightsManager() {

}

void *ChristmasLightsManager::setWorking(bool working) {
	this->working = working;

	return NULL;
}

void *ChristmasLightsManager::christmasLightsThread_function(Gpio* testGpio,
		int* offset, int* state, int* blinkPosition, int*blinkStatus,
		int* blinkAcceleration) {
	/*
	 printf("Thread before all\n");
	 fflush(stdout);

	 printf("Thread before if\n");
	 fflush(stdout);
	 */

	if (!working) {
		*offset = 0;
		*blinkStatus = 0;
		*blinkAcceleration = BLINK_ACCELERATION_START;
		*blinkPosition = 0;
		*state = STATE_START;

		setAllLightsStatus(testGpio, 0);
	} else {

		switch (*state) {
		case STATE_START: {
			/*printf("Thread case start %d\n", *offset);
			 fflush(stdout);*/
			setAllLightsStatus(testGpio, 1);

			if (*offset < NEXT_HOP)
				(*offset)++;
			else {
				*offset = 0;
				*state = STATE_BLINK_SINGLY;
			}

			break;
		}
		case STATE_BLINK_SINGLY: {
			setBlinkStatus(testGpio, *blinkPosition, *blinkStatus);

			if ((*offset) < NEXT_HOP) {
				(*offset)++;

				if ((*offset) % blinkTime == 0) {
					*blinkStatus = std::abs((*blinkStatus) - 1);
				}
			} else {
				*offset = 0;
				*blinkStatus = 0;

				if ((*blinkPosition) < CHRISTMAS_LIGHTS_COUNT - 1) {
					(*blinkPosition)++;
				} else {
					*blinkPosition = 0;
					*state = STATE_BLINK_PARITY;
				}
			}

			break;
		}
		case STATE_BLINK_PARITY: {
			setBlinkParityStatus(testGpio, *blinkPosition, *blinkStatus);

			if ((*offset) < NEXT_HOP) {
				(*offset)++;

				if ((*offset) % blinkTime == 0) {
					*blinkStatus = std::abs((*blinkStatus) - 1);
				}
			} else {
				*offset = 0;
				*blinkStatus = 0;

				if ((*blinkPosition) < 2) {
					(*blinkPosition)++;
				} else {
					*blinkPosition = 0;
					*state = STATE_BLINK_NEXT;
				}
			}

			break;
		}
		case STATE_BLINK_NEXT: {
			setBlinkStatus(testGpio, *blinkPosition, 0);

			if ((*blinkAcceleration) > 0) {
				(*offset)++;

				//printf("%d, %d\n", offset, blinkPosition);
				//fflush(stdout);

				if ((*offset) % *blinkAcceleration == 0) {
					if ((*blinkPosition) < CHRISTMAS_LIGHTS_COUNT - 1)
						(*blinkPosition)++;
					else {
						*blinkPosition = 0;
						(*blinkAcceleration)--;
					}
				}
			} else {
				*offset = 0;
				*blinkStatus = 0;
				*blinkAcceleration = BLINK_ACCELERATION_START;
				*blinkPosition = 0;
				*state = STATE_BLINK_NEXT_OFF;

			}

			break;
		}

		case STATE_BLINK_NEXT_OFF: {
			setBlinkStatusOff(testGpio, *blinkPosition, 1);

			if ((*blinkAcceleration) > 0) {
				(*offset)++;

				//printf("%d, %d\n", offset, blinkPosition);
				//fflush(stdout);

				if ((*offset) % *blinkAcceleration == 0) {
					if ((*blinkPosition) < CHRISTMAS_LIGHTS_COUNT - 1)
						(*blinkPosition)++;
					else {
						*blinkPosition = 0;
						(*blinkAcceleration)--;
					}
				}
			} else {
				*offset = 0;
				*blinkStatus = 0;
				*blinkAcceleration = BLINK_ACCELERATION_START;
				*blinkPosition = 0;
				*state = STATE_BLINK_INSIDE;

			}

			break;
		}
		case STATE_BLINK_INSIDE: {
			setBlinkInside(testGpio, *blinkPosition);

			if ((*blinkAcceleration) > 0) {
				(*offset)++;

				//printf("%d, %d\n", offset, blinkPosition);
				//fflush(stdout);

				if ((*offset) % *blinkAcceleration == 0) {
					if ((*blinkPosition) < CHRISTMAS_LIGHTS_COUNT / 2 - 1)
						(*blinkPosition)++;
					else {
						*blinkPosition = 0;
						(*blinkAcceleration)--;
					}
				}
			} else {
				*offset = 0;
				*blinkStatus = 0;
				*blinkAcceleration = BLINK_ACCELERATION_START;
				*blinkPosition = 0;
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

void * ChristmasLightsManager::setAllLightsStatus(Gpio* gpio, int status) {
	//printf("Thread All status\n");
	fflush(stdout);

	gpio->setValue(OUTPUT_CHRISTMAS_LIGHTS_0_PORT, status);
	gpio->setValue(OUTPUT_CHRISTMAS_LIGHTS_1_PORT, status);
	//gpio->setValue(OUTPUT_CHRISTMAS_LIGHTS_2_PORT, status);

	return NULL;
}

void * ChristmasLightsManager::setBlinkStatus(Gpio* gpio, int position,
		int status) {

	for (int i = 0; i < CHRISTMAS_LIGHTS_COUNT; i++) {
		if (i == position) {
			gpio->setValue(getPortByPosition(position), status);
		} else {
			gpio->setValue(getPortByPosition(i), 1);
		}

	}

	return NULL;
}

void * ChristmasLightsManager::setBlinkStatusOff(Gpio* gpio, int position,
		int status) {

	for (int i = 0; i < CHRISTMAS_LIGHTS_COUNT; i++) {
		if (i == position) {
			gpio->setValue(getPortByPosition(position), status);
		} else {
			gpio->setValue(getPortByPosition(i), 0);
		}

	}

	return NULL;
}

void * ChristmasLightsManager::setBlinkInside(Gpio* gpio, int position) {

	for (int i = 0; i < CHRISTMAS_LIGHTS_COUNT / 2; i++) {
		if (i == position) {
			gpio->setValue(getPortByPosition(position), 1);
			gpio->setValue(
					getPortByPosition((CHRISTMAS_LIGHTS_COUNT - 1) - position),
					1);
		} else {
			gpio->setValue(getPortByPosition(i), 0);
			gpio->setValue(getPortByPosition((CHRISTMAS_LIGHTS_COUNT - 1) - i),
					0);
		}

	}

	return NULL;
}

void * ChristmasLightsManager::setBlinkParityStatus(Gpio* gpio, int position,
		int status) {

	for (int i = 0; i < CHRISTMAS_LIGHTS_COUNT; i++) {
		if (i % 2 == position) {
			gpio->setValue(getPortByPosition(i), status);
		} else {
			gpio->setValue(getPortByPosition(i), 1);
		}
	}

	return NULL;
}
int ChristmasLightsManager::getPortByPosition(int position) {
	switch (position) {
	case 0: {
		return OUTPUT_CHRISTMAS_LIGHTS_0_PORT;

	}
	case 1: {
		return OUTPUT_CHRISTMAS_LIGHTS_1_PORT;

	}
	default:
		return OUTPUT_CHRISTMAS_LIGHTS_0_PORT;
	}
}

