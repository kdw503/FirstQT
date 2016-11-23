#include "firstqt.h"

void Worker::doWork() {
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
			if (i == 10)i = i;
		emit newLogMsgReady(".");
		//			qDebug(".");
		QApplication::instance()->processEvents();
		QThread::msleep(1000);
	} while (get_runWork());
	emit resultReady("Worker");
}

void Worker::doMemcpy_g() {
	char *allBuf, *volume;
	size_t size = (long long)2 * 1000000000;// (long long)4194304 * 2 * 200;
	Timer_g gt;
	QString msg;
	QTextStream time_string(&msg);

	allBuf = (char*)_aligned_malloc(size, 4 * 1024);
	volume = (char*)_aligned_malloc(size, 4 * 1024);

//	allBuf[100] = 1;
//	emit newLogMsgReady((int)allBuf[100]);

//	msg.clear();
//	msg.sprintf("%d\n", allBuf[100]);
//	msg = "allBuf[100] : " + msg;
//	emit newLogMsgReady(msg);

	gt.start(); // reset clock 0
	double startTime = gt.read();
	msg.clear();
	time_string << startTime;
	msg = "memcpy_g start time : " + msg;
	emit newLogMsgReady(msg);

	memcpy_g(volume, allBuf, size);

	double endTime = gt.read();
	msg.clear();
	time_string << endTime;
	msg = "memcpy_g end time : " + msg;
	emit newLogMsgReady(msg);

	_aligned_free(allBuf);
	_aligned_free(volume);
	allBuf = nullptr;
	volume = nullptr;

	msg.clear();
	time_string << endTime - startTime;
	msg = "memcpy_g elaspe time : " + msg;
	emit resultReady(msg);
}


void Worker::doMemcpy() {
	char *allBuf, *volume;
	size_t size = (long long)2 * 1000000000;// (long long)4194304 * 2 * 200;
	Timer_g gt;
	QString msg;
	QTextStream time_string(&msg);

	allBuf = (char*)malloc(size);
	volume = (char*)malloc(size);

	allBuf[100] = 1;

	double startTime = gt.read();
	time_string << startTime;
	msg = "memcpy start time : " + msg;
	emit newLogMsgReady(msg);

	memcpy(volume, allBuf, size);

	double endTime = gt.read();
	msg.clear();
	time_string << endTime;
	msg = "memcpy end time : " + msg;
	emit newLogMsgReady(msg);

	free(allBuf);
	free(volume);
	allBuf = nullptr;
	volume = nullptr;

	msg.clear();
	time_string << endTime - startTime;
	msg = "memcpy elaspe time : " + msg;
	emit resultReady(msg);
}
