#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <iostream>
#include <locale>
#include <codecvt>
#include <string>

#include "mywidget.h"

#include <client/crashpad_client.h>

void initializeCrashpad()
{
  const auto dataDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/crashpad_test";
  const auto db = dataDir + "/metrics/db";
  const auto metrics = dataDir + "/crash/metrics";
  std::cout << "Data dir: " << db.toStdString() << std::endl;
  std::cout << "Crash dir: " << metrics.toStdString() << std::endl;
  std::vector<std::string> args;

  QDir().mkpath(db);
  QDir().mkpath(metrics);

#ifdef WIN32
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  std::wstring crash_pad_handler(L"crashpad_handler.exe");
  std::wstring database(converter.from_bytes(db.toStdString()));
  std::wstring metric(converter.from_bytes(metrics.toStdString()));
#else
  std::string crash_pad_handler("crashpad_handler");
  std::string database(db.toStdString());
  std::string metric(metrics.toStdString());
#endif

  crashpad::CrashpadClient cpc;
  cpc.StartHandler(base::FilePath(crash_pad_handler),     // Relative path to a Crashpad handler executable
                   base::FilePath(database),       // Directory to Crashpad database
                   base::FilePath(metric),  // Directory where metrics files can be stored
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
