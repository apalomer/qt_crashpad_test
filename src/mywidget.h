#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "myprocess.h"

#include "project_export.h"

#ifdef MYWIDGET
#define MYWIDGETEXPORT PROJECT_EXPORT
#else
#define MYWIDGETEXPORT PROJECT_IMPORT
#endif

namespace Ui
{
class MyWidget;
}

class MYWIDGETEXPORT MyWidget : public QWidget
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
