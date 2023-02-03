#include "Position.h"

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

float Position::getX()
{
	return x;
}

float Position::getY()
{
	return y;
}

void Position::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Position::changePosition(float x, float y)
{
	this->x += x;
	this->y += y;
}
