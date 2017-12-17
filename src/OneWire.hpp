/*
 * OneWire.hpp
 *
 *  Created on: 15 mar 2015
 *      Author: markerwapk
 */

#ifndef ONEWIRE_HPP_
#define ONEWIRE_HPP_

#define BOILER_TEMP "10-000802d5f4f2"
#define OUTSIDE_TEMP "28-03146a5059ff"

#define BOILER_CYCLE_TEMP "28-000006dd9525"

#define COAL_FURNACE "28-000006dca87e"

#define OIL_FURNACE "28-000006de6ab8"

#define MAIN_CYCLE_TEMP "28-000006de5062"

#define MAIN_CYCLE_BACK_TEMP "28-000006dd6745"

#define ONE_WIRE_BEGIN_PATH "/sys/bus/w1/devices/"
#define ONE_WIRE_BEGIN_VALUE "/w1_slave"

#define ONE_WIRE_VALUE_PATH "/temp"

#include "string.h"
#include "string"
class OneWire {
public:
	int readValue(std::string id);
	int getValue();

private:
	int writeToFile(int value);
};

#endif /* ONEWIRE_HPP_ */
