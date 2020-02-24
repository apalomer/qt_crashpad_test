add_library(myprocess SHARED myprocess.cpp myprocess.h)
target_link_libraries(myprocess Qt5::Core Qt5::Widgets)

add_library(mywidget SHARED mywidget.cpp mywidget.h mywidget.ui)
target_link_libraries(mywidget myprocess Qt5::Core Qt5::Widgets)

add_compile_options(-Wl,--no-as-needed)
add_executable(main main.cpp)
target_link_libraries(main Qt5::Core Qt5::Widgets mywidget
  libclient.a
  libutil.a
  libbase.a
)
