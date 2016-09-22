# Ephemeral
## A simple time library in C.

### Features
* Getting high-resolution time.
* Sleeping the current thread.
* "Clocks" that can be used to see if a specific time has passed since their start or given value.
* Tick counter with embedded clock.
* Ease-of-use: Full documentation of every struct and function with Doxygen!
* A nice licence. (MIT)
* Debug overflow checking.
* Speed.

### Instructions
#### Preparation
You may use the premake build system to generate a .sln file for your version of Visual Studio.

To compile in your own project so that you do not have to link, all you need to add the UnityBuild.c and it will sort out all of the platform specific stuff, that is all.

If you would like to initialise Ephemeral yourself, define EPHEMERAL_DISABLE_INITIALISERS and call Ephemeral_Init(). Calling Ephemeral_Init without EPHEMERAL_DISABLE_INITIALISERS is ***NOT*** required, but it shouldn't cause any issues.

You may disable assertions in by building in Release or defining EPHEMERAL_DISABLE_ASSERTS.
#### Using
Ephemeral can be utilized in many different ways.
One example would be to use it in a game engine for getting delta-time:
```c
...
Ephemeral_TickCounter tc = Ephemeral_TickCounterCreate();
Ephemeral_Time prevTime = Ephemeral_TimeNow();

// Sleep for 0.5s
Ephemeral_TimeSleep(Ephemeral_TimeFromMicroseconds(500));

for(;;)
{
	Ephemeral_Time currentTime = Ephemeral_TimeNow();
	Ephemeral_Time deltaTime = Ephemeral_TimeMinus(currentTime, prevTime);
	prevTime = currentTime;
	...
	if (Ephemeral_TickCounterUpdate(&tc, Ephemeral_TimeFromMilliseconds(500)))
	{
		// This would update every 500ms (0.5s).
		printf("Your FPS is: %f", tc.tickRate);
		// You could use it to get frame time also.
		printf("Your frame time is: %f", 1000.0f / (float)tc.tickRate);
	}
	...
}
...
```
