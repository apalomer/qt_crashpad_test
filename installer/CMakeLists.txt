if(CMAKE_INSTALL_PREFIX MATCHES "${CMAKE_SOURCE_DIR}/installer/packages/qt_crashpad_test/data")

  # Deploy qt
  # This needs to be done before protecting
  if (WIN32)
    install(CODE "MESSAGE(\"Running windeployqt --release ${CMAKE_INSTALL_PREFIX}/bin\")")
    install(CODE "execute_process(COMMAND windeployqt --release \"${CMAKE_INSTALL_PREFIX}/bin/main.exe\")")
  endif()

  # Generate installer
  install(CODE "MESSAGE(\"Generating installer with qt framework (make sure binarycreator from QtInstallerFramework is added to the path)\")")
  install(CODE "execute_process(COMMAND binarycreator -c \"${CMAKE_SOURCE_DIR}/installer/config/config.xml\" -p \"${CMAKE_SOURCE_DIR}/installer/packages\" \"${CMAKE_SOURCE_DIR}/installer/QtCrashpadTest_${QTCRASPHADTEST_VERSION}_${CMAKE_SYSTEM}_${CMAKE_HOST_SYSTEM_PROCESSOR}\")")
endif()
