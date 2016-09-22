//===================== Copyright (C) 2016 Joshua Ashton =====================//
//============================ Licenced Under MIT ============================//
/*!	\file UnityBuild.c
	\brief The only file you need to include to build - sorts out all the platform specific stuff.
*/

#ifndef EPHEMERAL_UNITYBUILD_C
#define EPHEMERAL_UNITYBUILD_C

#include "../include/Ephemeral/Common.h" // To know our platform.

// Let's include the platform-specific C file.
#ifdef EPHEMERAL_SYSTEM_WINDOWS
#include "win32.c"
#else
#include "posix.c"
#endif

#endif
