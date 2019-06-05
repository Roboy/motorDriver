/*
 * canConfigLoader.h
 *
 *  Created on: 24 Oct 2012
 *      Author: alex
 */

#ifndef CANCONFIGLOADER_H_
#define CANCONFIGLOADER_H_
#include <QMutex>
 #include <QThread>

#define TEST_MESSAGE_01 0x08
#define STRING_MESSAGE 0x07
#define WAKE_UP_MSG_BASE_ID 0x500
#define CONFIGURATION_MSG_BASE_ID 0x700
#define CONFIGURATION_REPLY_ID 0x11

typedef enum CONFIG_STATE_T {
		WAIT_FOR_WAKEUP=1,
		START_CONFIG,
		CONFIG_MESSAGE_SENT,
		CONFIG_REPLY_RECEIVED,
		END_CONFIG
}CONFIG_STATE;

 class canConfigLoader : public QThread
 {
 public:
    canConfigLoader();
   Q_OBJECT
 private:
     void run();

 };

#endif /* CANCONFIGLOADER_H_ */
