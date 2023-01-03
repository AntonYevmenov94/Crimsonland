#include "Position.h"

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Position::getX()
{
	return x;
}

int Position::getY()
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
