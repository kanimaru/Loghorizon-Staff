// 
// 
// 

#include "Scan.h"
#include "Cube.h"
#include "Ball.h"

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

void doScan()
{
	if (!control.x && !control.y && !control.z)
	{
		control.x = 1;
	}

	cube.setRGB(0, 0, 0);	
	cube.move(control.inverseX ? -control.x : control.x, 
		control.inverseY ? -control.y : control.y,
		control.inverseZ ? -control.z : control.z);
	cube.setRGB(0xFFF,0,0);

	if (control.x)
	{
		if (cube.getX() == 60)
		{
			control.inverseX = 1;
		} 
		else if (cube.getX() == 0) 
		{
			control.inverseX = 0;
			control.x = 0;
			control.y = 1;
			cube.setPosition(30, 0, 0);
			cube.setDimension(180, 10, 20);
		}
			
	}
	else if (control.y)
	{
		if (cube.getY() == 100)
		{
			control.inverseY = 1;
		}
		else if (cube.getY() == 0)
		{
			control.inverseY = 0;
			control.y = 0;
			control.z = 1;
			cube.setPosition(0, 0, -20);
			cube.setDimension(180, 180, 10);
		}
	}
	else if (control.z)
	{
		if (cube.getZ() == 20)
		{
			control.inverseZ = 1;
		}
		else if (cube.getZ() == -20)
		{
			control.inverseZ = 0;
			control.z = 0;
			control.x = 1;
			cube.setPosition(0, 50, 0);
			cube.setDimension(10, 180, 20);
		}
	}
}
/*
Ball ball = Ball(70,0,0, 40);
uint8_t pos = 1;
uint8_t dir = 5;

void doScan()
{
	for (uint8_t i = 0; i < ball.ledCount; i++)
	{
		ball.leds[i]->setRGB(0, 0x0, 0);
	}

	pos += dir;
	ball.setPos(70, pos, 0);

	for (uint8_t i = 0; i < ball.ledCount; i++)
	{
		ball.leds[i]->setRGB(0, 0xFFF, 0);
	}
	if (pos > 100 || pos < 0)
	{
		dir *= -1;
	}

	delay(500);
}
*/