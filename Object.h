#pragma once
#include "Framework.h"
#include "Position.h"
#include <string>

class Object
{
protected:
	float speed;
	int sprite_h, sprite_w;
	Sprite* sprite;
	Position* position;
public:

	void Draw();

	Position* getPosition();

	Sprite* getSprite();
};

