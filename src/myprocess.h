#ifndef MYPROCESS_H
#define MYPROCESS_H

#include <functional>

#include <QObject>

class MyProcess : public QObject
{
  Q_OBJECT
public:
  explicit MyProcess(double value, QObject* parent = nullptr);
  ~MyProcess();

  void heavyLoadProcess(QWidget* requester, double value, std::function<void(double)> func);

protected:
  double value_;
};

#endif  // MYPROCESS_H
