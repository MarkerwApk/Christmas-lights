/*
 * Start.cpp

 *
 *  Created on: 5 mar 2015
 *      Author: marek
 */

#include "SmartHome.hpp"

#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>

void skeleton_daemon() {
	pid_t pid;

	/* Fork off the parent process */
	pid = fork();

	/* An error occurred */
	if (pid < 0)
		exit(EXIT_FAILURE);

	/* Success: Let the parent terminate */
	if (pid > 0)
		exit(EXIT_SUCCESS);

	/* On success: The child process becomes session leader */
	if (setsid() < 0)
		exit(EXIT_FAILURE);

	/* Catch, ignore and handle signals */
	//TODO: Implement a working signal handler */
	signal(SIGCHLD, SIG_IGN);
	signal(SIGHUP, SIG_IGN);

	/* Fork off for the second time*/
	pid = fork();

	/* An error occurred */
	if (pid < 0)
		exit(EXIT_FAILURE);

	/* Success: Let the parent terminate */
	if (pid > 0)
		exit(EXIT_SUCCESS);

	/* Set new file permissions */
	umask(0);

	/* Change the working directory to the root directory */
	/* or another appropriated directory */
	chdir("/");

	/* Close all open file descriptors */
	int x;
	for (x = sysconf(_SC_OPEN_MAX); x > 0; x--) {
		close(x);
	}

	/* Open the log file */
	openlog("firstdaemon", LOG_PID, LOG_DAEMON);
}

int main() {
//	skeleton_daemon();


	//syslog(LOG_NOTICE, "First daemon started.");

	SmartHome* home = new SmartHome();
	home->start();

	//syslog(LOG_NOTICE, "First daemon terminated.");
	//closelog();

	return 0;
}
