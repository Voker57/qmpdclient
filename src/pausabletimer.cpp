#include "pausabletimer.h"

PausableTimer::PausableTimer() : QTimer(), startTime(0) {
	setInterval(0);
}

void PausableTimer::start() {
	startTime = time(NULL);
	this->QTimer::start(interval());
}

void PausableTimer::pause() {
	if (isActive()) {
		stop();
		time_t elapsedTime = time(NULL) - startTime;
		setInterval(interval() - elapsedTime*1000);
	}
}

void PausableTimer::resume() {
	if (!isActive()) {
		startTime = time(NULL);
		QTimer::start(interval());
	}
}
