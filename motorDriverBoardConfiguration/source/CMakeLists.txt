
PROJECT(CanMotorConfiguration)


FIND_PACKAGE(Qt4 REQUIRED)


INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

#INCLUDE_DIRECTORIES(../include)
#INCLUDE_DIRECTORIES(../classes)


SET(PROJECT_HEADERS  can.h CanInterface.h KvaserCanInterface.h canConfigLoader.h configDataHandling.h)
SET(PROJECT_SOURCES   main.cpp can.cpp   CanInterface.cpp  KvaserCanInterface.cpp canConfigLoader.cpp configDataHandling.cpp)
QT4_WRAP_CPP(QTGENERATED_HEADERS_MOC canConfigLoader.h)

message(STATUS "MOC FILES ARE: ${QTGENERATED_HEADERS_MOC}")

ADD_EXECUTABLE(CanMotorConfiguration ${PROJECT_SOURCES} ${PROJECT_HEADERS}  ${QTGENERATED_HEADERS_MOC}  )

#include the Kvaser CAN library
TARGET_LINK_LIBRARIES(CanMotorConfiguration canlib  )
TARGET_LINK_LIBRARIES(CanMotorConfiguration ${QT_LIBRARIES})




