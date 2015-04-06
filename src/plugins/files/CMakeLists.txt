project(dummy)
cmake_minimum_required(VERSION 2.6)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

file(GLOB SOURCES *.cpp ../../libs/utils/*.cpp )
file(GLOB HEADERS *.h ../../libs/utils/*.h )



find_package(Qt4 REQUIRED)

set(GCC_11 "-std=c++11")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_11}" )


include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(dummy_SRCS ${SOURCES})
set(dummy_MOC_HEADERS ${HEADERS})

qt4_wrap_cpp(dummy_SRCS ${dummy_MOC_HEADERS})


add_executable(dummy ${dummy_SRCS} ${dummy_HEADERS})
target_link_libraries(dummy ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS dummy RUNTIME DESTINATION bin)


#/usr/bin/cmake -DQT_QMAKE_EXECUTABLE=/usr/lib/qt4/bin  -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Debug -G 'Unix Makefiles' /home/pmavrodiev/Projects/lm-invoice/src/plugins/files