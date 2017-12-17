/*
 * Gpio.hpp
 *
 *  Created on: 10 mar 2015
 *      Author: markerwapk
 */

#ifndef GPIO_HPP_
#define GPIO_HPP_

#define GPIO_PATH_BEGIN "/sys/class/gpio/gpio"
#define GPIO_PATH_VALUE "/value"
#define GPIO_PATH_ACTIVE "/active_low"
class Gpio {
public:
	Gpio();

	int readGpio(int port);
	int setActive(int port, int value);
	int setValue(int port, int value);
};

#endif /* GPIO_HPP_ */
