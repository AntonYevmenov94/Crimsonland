#include "Enemy.h"

Enemy::Enemy(int start_x, int start_y, int disp_w, int disp_h)
{
	
	sprite = createSprite("data/enemy.png");
	getSpriteSize(sprite, sprite_w, sprite_h);
	position = new Position(start_x, start_y);
}

Enemy::~Enemy()
{
	delete position;
	destroySprite(sprite);
}
