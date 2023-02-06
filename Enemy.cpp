#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int disp_w, int disp_h, int speed, Object* player, std::vector<Enemy*>* enemies)
{
	bool positionIsOk = false;

	this->speed = speed;
	sprite = createSprite("data/enemy.png");
	getSpriteSize(sprite, sprite_w, sprite_h);
	getSpriteSize(player->getSprite(), P_sprite_w, P_sprite_h);
	while (!positionIsOk)
	{
		start_x = 1 + rand() % (disp_w - sprite_w);
		start_y = 1 + rand() % (disp_h - sprite_h);

		positionIsOk = true;

		if ((start_x > (player->getPosition()->getX() - 132) && start_x < (player->getPosition()->getX() + P_sprite_w + 132)) &&
			(start_y > (player->getPosition()->getY() - 132) && start_y < (player->getPosition()->getY() + P_sprite_h + 132))
			)
		{
			positionIsOk = false;
			continue;
		}
		if (!enemies->empty())
		{
			for (auto enemy : *enemies)
			{
				if (start_x >= (enemy->position->getX() - 20) && start_x <= (enemy->position->getX() + sprite_w + 20) &&
					start_y >= (enemy->position->getY() - 20) && start_y <= (enemy->position->getY() + sprite_h + 20)
					)
				{
					positionIsOk = false;
				}
			}
		}
	}
	position = new Position(start_x, start_y);
}

void Enemy::Move(Position* player, std::vector<Enemy*>* enemies)
{
	float tmp_x, tmp_y;
	bool positionIsOk = true;

	float end_x = player->getX() + P_sprite_w / 2;
	float end_y = player->getY() + P_sprite_h / 2;

	Position s(end_x - position->getX(), end_y - position->getY());

	float length = sqrt(pow((s.getX()), 2) + pow((s.getY()), 2));

	float step_x = s.getX() / (length / speed);
	float step_y = s.getY() / (length / speed);

	float new_center_x = 0;
	float new_center_y = 0;
	float E_center_x = 0;
	float E_center_y = 0;
	float distance;

	if (!enemies->empty())
	{
		for (auto enemy : *enemies)
		{
			if (this != enemy)
			{
				E_center_x = enemy->position->getX() + sprite_w / 2;
				E_center_y = enemy->position->getY() + sprite_h / 2;

				new_center_x = (position->getX() + sprite_w / 2) + step_x;
				new_center_y = (position->getY() + sprite_h / 2) + step_y;

				distance = sqrt(pow((E_center_x - new_center_x), 2) + pow(E_center_y - new_center_y, 2));
				if (distance <= 28)
				{
					step_x = step_y = 0;
					break;
				}
			}
		}
	}
	position->changePosition(step_x, step_y);
}

bool Enemy::CatchUpPlayer(Position* player)
{
	float P_center_x = player->getX() + (float)P_sprite_w / 2;
	float P_center_y = player->getY() + (float)P_sprite_h / 2;

	float center_x = position->getX() + sprite_w / 2;
	float center_y = position->getY() + sprite_h / 2;

	float distance = sqrt(pow((P_center_x - center_x), 2) + pow(P_center_y - center_y, 2));
	
	return (distance <= 40) ? true : false;
}

Enemy::~Enemy()
{
	delete position;
	destroySprite(sprite);
}
