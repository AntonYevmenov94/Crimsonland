#include "Bullet.h"

Bullet::Bullet(int start_x, int start_y, float speed)
{
	this->speed = speed;

	//размеры спрайта
	int h, w;

	sprite = createSprite("data/bullet.png");
	getSpriteSize(sprite, w, h);

	//Начальная координата с учетом размера
	start_x -= w;
	start_y -= h;

	this->position = new Position(start_x, start_y);
}

void Bullet::Destroy(Enemy* enemy)
{
	delete enemy;
}

Bullet::~Bullet()
{
	delete position;
	destroySprite(sprite);
}
