/*
 * UserInterface.h
 *
 *  Created on: 27 Feb 2014
 *      Author: alex
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_
#include <QObject>
#include <QDir>
#include<QTextStream>
#include <QTimer>
#include <QElapsedTimer>
#include  "../../../myode/src/eu.myode.Myorobot/robot/CommunicationData.h"
class UserInterface : public QObject
{
	Q_OBJECT
	public:
		UserInterface();
		void initGlobalSafeCommandFrame();
		void setLogFilePointer(QTextStream * fileOutput);

	public slots:
		void run();
		void GanglionDataDisplay(ganglionData_t *);

	 signals:
		void startMotors (void);
		void stopMotors(void);
		void detachFromApp(void);
		void setReference(float ref);
		void setLoggingEnable(bool logEn);
		void setCommandAndParameterFrames(comsCommandFrame * completeCommandFrames, control_Parameters_t * ControlParams);



	private:
		//int  m_MuscleDriverCANInterface;
		QTextStream * mfileOutput;
		QElapsedTimer elapsedTime;
		 qint64 nanoSec;
		 unsigned long accutime;
		//global parameter structures
		comsCommandFrame allGlobalCommandFrames[NUMBER_OF_GANGLIONS];
		control_Parameters_t oneGlobalSetOfControlParameters;

};


#endif /* USERINTERFACE_H_ */
