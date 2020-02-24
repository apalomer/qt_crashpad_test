#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <iostream>
#include "mywidget.h"

#include <client/crashpad_client.h>

void initializeCrashpad()
{
  const auto dataDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  const auto db = dataDir + "/metrics/db";
  const auto metrics = dataDir + "/crash/metrics";
  std::cout << "Data dir: " << dataDir.toStdString() << std::endl;
  std::vector<std::string> args;

  QDir().mkpath(db);
  QDir().mkpath(metrics);

  crashpad::CrashpadClient cpc;
  cpc.StartHandler(base::FilePath("crashpad_handler"),     // Relative path to a Crashpad handler executable
                   base::FilePath(db.toStdString()),       // Directory to Crashpad database
                   base::FilePath(metrics.toStdString()),  // Directory where metrics files can be stored
                   "",                                     // URL of the HTTP upload server
                   {},                                     // Annonations to include in the crash report
                   args,
                   true,  // The program will be restarted if it crash
                   true);
}

int main(int argc, char** argv)
{
  initializeCrashpad();
  QApplication app(argc, argv);
  MyWidget* w = new MyWidget;
  w->show();
  return app.exec();
}
