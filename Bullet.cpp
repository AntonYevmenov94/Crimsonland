#include "Bullet.h"
#include <cmath>

Bullet::Bullet(int start_x, int start_y, int end_x, int end_y, float speed, int disp_w, int disp_h)
{
	display_w = disp_w;
	display_h = disp_w;

	this->speed = speed;

	//Sprite size
	sprite = createSprite("data/bullet.png");
	getSpriteSize(sprite, sprite_w, sprite_h);

	////Starting coordinate with dimension
	start_x -= sprite_w / 2;
	start_y -= sprite_h / 2;
	this->position = new Position(start_x, start_y);

	////Bullet movement vector
	end_x -= sprite_w / 2;
	end_y -= sprite_h / 2;
	Position s(end_x - start_x, end_y - start_y);
	float length = sqrt(pow((s.getX()), 2) + pow((s.getY()), 2));
	step_x = s.getX() / (length / speed);
	step_y = s.getY() / (length / speed);
}

bool Bullet::Move()
{
	position->changePosition(step_x, step_y);

	//Chek bullet out of range display
	if (position->getX() < 0 || position->getX() > display_w || position->getY() < 0 || position->getY() > display_h)
		return false;
	return true;
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
