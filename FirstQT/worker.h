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
	void doWork() {
		if (get_runWork())
			return;
//		QString msg = QString("ID of thread where %1 object reside : %2")
//			.arg("woker").arg((long long)(QThread::currentThreadId()));
		QString msg;
		msg.sprintf("ID of thread where worker object reside : 0x%x", (long long)(QThread::currentThreadId()));
		set_runWork(1);
		emit newLogMsgReady(msg);
		emit newLogMsgReady("Worker is running..\n");
		do {
			for (int i = 0; i < 100; i++)
				if(i==10)i=i;
			emit newLogMsgReady(".");
//			qDebug(".");
			QApplication::instance()->processEvents();
			QThread::msleep(1000);
		} while(get_runWork());
		emit resultReady("Worker");
	}
	void stopWork() {
		set_runWork(0);
	}

signals:
	void newLogMsgReady(const QString &result);
	void resultReady(const QString &result);
};

