// Physics.h

#ifndef _PHYSICS_h
#define _PHYSICS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define MAX_ANGLE_DEFS 5
#define MAX_IMPULS_DEFS 5
#define MAX_TRACK_DEFS 5

#define MIN_TIME 50
#define POS_TIMEOUT 100
#define POS_OFFSET 50

typedef void(*runner)();
typedef void(*trigger)();
typedef void(*tracker)(int direction);

struct AngleDef
{
	boolean assigned;
	boolean active;

	int min;
	int max;

	double* ref;

	int curTime;
	int minTime;
	int maxTime;

	trigger onTrigger;
	runner onRun;

	boolean isInRange;
	boolean isTriggerd;
};

struct ImpulsDef
{
	boolean assigned;
	boolean active;

	int* ref;
	boolean isTriggerd;
	trigger onTrigger;

	int timeout;
};

struct TrackAngleDef
{
	boolean assigned;
	boolean active;

	double* ref;
	double last;
	double abs;
	double inertia;
	int resolutions;
	tracker callback;
};

void doPhysics();
void setupPhysics();

ImpulsDef* restrictImpuls(int* ref);
AngleDef* restrictAngle(double* ref, int min, int max);
TrackAngleDef* trackAngle(double* ref, int resolutions, tracker cb);

void freeAngleDef(AngleDef* def);
void freeImpulsDef(ImpulsDef* def);
void freeTrackAngleDef(TrackAngleDef* def);

#endif

