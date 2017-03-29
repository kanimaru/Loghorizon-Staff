// Physics.h

#ifndef _PHYSICS_h
#define _PHYSICS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

//#define DEBUG_TRACK

#define MAX_ANGLE_DEFS 3
#define MAX_IMPULS_DEFS 3
#define MAX_TRACK_DEFS 3

#define MIN_TIME 20
#define POS_TIMEOUT 100
#define POS_OFFSET 5

class Definition
{
public:
	virtual void calculate() = 0;

};

class Physics
{
public:
	void init();

	void add(Definition* def);
	void free(Definition* def);

	void doPhysics();
private:
	Definition* definitions[10];
};

class Runner
{
public:
	virtual void onRun() = 0;
};

class Trigger
{
public:
	virtual void onTrigger() = 0;
};

class Tracker
{
public:
	virtual void onTrack(int8_t direction) = 0;
};

class AngleDef : public Definition
{
public:
	void init(int8_t* ref, int8_t min, int8_t max);
	void calculate();

	boolean isInRange;
	boolean isTriggerd;

	Trigger* onTrigger;
	Runner* onRun;
	boolean active;

private:


	int16_t min;
	int16_t max;

	int8_t* ref;

	int16_t curTime;
	int16_t minTime;
	int16_t maxTime;
};

class ImpulsDef : public Definition
{
public:
	void init(int8_t* ref);
	void calculate();
	boolean isTriggerd;
	Trigger* onTrigger;
	boolean active;

private:
	int8_t* ref;
	int8_t timeout;
};

class TrackAngleDef : public Definition
{
public:
	void init(int8_t* refX, int8_t* refY, int8_t resolutions, Tracker* cb);
	void calculate();
	Tracker* callback;
	boolean active;

private:

	int8_t* refX;
	int8_t* refY;
	double last;
	double abs;
	double inertia;
	int8_t resolutions;
};

extern Physics physics;

#endif

