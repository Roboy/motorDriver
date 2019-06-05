
PROJECT(muscleDriverCANInterface)


FIND_PACKAGE(Qt4 REQUIRED)


INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

#INCLUDE_DIRECTORIES(../include)
#INCLUDE_DIRECTORIES(../classes)


SET(PROJECT_HEADERS   ../../motorDriverBoardConfiguration/source/CanInterface.h ../../motorDriverBoardConfiguration/source/KvaserCanInterface.h UserInterface.h)
SET(PROJECT_SOURCES   main.cpp ../../motorDriverBoardConfiguration/source/can.cpp   ../../motorDriverBoardConfiguration/source/CanInterface.cpp  ../../motorDriverBoardConfiguration/source/KvaserCanInterface.cpp muscleDriverCANInterface.cpp )
QT4_WRAP_CPP(QTGENERATED_HEADERS_MOC muscleDriverCANInterface.h UserInterface.h)

message(STATUS "MOC FILES ARE: ${QTGENERATED_HEADERS_MOC}")

ADD_EXECUTABLE(muscleDriverCANInterface ${PROJECT_SOURCES} ${PROJECT_HEADERS}  ${QTGENERATED_HEADERS_MOC}  )

#include the Kvaser CAN library
TARGET_LINK_LIBRARIES(muscleDriverCANInterface canlib  )
TARGET_LINK_LIBRARIES(muscleDriverCANInterface ${QT_LIBRARIES})




