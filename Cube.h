// Cube.h

#ifndef _CUBE_h
#define _CUBE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Selector.h"

class Cube : public Selector
{
public:
	Cube(int16_t _x, int16_t _y, int16_t _z, int16_t height, int16_t width, int16_t depth);
	boolean isIn(int16_t _x, int16_t _y, int16_t _z);

	void setDimension(int16_t width, int16_t height, int16_t depth);
	void setWidth(int16_t width);
	void setHeight(int16_t height);
	void setDepth(int16_t depth);
protected:
	void _collect();
private: 
	int16_t width, height, depth;
	int16_t _x1, _y1, _z1;
	int16_t _x2, _y2, _z2;
};

#endif

