//===================== Copyright (C) 2016 Joshua Ashton =====================//
//============================ Licenced Under MIT ============================//
/*!	\file Ephemeral.h
	\brief The main include file you need for all of Ephemeral.
	The main file you need to include to use Ephemeral.
	This is all you need for all functionality.
*/

#ifndef EPHEMERAL_EPHEMERAL_H
#define EPHEMERAL_EPHEMERAL_H

#include "Common.h"
#include "Time.h"
#include "Clock.h"
#include "TickCounter.h"

/*!	\fn void Epehemeral_Init(void);
	\brief Initialises Ephemeral.
	\warning You do not need to use this function unless you define EPHEMERAL_DISABLE_INITIALISERS.
*/
void EPHEMERAL_EXPORT Epehemeral_Init(void);

#ifndef EPHEMERAL_DISABLE_INITIALISERS
INITIALISER(TimeInit);
#endif

#endif
