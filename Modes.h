// ModeHandler.h

#ifndef _MODE_HANDLER_h
#define _MODE_HANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Physics.h"
#include "LED.h"
#include "Hardware.h"

#define MODE_COUNT 2
//#define MODE_DEBUG

class ModeHandler
{
public:
	void setupModes();
	void doModes();
	runner modes[MODE_COUNT];
	runner activeMode;
	void doSetup();

	// Current mode selection
	int mode = 0;
	LED* lastLED;

	// Helper to get into Setup
	AngleDef* setupX;
	AngleDef* setupZ;
	ImpulsDef* setupImpulsY;
	boolean setupMode;

	// Helper to change the modis
	AngleDef* modeX;
	AngleDef* modeZ;
	TrackAngleDef* trackY;
private:
	void changeMode(int direction);
	static void wrap_changeMode(int direction);
	static void wrap_doSetup();

};

extern ModeHandler modeHandler;

#endif

