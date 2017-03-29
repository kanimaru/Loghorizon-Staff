// ModeHandler.h

#ifndef _MODE_h
#define _MODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Fire.h"
#include "LightningBall.h"
#include "Scan.h"
#include "Hypnotic.h"
#include "ColorChanger.h"
#include "Physics.h"
#include "LED.h"
#include "Defines.h"
#include "Ball.h"

class Modes : public Trigger, Tracker
{
public:
	void init();
	void doModes();
	Effect* activeMode;

	void onTrack(int8_t direction);
	void onTrigger();
	void singleTap();
	void doubleTap();
	
	void animate(Ball* selector, uint16_t range, LED* target, int8_t direction);
private:
	Effect* effects[EFFECT_COUNT];

	// Current mode selection
	int8_t mode = 0;
	LED* lastLED;

	// Helper to get into Setup
	AngleDef setupY = AngleDef();
	ImpulsDef setupImpulsY = ImpulsDef();
	boolean setupMode;

	// Shows wich LED is for which Mode;
	LED* modeLed[EFFECT_COUNT];
	Ball ballSelector = Ball(0, 0, 0, MODE_ANIMATE_RANGE);
};

extern Modes modes;

#endif

