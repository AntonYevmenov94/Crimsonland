#include "Enemy.h"

Enemy::Enemy(int disp_w, int disp_h, int speed, Position* player, std::vector<Enemy*>* enemies)
{
	bool positionIsOk = false;

	this->speed = speed;
	sprite = createSprite("data/enemy.png");
	getSpriteSize(sprite, sprite_w, sprite_h);
	getSpriteSize(sprite, P_sprite_w, P_sprite_h);

	while (!positionIsOk)
	{
		start_x = 1 + rand() % (1000 - sprite_w);
		start_y = 1 + rand() % (800 - sprite_h);

		positionIsOk = true;

		if ((start_x > (player->getX() - 132) && start_x < (player->getX() + P_sprite_w + 132)) && 
			(start_y > (player->getY() - 132) && start_y < (player->getY() + P_sprite_h + 132))
			)
		{
			positionIsOk = false;
			continue;
		}
		if (!enemies->empty())
		{
			for (auto enemy : *enemies)
			{
				if (start_x >= (enemy->position->getX() - 10) && start_x <= (enemy->position->getX() + sprite_w + 10) &&
					start_y >= (enemy->position->getY() - 10) && start_y <= (enemy->position->getY() + sprite_h + 10)
					)
				{
					positionIsOk = false;
				}
			}
		}
	}
	position = new Position(start_x, start_y);
}

bool Enemy::Move(Position* player, std::vector<Enemy*>* enemies)
{
	int end_x = player->getX() + P_sprite_w / 2;
	int end_y = player->getY() + P_sprite_h / 2;

	Position s(end_x - position->getX(), end_y - position->getY());

	float length = sqrt(pow((s.getX()), 2) + pow((s.getY()), 2));

	float step_x = s.getX() / (length / speed);
	float step_y = s.getY() / (length / speed);

	position->changePosition(step_x, step_y);

	return false;
}

Enemy::~Enemy()
{
	delete position;
	destroySprite(sprite);
}
