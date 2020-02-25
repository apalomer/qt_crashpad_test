#include "myprocess.h"

#include <thread>
#include <signal.h>

#include <QDebug>
#include <QProgressDialog>
#include <QtConcurrent/QtConcurrent>
#include <QLabel>

MyProcess::MyProcess(double value, QObject* parent) : QObject(parent), value_(value)
{
}

MyProcess::~MyProcess()
{
}

void MyProcess::heavyLoadProcess(QWidget* requester, double value, std::function<void(double)> func)
{
  // Progress dialog
  QProgressDialog* progress = new QProgressDialog("Heavy computation", "", 0, 0, requester);
  progress->setWindowTitle(requester->windowTitle());
  progress->setWindowFlags((progress->windowFlags() | Qt::CustomizeWindowHint) &
                           ~Qt::WindowCloseButtonHint);  // Hide close button
  progress->setWindowModality(Qt::WindowModal);
  progress->setCancelButton(nullptr);
  progress->setMaximum(0);
  progress->show();

  QtConcurrent::run([this, value, func, progress]() {
    QLabel* l;
    l->setText("a");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    func(value + value_);
    progress->close();
    progress->deleteLater();
    qDebug() << "Done!";
  });
}
