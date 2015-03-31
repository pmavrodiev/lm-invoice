project(Invoice_Generator)
cmake_minimum_required(VERSION 2.6)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)


find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(Invoice_Generator_SRCS src/dialogs/SettingsDialog.cpp src/lm-invoice.cpp src/main.cpp)
set(Invoice_Generator_MOC_HEADERS src/dialogs/SettingsDialog.h src/lm-invoice.h)

qt4_wrap_cpp(Invoice_Generator_SRCS ${Invoice_Generator_MOC_HEADERS})

add_executable(Invoice_Generator ${Invoice_Generator_SRCS} ${Invoice_Generator_HEADERS})
target_link_libraries(Invoice_Generator ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS Invoice_Generator RUNTIME DESTINATION bin)
