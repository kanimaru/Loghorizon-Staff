// Scan.h

#ifndef _SCAN_h
#define _SCAN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Effect.h"
#include "Cube.h"

class Effect_Scan : public Effect
{
public:
	void doIt();

private:
	struct Control
	{
		uint8_t x : 1,
			y : 1,
			z : 1,
			inverseX : 1,
			inverseY : 1,
			inverseZ : 1;
	} control;

	Cube cube = Cube(0, 50, 0, 10, 180, 20);

};

#endif

