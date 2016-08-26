// 
// 
// 

#include "Physics.h"
#include "Timer.h"

AngleDef angleRegisters[MAX_ANGLE_DEFS];
ImpulsDef impulsRegisters[MAX_IMPULS_DEFS];
TrackAngleDef trackRegisters[MAX_TRACK_DEFS];

void setupPhysics()
{
	for (int i = 0; i < MAX_ANGLE_DEFS; i++)
		freeAngleDef(&angleRegisters[i]);
	for (int i = 0; i < MAX_IMPULS_DEFS; i++)
		freeImpulsDef(&impulsRegisters[i]);
	for (int i = 0; i < MAX_TRACK_DEFS; i++)
		freeTrackAngleDef(&trackRegisters[i]);
}

void doPhysics()
{
	// ANGLES
	for (int i = 0; i < MAX_ANGLE_DEFS; i++)
	{
		AngleDef* def = &angleRegisters[i];
		if (!def->assigned || !def->active) continue;

		if (*def->ref < def->max &&
			*def->ref > def->min)
		{
			def->isInRange = true;

			if (def->curTime < def->maxTime) def->curTime += diff;
			if (def->curTime > def->maxTime) def->curTime = def->maxTime;

			if (def->minTime > 0 && 
				def->curTime < def->minTime) continue;

			if (def->onTrigger != nullptr && !def->isTriggerd)
			{
				(def->onTrigger)();
			}
			if (def->onRun != nullptr)
			{
				(def->onRun)();
			}
			def->isTriggerd = true;
		}
		else
		{
			def->curTime -= diff;
			if (def->curTime < 0)
			{
				def->curTime = 0;
				def->isTriggerd = false;
			}
			def->isInRange = false;
		}
	}

	// IMPULSES
	for (int i = 0; i < MAX_IMPULS_DEFS; i++)
	{
		ImpulsDef* def = &impulsRegisters[i];
		if (!def->assigned || !def->active) continue;

		if (*def->ref > POS_OFFSET) // anti schwingung
		{
			def->timeout = POS_TIMEOUT;
		}

		if (*def->ref < -POS_OFFSET && def->timeout > 0 && !def->isTriggerd)
		{
			if (def->onTrigger != nullptr)
			{
				(def->onTrigger)();
			}
			def->isTriggerd = true;
		}

		def->timeout -= diff;
		if (def->timeout < 0)
		{
			def->timeout = 0;
			def->isTriggerd = false;
		}
	}

	// TRACK ANGLES
	for (int i = 0; i < MAX_TRACK_DEFS; i++)
	{
		TrackAngleDef* def = &trackRegisters[i];
		if (!def->assigned || !def->active) continue;

		double diff = *def->ref - def->last;
		
		// ref(350) - last(10) = diff(340) != diff(-20)
		if (diff > 180)
		{
			diff = *def->ref - 360 - def->last; 
		}

		// ref(10) - last(350) = diff(-340) != diff(20)
		else if (diff < -180)
		{
			diff = 360 - def->last + *def->ref; 
		}

		boolean forward = diff > def->resolutions || diff < -180;
		boolean backward = diff < -def->resolutions || diff > 180;
		if (forward)
		{
			def->last = *def->ref;
			def->callback(1);
		}
		else if(backward)
		{
			def->last = *def->ref;
			def->callback(-1);
		}
	}
}

ImpulsDef* restrictImpuls(int* ref)
{
	for (int i = 0; i < MAX_IMPULS_DEFS; i++)
	{
		ImpulsDef* def = &impulsRegisters[i];
		if (!def->assigned)
		{
			def->ref = ref;
			def->assigned = true;
			def->active = true;
			return def;
		}

	}
	return nullptr;
}

AngleDef * restrictAngle(double* ref, int min, int max)
{
	for (int i = 0; i < MAX_ANGLE_DEFS; i++)
	{
		AngleDef* def = &angleRegisters[i];
		if (!def->assigned)
		{
			def->ref = ref;
			def->min = min;
			def->max = max;
			def->assigned = true;
			def->active = true;
			return def;
		}

	}
	return nullptr;
}

TrackAngleDef* trackAngle(double* ref, int resolutions, tracker cb)
{
	for (int i = 0; i < MAX_TRACK_DEFS; i++)
	{
		TrackAngleDef* def = &trackRegisters[i];
		if (!def->assigned)
		{
			def->active = true;
			def->assigned = true;
			def->ref = ref;
			def->resolutions = resolutions;
			def->callback = cb;
			return def;
		}
	}
}

void freeAngleDef(AngleDef* def)
{
	if (def == nullptr) return;
	def->active = false;
	def->assigned = false;
	def->curTime = 0;
	def->isInRange = false;
	def->max = 0;
	def->maxTime = POS_TIMEOUT * 2;
	def->min = 0;
	def->minTime = POS_TIMEOUT;
	def->onRun = nullptr;
	def->onTrigger = nullptr;
	def->ref = nullptr;
	def->isTriggerd = false;
}

void freeImpulsDef(ImpulsDef* def)
{
	if (def == nullptr) return;
	def->active = false;
	def->assigned = false;
	def->onTrigger = nullptr;
	def->ref = nullptr;
	def->isTriggerd = false;
}

void freeTrackAngleDef(TrackAngleDef* def)
{
	if (def == nullptr) return;
	def->active = false;
	def->assigned = false;
	def->callback = nullptr;
	def->last = 0;
	def->resolutions = 0;
	def->ref = nullptr;
}