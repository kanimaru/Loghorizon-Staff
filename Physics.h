// Physics.h

#ifndef _PHYSICS_h
#define _PHYSICS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define MAX_ANGLE_DEFS 1
#define MAX_IMPULS_DEFS 1
#define MAX_TRACK_DEFS 1

#define MIN_TIME 50
#define POS_TIMEOUT 100
#define POS_OFFSET 50

typedef void(*runner)();
typedef void(*trigger)();
typedef void(*tracker)(int8_t direction);

struct AngleDef
{
	boolean assigned;
	boolean active;

	int8_t min;
	int8_t max;

	double* ref;

	int8_t curTime;
	int8_t minTime;
	int8_t maxTime;

	trigger onTrigger;
	runner onRun;

	boolean isInRange;
	boolean isTriggerd;
};

struct ImpulsDef
{
	boolean assigned;
	boolean active;

	int8_t* ref;
	boolean isTriggerd;
	trigger onTrigger;

	int8_t timeout;
};

struct TrackAngleDef
{
	boolean assigned;
	boolean active;

	double* ref;
	double last;
	double abs;
	double inertia;
	int8_t resolutions;
	tracker callback;
};

void doPhysics();
void setupPhysics();

ImpulsDef* restrictImpuls(int8_t* ref);
AngleDef* restrictAngle(double* ref, int8_t min, int8_t max);
TrackAngleDef* trackAngle(double* ref, int8_t resolutions, tracker cb);

void freeAngleDef(AngleDef* def);
void freeImpulsDef(ImpulsDef* def);
void freeTrackAngleDef(TrackAngleDef* def);

#endif

