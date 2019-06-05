#ifndef _UTIL_H_
#define _UTIL_H_

#include "fcBase/fcBaseTypes.h"
#include "fcBase/fcBaseTypesFlexRay.h"
#include "fcBase/fcBaseTypesPMC.h"
#include "fcBase/fcBaseTypesCAN.h"

#include <string>
#include <errno.h>

inline void ms_sleep(unsigned int ms_delay)
{
	timespec rqtp, rmtp;
	rmtp.tv_nsec = 0;
	rmtp.tv_sec  = 0;

	rqtp.tv_nsec = ms_delay * 1000000;
	rqtp.tv_sec  = rqtp.tv_nsec / 1000000000;
	rqtp.tv_nsec = rqtp.tv_nsec % 1000000000;

	while ((nanosleep(&rqtp, &rmtp) == -1) && (errno == EINTR))
	{
		if (rmtp.tv_nsec != 0 || rmtp.tv_sec != 0)
		{
			rqtp = rmtp;
			continue; /* Wait again when interrupted by a signal handler */
		}
	}
}

class Util
{
public:
	static void print(fcPacket* p, fcFlexCardDeviceId Id = fcNoDevice);
	static std::string ToString(fcInfoPacket* pFrame, fcFlexCardDeviceId Id = fcNoDevice);
	static std::string ToString(fcFlexRayFrame* pFrame, fcFlexCardDeviceId Id = fcNoDevice);
	static std::string ToString(fcErrorPacket* pFrame, fcFlexCardDeviceId Id = fcNoDevice);
	static std::string ToString(fcStatusPacket* pFrame, fcFlexCardDeviceId Id = fcNoDevice);
	static std::string ToString(fcTriggerInfoPacket* pFrame, fcFlexCardDeviceId Id = fcNoDevice);
	static std::string ToString(fcTxAcknowledgePacket* pFrame, fcFlexCardDeviceId Id = fcNoDevice);
	static std::string ToString(fcNMVectorPacket* pFrame, fcFlexCardDeviceId Id = fcNoDevice);
	static std::string ToString(fcNotificationPacket* pFrame, fcFlexCardDeviceId Id = fcNoDevice);
	static std::string ToString(fcTriggerExInfoPacket* pFrame, fcFlexCardDeviceId Id = fcNoDevice);
	static std::string ToString(fcCANPacket* pFrame, fcFlexCardDeviceId Id = fcNoDevice);
	static std::string ToString(fcCANErrorPacket* pFrame, fcFlexCardDeviceId Id = fcNoDevice);
};

#endif /* _UTIL_H_ */
