#pragma once
#include "Framework.h"
#include "Position.h"

class Object
{
protected:
	float speed;
	Sprite* sprite;
	Position* position;
public:

	Sprite* getSprite();
};

