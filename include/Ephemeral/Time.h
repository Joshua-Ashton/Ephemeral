//===================== Copyright (C) 2016 Joshua Ashton =====================//
//============================ Licenced Under MIT ============================//
/*!	\file Time.h
	\brief Contains all the code for Ephemeral_Time and its associated functions.
*/

#ifndef EPHEMERAL_TIME_H
#define EPHEMERAL_TIME_H

#include "Common.h"

#include <math.h>	// For floorf.
#include <time.h>	// For struct timespec and posix sleep functions (when using those platforms).
#include <assert.h>	// For assert.
#include <limits.h>	// For testing if an overflow will occur by checking against type limits (integers).
#include <float.h>	// For testing if an overflow will occur by checking against type limits (floats).

/*!	\struct Ephemeral_Time
	\brief A moment in time.
	Uses a microsecond backend.
*/
typedef struct
{
	int64_t microseconds; /*!< The time of this moment in microseconds.*/
} Ephemeral_Time;

/*!	\fn Ephemeral_Time Ephemeral_TimeNow(void)
	\brief Gets the current moment in time.
*/
Ephemeral_Time EPHEMERAL_EXPORT Ephemeral_TimeNow(void);

/*!	\fn void Ephemeral_TimeSleep(Ephemeral_Time time)
	\brief Sleeps for an given Ephemeral_Time moment.
*/
void EPHEMERAL_EXPORT Ephemeral_TimeSleep(Ephemeral_Time time);

/*!	\fn Ephemeral_Time Ephemeral_TimeMinus(Ephemeral_Time a, Ephemeral_Time b)
	\brief Takes away two Ephemeral_Time moments.
*/
inline Ephemeral_Time Ephemeral_TimeMinus(Ephemeral_Time a, Ephemeral_Time b)
{
	// Unsigned check here as we want the full amount, not just the positive half.
	EPHEMERAL_ASSERT(((uint64_t)b.microseconds < ULLONG_MAX - a.microseconds && (uint64_t)b.microseconds < ULLONG_MAX + a.microseconds) && "Overflow will occur here!");
	return (Ephemeral_Time) { a.microseconds - b.microseconds };
}

/*!	\fn Ephemeral_Time Ephemeral_TimeAdd(Ephemeral_Time a, Ephemeral_Time b)
	\brief Adds two Ephemeral_Time moments.
*/
inline Ephemeral_Time Ephemeral_TimeAdd(Ephemeral_Time a, Ephemeral_Time b)
{
	// Unsigned check here as we want the full amount, not just the positive half.
	EPHEMERAL_ASSERT(((uint64_t)b.microseconds < ULLONG_MAX - a.microseconds && (uint64_t)b.microseconds < ULLONG_MAX + a.microseconds) && "Overflow will occur here!");
	return (Ephemeral_Time) { a.microseconds + b.microseconds };
}

/*!	\fn Ephemeral_Time Ephemeral_TimeMultiply(Ephemeral_Time a, int64_t b)
	\brief Multiplies an Ephemeral_Time moment by a given integer.
*/
inline Ephemeral_Time Ephemeral_TimeMultiply(Ephemeral_Time a, int64_t b)
{
	EPHEMERAL_ASSERT(a.microseconds < LLONG_MAX / b && "Overflow will occur here!");
	return (Ephemeral_Time) { a.microseconds * b };
}

/*!	\fn Ephemeral_Time Ephemeral_TimeDivide(Ephemeral_Time a, int64_t b)
	\brief Divides a time moment by an given integer.
*/
inline Ephemeral_Time Ephemeral_TimeDivide(Ephemeral_Time a, int64_t b)
{
	EPHEMERAL_ASSERT(b != 0 && "You cannot divide by zero!");
	EPHEMERAL_ASSERT(a.microseconds < LLONG_MAX * b && "Overflow will occur here!");
	return (Ephemeral_Time) { a.microseconds / b };
}

/*!	\fn float Ephemeral_TimeAsSeconds(Ephemeral_Time time)
	\brief Gives the value of an Ephemeral_Time moment in seconds (float).
*/
inline float Ephemeral_TimeAsSeconds(Ephemeral_Time time)
{
	if (time.microseconds == 0)
		return 0.0f;

	return (float)time.microseconds / 1000000.0f;
}

/*!	\fn int64_t Ephemeral_TimeAsLowerSeconds(Ephemeral_Time time)
	\brief Gives the value of an Ephemeral_Time moment in seconds (int64_t) rounded down.
*/
inline int64_t Ephemeral_TimeAsLowerSeconds(Ephemeral_Time time)
{
	return (int64_t)floorf(Ephemeral_TimeAsSeconds(time));
}

/*!	\fn double Ephemeral_TimeAsAccurateSeconds(Ephemeral_Time time)
	\brief Gives the value of an Ephemeral_Time moment in seconds (double).
*/
inline double Ephemeral_TimeAsAccurateSeconds(Ephemeral_Time time)
{
	if (time.microseconds == 0)
		return 0.0;

	return (double)time.microseconds / 1000000.0;
}

/*!	\fn int32_t Ephemeral_TimeAsMilliseconds(Ephemeral_Time time)
	\brief Gives the value of an Ephemeral_Time moment in milliseconds.
*/
inline int32_t Ephemeral_TimeAsMilliseconds(Ephemeral_Time time)
{
	if (time.microseconds == 0)
		return 0;

	return (int32_t)(time.microseconds / 1000);
}

/*!	\fn int64_t Ephemeral_TimeAsMicroseconds(Ephemeral_Time time)
	\brief Gives the value of an Ephemeral_Time moment in microseconds.
*/
inline int64_t Ephemeral_TimeAsMicroseconds(Ephemeral_Time time)
{
	return time.microseconds;
}

/*!	\fn int64_t Ephemeral_TimeAsNanoseconds(Ephemeral_Time time)
	\brief Gives the value of an Ephemeral_Time moment in nanoseconds.
	\warning This function may overflow easily quite easily. It is recommended to get it as a timespec (Ephemeral_TimeAsTimeSpec) to avoid this overflow.
*/
inline int64_t Ephemeral_TimeAsNanoseconds(Ephemeral_Time time)
{
	EPHEMERAL_ASSERT(time.microseconds < LLONG_MAX / 1000000 && "Overflow will occur here!");
	return time.microseconds * 1000000;
}

/*!	\fn Ephemeral_Time Ephemeral_TimeFromSeconds(float amount)
	\brief Converts a time in seconds (float) to an Ephemeral_Time moment.
*/
inline Ephemeral_Time Ephemeral_TimeFromSeconds(float amount)
{
	EPHEMERAL_ASSERT(amount < FLT_MAX / 1000000.0f && "Overflow will occur here!");
	return (Ephemeral_Time) { (int64_t)(amount * 1000000.0f) };
}

/*!	\fn Ephemeral_Time Ephemeral_TimeFromAccurateSeconds(double amount)
	\brief Converts a time in seconds (double) to an Ephemeral_Time moment.
*/
inline Ephemeral_Time Ephemeral_TimeFromAccurateSeconds(double amount)
{
	EPHEMERAL_ASSERT(amount < DBL_MAX / 1000000.0 && "Overflow will occur here!");
	return (Ephemeral_Time) { (int64_t)(amount * 1000000.0) };
}

/*!	\fn Ephemeral_Time Ephemeral_TimeFromLowerSeconds(int64_t amount)
	\brief Converts a time in seconds (int64_t) to an Ephemeral_Time moment.
*/
inline Ephemeral_Time Ephemeral_TimeFromLowerSeconds(int64_t amount)
{
	EPHEMERAL_ASSERT(amount < ULLONG_MAX / 1000000 && "Overflow will occur here!");
	return (Ephemeral_Time) { (int64_t)(amount * 1000000) };
}

/*!	\fn Ephemeral_Time Ephemeral_TimeFromMilliseconds(int32_t amount)
	\brief Converts a time in milliseconds to an Ephemeral_Time moment.
*/
inline Ephemeral_Time Ephemeral_TimeFromMilliseconds(int32_t amount)
{
	return (Ephemeral_Time) { ((int64_t)(amount)) * 1000 };
}

/*!	\fn Ephemeral_Time Ephemeral_TimeFromMicroseconds(int64_t amount)
	\brief Converts a time in microseconds to an Ephemeral_Time moment.
*/
inline Ephemeral_Time Ephemeral_TimeFromMicroseconds(int64_t amount)
{
	return (Ephemeral_Time) { amount };
}

/*!	\fn Ephemeral_Time Ephemeral_TimeFromNanoseconds(int64_t amount)
	\brief Converts a time in nanoseconds to an Ephemeral_Time moment.
*/
inline Ephemeral_Time Ephemeral_TimeFromNanoseconds(int64_t amount)
{
	if (amount == 0)
		return (Ephemeral_Time) { 0 };

	return (Ephemeral_Time) { amount / 1000000 };
}

/*!	\fn struct timespec Ephemeral_TimeAsTimeSpec(Ephemeral_Time time)
	\brief Gives the value of an Ephemeral_Time moment as a sturct timespec (seconds, nanos).
*/
inline struct timespec Ephemeral_TimeAsTimeSpec(Ephemeral_Time time)
{
	// Get just the seconds rounded down.
	time_t seconds = (time_t)Ephemeral_TimeAsLowerSeconds(time);
	// Return timespec of { our seconds, (the actual full time, take away the time of the rounded down seconds in microseconds) converted to nanoseconds.
	return (struct timespec) { seconds, (long)Ephemeral_TimeAsNanoseconds(Ephemeral_TimeMinus(time, Ephemeral_TimeFromLowerSeconds(seconds))) };
}

/*!	\fn Ephemeral_Time Ephemeral_TimeFromTimeSpec(struct timespec* amount)
	\brief Converts a time as a struct timespec to an Ephemeral_Time moment.
*/
inline Ephemeral_Time Ephemeral_TimeFromTimeSpec(struct timespec* amount)
{
	// Add the converted seconds and nanos to convert from timespec to Ephemeral_Time.
	return Ephemeral_TimeAdd(Ephemeral_TimeFromSeconds((float)amount->tv_sec), Ephemeral_TimeFromNanoseconds(amount->tv_nsec));
}

#endif
