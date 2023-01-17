#include "Aim.h"

Aim::Aim()
{
	sprite = createSprite("data/circle.tga");
	position = new Position(0, 0);
	getSpriteSize(sprite, sprite_w, sprite_h);
}

void Aim::setPosition(int x, int y)
{
	position->setPosition(x - sprite_w / 2, y - sprite_h / 2);
}
