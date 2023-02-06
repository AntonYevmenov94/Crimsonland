#include "Object.h"

void Object::Draw()
{
	drawSprite(sprite, position->getX(), position->getY());
}

Position* Object::getPosition()
{
	return position;
}

Sprite* Object::getSprite()
{
	return sprite;
}