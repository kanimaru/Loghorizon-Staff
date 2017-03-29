// 
// Helper for register different physically events. Like Rotation to a special point.
// 

#include "Physics.h"
#include "Defines.h"
#include "Hardware.h"

Physics physics;

void ImpulsDef::init(int8_t* ref)
{
	this->ref = ref;
	active = true;
	onTrigger = nullptr;
	isTriggerd = false;
}

void ImpulsDef::calculate()
{
	if (!active) return;

	if (*ref > POS_OFFSET) // anti schwingung
		timeout = POS_TIMEOUT;

	if (*ref < -POS_OFFSET && timeout > 0 && !isTriggerd)
	{
		if (onTrigger != nullptr)
		{
			onTrigger->onTrigger();
		}
		isTriggerd = true;
	}

	timeout -= hardware.diff;
	if (timeout < 0)
	{
		timeout = 0;
		isTriggerd = false;
	}
}

void AngleDef::init(int8_t* ref, int8_t min, int8_t max)
{
	this->ref = ref;
	this->min = min;
	this->max = max;
	active = true;

	curTime = 0;
	isInRange = false;
	maxTime = 400;
	minTime = 30;
	onRun = nullptr;
	onTrigger = nullptr;
	isTriggerd = false;
}

void AngleDef::calculate()
{
	if (!active) return;

	if (*ref < max &&
		*ref > min)
	{
		isInRange = true;
		if (curTime < maxTime) curTime += hardware.diff;
		if (curTime > maxTime) curTime = maxTime;

		if (minTime > 0 &&
			curTime < minTime) return;

		if (onTrigger != nullptr && !isTriggerd)
		{
			onTrigger->onTrigger();
		}
		if (onRun != nullptr)
		{
			onRun->onRun();
		}
		isTriggerd = true;
	}
	else
	{
		curTime -= hardware.diff;
		if (curTime < 0)
		{
			curTime = 0;
			isTriggerd = false;
		}
		isInRange = false;
	}
}

void TrackAngleDef::init(int8_t* refX, int8_t* refY, int8_t resolutions, Tracker* cb)
{
	last = 0;
	active = true;
	this->refX = refX;
	this->refY = refY;
	this->resolutions = resolutions;
	callback = cb;
}

void TrackAngleDef::calculate()
{
	if (!active) return;

	double xAngle = 0;

	if (*refY == 0 && *refX > 0)
	{
		xAngle = 180;
	}
	else if (*refY == 0 && *refX < 0)
	{
		xAngle = 360;
	}
	else
	{
		double angle = (double)*refX / (double)*refY;
		xAngle = atan(angle) * RAD_TO_DEG;
		if (*refY > 0)
			xAngle += 90;
		else
			xAngle += 270;
	}

	double diff = xAngle - last;

	// ref(350) - last(10) = diff(340) != diff(-20)
	if (diff > 180)
	{
		diff = xAngle - 360 - last;
	}

	// ref(10) - last(350) = diff(-340) != diff(20)
	else if (diff < -180)
	{
		diff = 360 - last + xAngle;
	}

	boolean forward = diff > resolutions || diff < -180;
	boolean backward = diff < -resolutions || diff > 180;
	if (forward)
	{
		last = xAngle;
		callback->onTrack(1);
	} else if (backward) {
		last = xAngle;
		callback->onTrack(-1);
	}

#ifdef DEBUG_TRACK
	Serial.print("X: ");
	Serial.print(*refX);
	Serial.print(" Y: ");
	Serial.print(*refY);
	Serial.print(" Winkel: ");
	Serial.println(xAngle);
#endif
}

void Physics::init()
{
	for (int i = 0; i < 10; i++)
		definitions[i] = nullptr;
}

void Physics::doPhysics()
{
	for (int i = 0; i < 10; i++)
		if(definitions[i] != nullptr) {
			definitions[i]->calculate();
		}
		
}

void Physics::add(Definition* def)
{
	for (int i = 0; i < 10; i++)
		if (definitions[i] == nullptr)
		{
			definitions[i] = def;
			return;
		}
}

void Physics::free(Definition* def)
{
	for (int i = 0; i < 10; i++)
	{
		if (definitions[i] == def)
		{
			definitions[i] = nullptr;
			return;
		}
	}
}
