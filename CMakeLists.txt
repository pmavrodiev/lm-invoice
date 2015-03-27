project(lm-invoice)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(lm-invoice_SRCS lm-invoice.cpp main.cpp)
qt4_automoc(${lm-invoice_SRCS})
add_executable(lm-invoice ${lm-invoice_SRCS})
target_link_libraries(lm-invoice ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS lm-invoice RUNTIME DESTINATION bin)
