#include "firstqt.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

FirstQT::FirstQT(QWidget *parent)
	: QMainWindow(parent)
{
	QThread*workerThread = new QThread;
	Worker *worker = new Worker;

	worker->moveToThread(workerThread);
	connect(this, SIGNAL(workerOperate()), worker, SLOT(doWork()));
	connect(this, SIGNAL(workerStop()), worker, SLOT(stopWork()));
//	connect(workerThread, SIGNAL(started()), worker, SLOT(process()));
	connect(workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
	connect(worker, SIGNAL(newLogMsgReady(QString)), this, SLOT(appendLog(QString)));
	connect(worker, SIGNAL(newLogMsgReady(int)), this, SLOT(appendLog(int)));
	connect(worker, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));
//	connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	connect(workerThread, SIGNAL(finished()), workerThread, SLOT(quit()));
	connect(this, SIGNAL(workerMemcpy_g()), worker, SLOT(doMemcpy_g()));
	connect(this, SIGNAL(workerMemcpy()), worker, SLOT(doMemcpy()));

	workerThread->start();

	ui.setupUi(this);

	//to overcome qt designer's incapability
	addDockWidget(Qt::TopDockWidgetArea, ui.dockWidget);

	connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(exit()));
}

void FirstQT::on_actionOpen_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
		tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

	if (!fileName.isEmpty()) {
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly)) {
			QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
			return;
		}
		QTextStream in(&file);
		ui.textEdit->setText(in.readAll());
		file.close();
	}
}

void FirstQT::on_actionSave_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
		tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

	if (!fileName.isEmpty()) {
		QFile file(fileName);
		if (!file.open(QIODevice::WriteOnly)) {
			// error message
		}
		else {
			QTextStream stream(&file);
			stream << ui.textEdit->toPlainText();
			stream.flush();
			file.close();
		}
	}
}

void FirstQT::on_actionQuit_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
		tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

	if (!fileName.isEmpty()) {
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly)) {
			QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
			return;
		}
		QTextStream in(&file);
		ui.textEdit->setText(in.readAll());
		file.close();
	}
}

void setDockwigetByAction(QAction* act, QDockWidget* widget)
{
	bool visible = act->isChecked();
	widget->setVisible(visible);
	if (visible) widget->raise();
}

void FirstQT::on_actionTest_triggered()
{
	setDockwigetByAction(ui.actionTest, ui.dockWidget);
}

void FirstQT::exit() {
	qDebug("push button clicked\n");
	QApplication::exit();
}

void FirstQT::handleResults(const QString &result)
{
	QString msg;
	msg = result + " end\n";
	appendLog(msg);
}

void FirstQT::appendLog(const QString& msg)
{
//	static int nAppendingLog = 0;
	//if(nAppendingLog>=1000) {
//	if (nAppendingLog >= ui.spinBoxMaxNumOfLinesInLog->value()) {
//		ui.textEditLog->clear();
//		nAppendingLog = 0;
//	}

	ui.textEdit->append(msg);
//	nAppendingLog++;
}


void FirstQT::appendLog(const int& result)
{
	QString msg;
	msg.sprintf("%d", result);

	ui.textEdit->append(msg);
}

void FirstQT::on_workerStartButton_clicked()
{
	QString msg;
	QTextStream id_string(&msg);

	id_string << QThread::currentThreadId();
//	qDebug() << "From worker thread: " << msg;
	//	id_string >> msg;
	//	msg << id_string; // this doesn't work
	msg = "Caller of worker object ID : " + msg;
	appendLog(msg);
	emit workerOperate();
}

void FirstQT::on_workerEndButton_clicked()
{
	emit workerStop();
}

void FirstQT::on_workerThreadStartButton_clicked()
{
	WorkerThread *workerThread = new WorkerThread();
//	connect(workerThread, SIGNAL(workerThreadOperate(QString)), this, SLOT(handleResults(QString)));
	connect(this, SIGNAL(workerThreadStop()), workerThread, SLOT(stopWork()));
	connect(workerThread, SIGNAL(newLogMsgReady(QString)), this, SLOT(appendLog(QString)));
	connect(workerThread, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));
	connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
	workerThread->start();
}

void FirstQT::on_workerThreadEndButton_clicked()
{
	emit workerThreadStop();
}

void FirstQT::on_memcpy_g_Button_clicked()
{
	emit workerMemcpy_g();
}

void FirstQT::on_memcpyButton_clicked()
{
	emit workerMemcpy();
}
