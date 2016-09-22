//===================== Copyright (C) 2016 Joshua Ashton =====================//
//============================ Licenced Under MIT ============================//
/*!	\file win32.c
	\brief Platform specific code for Win32.
*/
#include "../include/Ephemeral/Clock.h"
#include "../include/Ephemeral/TickCounter.h"
#include "../include/Ephemeral/Time.h"
#include "../include/Ephemeral/Ephemeral.h"

// Windows library and the link requirements.
#include <Windows.h>
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Winmm.lib")

static LARGE_INTEGER timeFrequency = { 0 };

static LARGE_INTEGER Ephemeral_TimeGetFrequency(void)
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}

static void Ephemeral_TimeInit(void)
{
	timeFrequency = Ephemeral_TimeGetFrequency();
}

void Epehemeral_Init(void)
{
	Ephemeral_TimeInit();
}

inline Ephemeral_Time Ephemeral_TimeNow(void)
{
	HANDLE currentThread = GetCurrentThread();
	DWORD_PTR previousMask = SetThreadAffinityMask(currentThread, 1);

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	SetThreadAffinityMask(currentThread, previousMask);
	return (Ephemeral_Time) { 1000000 * time.QuadPart / timeFrequency.QuadPart };
}

inline void Ephemeral_TimeSleep(Ephemeral_Time time)
{
	if (time.microseconds <= 0)
		return;

	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));
	timeBeginPeriod(tc.wPeriodMin);

	Sleep(Ephemeral_TimeAsMilliseconds(time));

	timeBeginPeriod(tc.wPeriodMin);
}
