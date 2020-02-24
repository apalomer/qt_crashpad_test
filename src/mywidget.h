#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "myprocess.h"

namespace Ui
{
class MyWidget;
}

class MyWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MyWidget(QWidget *parent = nullptr);
  ~MyWidget();

public slots:

  void setResult(double result);

private slots:
  void on_pushButton_clicked();

private:
  Ui::MyWidget *ui;

  MyProcess *myprocess_ = nullptr;
};

#endif  // MYWIDGET_H
