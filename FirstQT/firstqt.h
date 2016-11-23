#pragma once

#include <QtWidgets/QMainWindow>
#include <qthread.h>
#include "ui_firstqt.h"
#include "worker.h"
#include "workerthread.h"

#include "timer_g.hpp"
#include "memcpy_g.h"
#include <assert.h>

class FirstQT : public QMainWindow
{
    Q_OBJECT
	QThread workerThread;
public:
    FirstQT(QWidget *parent = Q_NULLPTR);
	~FirstQT() {
		workerThread.quit();
		workerThread.wait();
	}

private:
    Ui::FirstQTClass ui;

signals:
	void testSignal(const QString &str);
	void workerOperate();
	void workerStop();
	void workerThreadOperate(const bool &);
	void workerThreadStop();
	void workerMemcpy_g();
	void workerMemcpy();

private slots:
	void on_actionOpen_triggered();
	void on_actionSave_triggered();
	void on_actionTest_triggered();
	void on_actionQuit_triggered();
	void on_workerStartButton_clicked();
	void on_workerEndButton_clicked();
	void on_workerThreadStartButton_clicked();
	void on_workerThreadEndButton_clicked();
	void on_memcpy_g_Button_clicked();
	void on_memcpyButton_clicked();
	
	void exit();
	void handleResults(const QString&);
	void appendLog(const QString& );
	void appendLog(const int&);

};
