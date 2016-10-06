// 
// 
// 

#include "Cube.h"


Cube::Cube(int16_t _x, int16_t _y, int16_t _z, int16_t width, int16_t height, int16_t depth) : Selector()
{
	this->_x = _x;
	this->_y = _y;
	this->_z = _z;
	this->width = width;
	this->height = height;
	this->depth = depth;
	
	this->_collect();
}

void Cube::_collect()
{
	this->_x1 = _x - width / 2;
	this->_y1 = _y - height / 2;
	this->_z1 = _z - depth / 2;
	this->_x2 = _x + width / 2;
	this->_y2 = _y + height / 2;
	this->_z2 = _z + depth / 2;
	Selector::_collect();
}

boolean Cube::isIn(int16_t _x, int16_t _y, int16_t _z)
{
	return _x1 < _x && _x < _x2 && _y1 < _y && _y < _y2 && _z1 < _z && _z < _z2;
}

void Cube::setDimension(int16_t width, int16_t height, int16_t depth)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->_collect();
}

void Cube::setWidth(int16_t width)
{
	this->width = width;
	this->_collect();
}

void Cube::setHeight(int16_t height)
{
	this->height = height;
	this->_collect();
}

void Cube::setDepth(int16_t depth)
{
	this->depth = depth;
	this->_collect();
}