add_library(myprocess SHARED myprocess.cpp myprocess.h)
target_compile_definitions(myprocess PRIVATE MYPROCESS)
target_link_libraries(myprocess Qt5::Core Qt5::Widgets)

add_library(mywidget SHARED mywidget.cpp mywidget.h mywidget.ui)
target_compile_definitions(mywidget PRIVATE MYWIDGET)
target_link_libraries(mywidget myprocess Qt5::Core Qt5::Widgets)

add_executable(main main.cpp)
if (UNIX)
  target_link_libraries(main Qt5::Core Qt5::Widgets mywidget
    libclient.a
    libutil.a
    libbase.a
  )
else()
  target_link_libraries(main Qt5::Core Qt5::Widgets mywidget
    client.lib
    util.lib
    base.lib
  )
endif()
