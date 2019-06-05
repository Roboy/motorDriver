
PROJECT(uartMotorConfiguration)


FIND_PACKAGE(Qt4 REQUIRED)


INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

#INCLUDE_DIRECTORIES(../include )
#INCLUDE_DIRECTORIES(../classes)


#SET(PROJECT_HEADERS  can.h CanInterface.h KvaserCanInterface.h canConfigLoader.h configDataHandling.h)
#SET(PROJECT_SOURCES   main.cpp can.cpp   CanInterface.cpp  KvaserCanInterface.cpp canConfigLoader.cpp configDataHandling.cpp)


SET(PROJECT_HEADERS   configDataHandling.h)
SET(PROJECT_SOURCES   main.cpp configDataHandling.cpp SerialCommunication.cpp)
QT4_WRAP_CPP(QTGENERATED_HEADERS_MOC configDataHandling.h SerialCommunication.h)

message(STATUS "MOC FILES ARE: ${QTGENERATED_HEADERS_MOC}")

ADD_EXECUTABLE(uartMotorConfiguration ${PROJECT_SOURCES} ${PROJECT_HEADERS}  ${QTGENERATED_HEADERS_MOC}  )

#include serial libary

TARGET_LINK_LIBRARIES(uartMotorConfiguration ${QT_LIBRARIES}  serial)




