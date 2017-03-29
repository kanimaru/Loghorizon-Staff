// 
// Simmulates fire and depends on the position how hot it is.
// 

#include "Fire.h"
#include "Hardware.h"
#include "Modes.h"


void Effect_Fire::doIt()
{
	uint16_t x = hardware._x / 2;
	uint16_t y = hardware._y / 2;
	uint16_t z = hardware._z / 2;

	ballSelector.move(x, y, z);

	restrictBall(&ballSelector);
	modes.animate(&ballSelector, FIRE_ANIMATE_RANGE, nullptr, 1);
}

void Effect_Fire::restrictBall(Ball* ball)
{
	ball->setX(constrain(ball->getX(), 0, 100));
	ball->setY(constrain(ball->getY(), 0, 100));
	ball->setZ(constrain(ball->getZ(), -10, 10));
}