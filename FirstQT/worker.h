#pragma once
#include <qthread.h>
#include <qmutex.h>
#include <qtimer.h>
#include <qapplication.h>
#include <QTextStream>
#include <QDebug>


class Worker : public QObject {
	Q_OBJECT
//	QThread workerThread;
	QMutex mutex;
	bool runWork = 0;
public:
	bool get_runWork() {
		QMutexLocker locker(&mutex);
		return runWork;
	}
	void set_runWork(bool running) {
		QMutexLocker locker(&mutex);
		runWork = running;
	}

public slots:
	void doWork();
	void doMemcpy_g();
	void doMemcpy();

	void stopWork() {
		set_runWork(0);
	}

signals:
	void newLogMsgReady(const QString &msg);
	void newLogMsgReady(const int &result);
	void resultReady(const QString &result);
};

