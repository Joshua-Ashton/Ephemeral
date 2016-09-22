//===================== Copyright (C) 2016 Joshua Ashton =====================//
//============================ Licenced Under MIT ============================//
/*!	\file Clock.h
	\brief Contains all the code for Ephemeral_Clock and its associated functions.
*/

#ifndef EPHEMERAL_CLOCK_H
#define EPHEMERAL_CLOCK_H

#include "Common.h"
#include "Time.h"

/*!	\struct Ephemeral_Clock
	\brief A clock, used for getting elapsed time.
	\warning You should initialise your instance with Ephemeral_ClockCreate() or you will experience errors and it will not work as intended.
	A resettable clock, used for getting elapsed time from a point - think of it as a stopwatch.
*/
typedef struct
{
	Ephemeral_Time startTime; /*!< The start time of the clock. */
} Ephemeral_Clock;

/*!	\fn Ephemeral_Clock Ephemeral_ClockCreate(void)
	\brief Initializes a new clock at the current time.
	You should use this to initialise any Ephemeral_Clock you make.
	You can also use this to reset the clock *without* getting an elapsed time which may be needed for efficiency, especially as there is no pointer required.
	There is no cleanup method required for this.
*/
inline Ephemeral_Clock Ephemeral_ClockCreate(void)
{
	return (Ephemeral_Clock) { Ephemeral_TimeNow() };
}

/*!	\fn Ephemeral_Time Ephemeral_ClockGetElapsedTime(Ephemeral_Clock clock)
	\brief Get the elapsed time since the start of the clock.
*/
inline Ephemeral_Time Ephemeral_ClockGetElapsedTime(Ephemeral_Clock clock)
{
	return Ephemeral_TimeFromMicroseconds(Ephemeral_TimeNow().microseconds - clock.startTime.microseconds);
}

/*!	\fn Ephemeral_Time Ephemeral_ClockRestart(Ephemeral_Clock* clock)
	\brief Restarts the clock and returns the elapsed time.
	You should use function this to reset the clock instead of just using Ephemeral_ClockCreate if you want the elapsed time also.
*/
inline Ephemeral_Time Ephemeral_ClockRestart(Ephemeral_Clock* clock)
{
	Ephemeral_Time now = Ephemeral_TimeNow();
	Ephemeral_Time elapsed = Ephemeral_TimeFromMicroseconds(now.microseconds - clock->startTime.microseconds);
	clock->startTime = now;

	return elapsed;
}

#endif
