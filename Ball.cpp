// 
// Just for selecting LEDs
// 

#include "Ball.h"

Ball::Ball(int16_t _x, int16_t _y, int16_t _z, int16_t radius) : Selector()
{
	this->_x = _x;
	this->_y = _y;
	this->_z = _z;
	_radius = radius;
	_radius2 = pow(radius, 2);
	_collect();
}

void Ball::setRadius(int16_t radius)
{
	_radius = radius;
	_radius2 = pow(radius, 2);
	_collect();
}

boolean Ball::isIn(int16_t _x, int16_t _y, int16_t _z)
{
	return pow(this->_x - _x, 2) + pow(this->_y - _y, 2) + pow(this->_z - _z, 2) < _radius2;
}

int16_t Ball::dist(int16_t _x, int16_t _y, int16_t _z)
{
	return sqrt(pow(this->_x - _x, 2) + pow(this->_y - _y, 2) + pow(this->_z - _z, 2)) - _radius;
}