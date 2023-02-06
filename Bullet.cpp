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

bool Bullet::Move(std::vector<Enemy*>& enemies)
{
	position->changePosition(step_x, step_y);

	//Chek bullet out of range display
	if (position->getX() < 0 || position->getX() > display_w || position->getY() < 0 || position->getY() > display_h || IsHit(enemies))
		return false;
	return true;
}

bool Bullet::IsHit(std::vector<Enemy*>& enemies)
{
	float E_center_x, E_center_y;
	float B_center_x, B_center_y;
	int E_sprite_w;
	int E_sprite_h;
	getSpriteSize(enemies[0]->getSprite(), E_sprite_w, E_sprite_h);

	B_center_x = position->getX() + sprite_w / 2;
	B_center_y = position->getY() + sprite_h / 2;

	float distance = 0;

	for (int i = 0; i < enemies.size(); i++)
	{
		E_center_x = enemies[i]->getPosition()->getX() + E_sprite_w / 2;
		E_center_y = enemies[i]->getPosition()->getY() + E_sprite_h / 2;

		distance = sqrt(pow((E_center_x - B_center_x), 2) + pow(E_center_y - B_center_y, 2));
		if (distance < 18)
		{
			Destroy(enemies[i]);
			enemies.erase(enemies.begin() + i);
			return true;
		}
	}
	return false;
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
