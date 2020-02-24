#include "mywidget.h"
#include "ui_mywidget.h"

#include <QDebug>
#include <QDoubleSpinBox>
#include <QProgressDialog>

#include <functional>

MyWidget::MyWidget(QWidget* parent) : QWidget(parent), ui(new Ui::MyWidget), myprocess_(new MyProcess(-3.45))
{
  ui->setupUi(this);
}

MyWidget::~MyWidget()
{
  delete ui;
}

void MyWidget::on_pushButton_clicked()
{
  // Call
  myprocess_->heavyLoadProcess(this, ui->value_doubleSpinBox->value(),
                               std::bind(&MyWidget::setResult, this, std::placeholders::_1));
}

void MyWidget::setResult(double result)
{
  ui->result_doubleSpinBox->setValue(result);
  qDebug() << "Result set to: " << result;
}
