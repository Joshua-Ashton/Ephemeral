//===================== Copyright (C) 2016 Joshua Ashton =====================//
//============================ Licenced Under MIT ============================//
/*!	\file posix.c
	\brief Platform specific code for posix-compliant platforms.
*/
#include "../include/Ephemeral/Clock.h"
#include "../include/Ephemeral/TickCounter.h"
#include "../include/Ephemeral/Time.h"
#include "../include/Ephemeral/Ephemeral.h"

void Epehemeral_Init(void)
{
	// No initialization required! Hooray!
}

inline Ephemeral_Time Ephemeral_TimeNow(void)
{
	struct timespec time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
	return Ephemeral_TimeFromTimeSpec(&time);
}

inline void Ephemeral_TimeSleep(Ephemeral_Time time)
{
	if (time.microseconds <= 0)
		return;

#ifdef EPHEMERAL_USE_USLEEP
	usleep(time.microseconds);
#else
	struct timespec timespec = Ephemeral_TimeAsTimeSpec(&time);
	nanosleep(&timespec, NULL);
#endif
}
