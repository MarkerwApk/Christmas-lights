/*
 * Serial.cpp
 *
 *  Created on: 5 mar 2015
 *      Author: marek
 */
#include "Serial.hpp"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cmath>
#include <sys/ioctl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

Serial::Serial() {
	connect();
}
void Serial::connect() {
	if (serialOpen("/dev/ttyO4") < 0) {
		fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
		return;
	}

}

int Serial::serialOpen(const char* devicePath) {
	if ((fd = open(devicePath, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK))
			< 0) {
		printf("Could not open port.");
		return -1;
	}

	fcntl(fd, F_SETFL, O_RDWR);

	struct termios options;

	cfmakeraw(&options);

	if (tcgetattr(fd, &options) != 0) {
		printf("Unable to retrieve port attributes.");

		return -1;
	}
	if (cfsetispeed(&options, B9600) < 0) {
		printf("Input baud rate not successfully set.");
	}

	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);

	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	options.c_oflag &= ~OPOST;

	options.c_cc[VMIN] = 0;
	options.c_cc[VTIME] = 100;

	if (tcsetattr(fd, TCSANOW, &options) < 0) {
		printf("Options not successfully set.");
	}

	int status;

	ioctl(fd, TIOCMGET, &status);

	status |= TIOCM_DTR;
	status |= TIOCM_RTS;

	ioctl(fd, TIOCMSET, &status);

	usleep(10000);

	return 0;

}
int Serial::calcCrc(int data[], int len) {
	signed char crc = 0;
	for (unsigned int i = 0; i < len; i++) {
		crc = crc ^ data[i];
	}
	return crc;
}

bool Serial::checkCrc(byte* data, int offset) {
	byte readedCrc = data[offset];
	byte crc = 0;
	for (unsigned int i = 0; i < offset; i++) {
		crc = crc ^ data[i];
	}
	return crc == readedCrc;
}

void Serial::sendData(int test[], int len) {
	fflush(stdout);
	for (unsigned int i = 0; i < len; i++) {
		write(fd, &test[i], 1);
	}
	fflush(stdout);
}

int Serial::getDataCount() {
	int bytes_avail;
	ioctl(fd, FIONREAD, &bytes_avail);
	return bytes_avail;

}
byte* Serial::readSerialData(byte* &data, int count) {

	read(fd, data, count);
	fflush(stdout);
	return data;

}

