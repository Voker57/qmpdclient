#ifndef PAUSABLETIMER_H
#define PAUSABLETIMER_H

#include <QTimer>
#include <time.h>

class PausableTimer : public QTimer {
	Q_OBJECT
	public:
		PausableTimer();
		void start();
		void pause();

	private:
		time_t startTime;
};

#endif
