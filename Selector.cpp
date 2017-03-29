// 
// 
// 

#include "Selector.h"
#include "Hardware.h"

void Selector::_collect()
{
	this->ledCount = 0;
	for (uint8_t i = 0; i < LED_AMOUNT; i++)
	{
		if (this->isIn(hardware.leds[i]->_x, hardware.leds[i]->_y, hardware.leds[i]->_z))
		{
			this->leds[this->ledCount] = hardware.leds[i];
			this->ledCount++;
		}
	}
}

void Selector::setRGB(uint16_t r, uint16_t g, uint16_t b)
{
	for (uint8_t i = 0; i < this->ledCount; i++)
		this->leds[i]->setRGB(r, g, b);
}

void Selector::move(int16_t _x, int16_t _y, int16_t _z)
{
	this->_x += _x;
	this->_y += _y;
	this->_z += _z;
	_collect();
}

void Selector::setPosition(int16_t _x, int16_t _y, int16_t _z)
{
	this->_x = _x;
	this->_y = _y;
	this->_z = _z;
	_collect();
}

void Selector::setX(int16_t x)
{
	this->_x = x;
	_collect();
}

void Selector::setY(int16_t y)
{
	this->_y = y;
	_collect();
}

void Selector::setZ(int16_t z)
{
	this->_z = z;
	_collect();
}

int16_t Selector::getX()
{
	return _x;
}

int16_t Selector::getY()
{
	return _y;
}

int16_t Selector::getZ()
{
	return _z;
}

