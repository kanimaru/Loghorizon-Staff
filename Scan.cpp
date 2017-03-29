// 
// 
// 

#include "Scan.h"
#include "Cube.h"
#include "Ball.h"

void Effect_Scan::doIt()
{
	if (!control.x && !control.y && !control.z)
	{
		control.x = 1;
	}

	cube.setRGB(0, 0, 0);	
	cube.move(control.inverseX ? -control.x : control.x,
		control.inverseY ? -control.y : control.y,
		control.inverseZ ? -control.z : control.z);
	cube.setRGB(sin(hardware.ms / 100) * 0x7FF, cos(hardware.ms / 100) * 0x7FF, tan(hardware.ms / 100) * 0x7FF);

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
