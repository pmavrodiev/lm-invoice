project(Invoice_Generator)
cmake_minimum_required(VERSION 2.6)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

file(GLOB SOURCES src/*.cpp src/dialogs/*.cpp src/libs/pluginmanager/*.cpp src/libs/utils/*.cpp src/plugins/files/*.cpp )
file(GLOB HEADERS src/*.h src/dialogs/*.h src/libs/pluginmanager/*.h src/libs/utils/*.h src/plugins/files/*.h )



set(Invoice_Generator_SRCS ${SOURCES})
set(Invoice_Generator_MOC_HEADERS ${HEADERS})

set(GCC_11 "-std=c++11")

find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_11}")

qt4_wrap_cpp(Invoice_Generator_SRCS ${Invoice_Generator_MOC_HEADERS})

add_executable(Invoice_Generator ${Invoice_Generator_SRCS} ${Invoice_Generator_MOC_HEADERS})
target_link_libraries(Invoice_Generator ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS Invoice_Generator RUNTIME DESTINATION bin)
