#pragma once
#include <qthread.h>

class WorkerThread : public QThread
{
	Q_OBJECT
		bool runWork = 0;
	void run(const bool &running) { // this is called when workerthread start
		runWork = running;
		emit newLogMsgReady("Worker thread is running..\n");
		do {
			for (int i = 0; i < 1000; i++);
				emit newLogMsgReady(".");
		} while (runWork);
		emit resultReady("Worker thread");
	}
	void stopWork() {
		runWork = 0;
	}
signals:
	void newLogMsgReady(const QString &s);
	void resultReady(const QString &s);
};


