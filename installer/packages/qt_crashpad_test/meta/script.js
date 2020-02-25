function Component()
{
  // default constructor
  component.loaded.connect(this, Component.prototype.installerLoaded);
}

Component.prototype.installerLoaded = function () 
{
  if (systemInfo.productType !=  "windows")
  {
    installer.addWizardPage( component, "UnixDependencies", QInstaller.ReadyForInstallation )

    var currentWidget = gui.pageByObjectName("DynamicUnixDependencies");
    if (currentWidget != null)
    {
        currentWidget.complete = gui.pageWidgetByObjectName("DynamicUnixDependencies").checkBox.checked
    }
    component.userInterface( "UnixDependencies" ).checkBox.clicked.connect(function(){
      var currentWidget = gui.pageByObjectName("DynamicUnixDependencies");
      if (currentWidget != null)
      {
        currentWidget.complete = gui.pageWidgetByObjectName("DynamicUnixDependencies").checkBox.checked;
      }
    });
  }
} 

Component.prototype.createOperations = function()
{
  component.createOperations();

  if (systemInfo.currentCpuArchitecture != "x86_64")
  {
      installer.setValue("FinishedText", "<font color='red' size=3>Qt crashpad test can only be installed in 64bit machines.</font>");
      installer.setDefaultPageVisible(QInstaller.TargetDirectory, false);
      installer.setDefaultPageVisible(QInstaller.ReadyForInstallation, false);
      installer.setDefaultPageVisible(QInstaller.ComponentSelection, false);
      installer.setDefaultPageVisible(QInstaller.StartMenuSelection, false);
      installer.setDefaultPageVisible(QInstaller.PerformInstallation, false);
      installer.setDefaultPageVisible(QInstaller.LicenseCheck, false);
      gui.clickButton(buttons.NextButton);
  }
    
  var cm_runtime;
  if (systemInfo.productType ==  "windows")
  {
    component.addOperation("Execute","{0,3010}","@TargetDir@/VC_redist.x64.exe","/quiet","/norestart");
    component.addOperation("CreateShortcut",
                   "@TargetDir@/bin/main.exe",
                   "@StartMenuDir@/QtCrashpadTest.lnk")
    component.addOperation("CreateShortcut",
                   "@TargetDir@/bin/main.exe",
                   "@DesktopDir@/QtCrashpadTest.lnk")
  }
  else
  {     
    var tgtdir0 = installer.value("TargetDir")
    var tgtdir = tgtdir0.replace(" ","\\ ")
    component.addOperation("AppendFile","@TargetDir@/qt_crashpad_test.desktop","Path=@TargetDir@/bin\n")
    component.addOperation("AppendFile","@TargetDir@/qt_crashpad_test.desktop","Exec=env LD_LIBRARY_PATH=$LD_LIBRARY_PATH:@TargetDir@/lib @TargetDir@/bin/main")
    component.addOperation("Copy","@TargetDir@/qt_crashpad_test.desktop","/usr/share/applications/qt_crashpad_test.desktop")
  }
}
