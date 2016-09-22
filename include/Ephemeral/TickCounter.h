//===================== Copyright (C) 2016 Joshua Ashton =====================//
//============================ Licenced Under MIT ============================//
/*!	\file TickCounter.h
	\brief Contains all the code for Ephemeral_TickCounter and its associated functions.
*/
#ifndef EPHEMERAL_TICKCOUNTER_H
#define EPHEMERAL_TICKCOUNTER_H

#include "Common.h"
#include "Time.h"
#include "Clock.h"

/*!	\struct Ephemeral_TickCounter
	\brief A tick counter w/ clock.
	\warning You should not need to edit any of the values inside this struct, all the work you should ever need is provided in the functions.
	\warning You should initialise your instance with Ephemeral_TickCounterCreate() or you will experience errors.
	A tick counter with an embedded clock for getting if a given interval has passed.
*/
typedef struct
{
	double tickRate; /*!< The last known tick rate of the counter in ticks-per-second. */
	Ephemeral_Clock clock; /*!< The clock internal to the tick counter for getting if the interval has passed.*/
	size_t tickCount; /*!< How many ticks have passed since the last inverval check returned true.*/
} Ephemeral_TickCounter;

/*!	\fn Ephemeral_TickCounter Ephemeral_TickCounterCreate(void)
	\brief Initializes a new tick counter at the current time.
	Initializes a new tick counter at the current time, you should use this to initialise any Ephemeral_TickCounters you make.
*/
inline Ephemeral_TickCounter Ephemeral_TickCounterCreate(void)
{
	return (Ephemeral_TickCounter) { 0, Ephemeral_ClockCreate(), 0 };
}

/*!	\fn int8_t Ephemeral_TickCounterUpdate(Ephemeral_TickCounter* counter,Ephemeral_Time period)
	\brief Updates the tick counter once it has elapsed the given period.
	Updates the tick counter once it has elapsed the given period, returns if it reset or not.
	If it returns true, the running the counter's tick rate (tickRate) will be updated and the clock reset.
	If it returns false, the counter's tick count (tickCount) will be incremented by one.
*/
inline int8_t Ephemeral_TickCounterUpdate(Ephemeral_TickCounter* counter, Ephemeral_Time period)
{
	int8_t reset = 0;
	Ephemeral_Time elapsedTime = Ephemeral_ClockGetElapsedTime(counter->clock);
	if (elapsedTime.microseconds >= period.microseconds)
	{
		counter->tickRate = ((double)(counter->tickCount)) * (1.0f / Ephemeral_TimeAsSeconds(period));
		counter->tickCount = 0;
		reset = 1;
		Ephemeral_ClockRestart(&(counter->clock));
	}

	counter->tickCount++;
	return reset;
}

#endif
