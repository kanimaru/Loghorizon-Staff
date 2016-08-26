// 
// Just for selecting LEDs
// 

#include "Ball.h"


Ball::Ball(int16_t x, int16_t y, int16_t z, int16_t radius)
{
	this->x = x;
	this->y = y;
	this->z = z;
	_radius = radius;
	_radius2 = pow(radius, 2);
}

boolean Ball::isIn(int16_t x, int16_t y, int16_t z)
{
	return pow(x - x, 2) + pow(y - y, 2) + pow(z - z, 2) < _radius2;
}

int16_t Ball::dist(int16_t x, int16_t y, int16_t z)
{
	return sqrt(pow(this->x - x, 2) + pow(this->y - y, 2) + pow(this->z - z, 2)) - _radius;
}

void Ball::debug()
{
	Serial.print("x: ");
	Serial.print(x);
	Serial.print(" y: ");
	Serial.print(y);
	Serial.print(" z: ");
	Serial.println(z);
}