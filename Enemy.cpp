#include "Enemy.h"

Enemy::Enemy(int disp_w, int disp_h, Position* player, std::vector<Enemy*> enemies)
{
	int P_sprite_w, P_sprite_h;
	bool positionIsOk = false;

	sprite = createSprite("data/enemy.png");
	getSpriteSize(sprite, sprite_w, sprite_h);
	getSpriteSize(sprite, P_sprite_w, P_sprite_h);

	while (!positionIsOk)
	{
		start_x = 1 + rand() % 1000;
		start_y = 1 + rand() % 800;

		positionIsOk = true;

		if ((start_x > (player->getX() - 132) && start_x < (player->getX() + P_sprite_w + 132)) && 
			(start_y > (player->getY() - 132) && start_y < (player->getY() + P_sprite_h + 132))
			)
		{
			positionIsOk = false;
			continue;
		}
		if (!enemies.empty())
		{
			for (auto enemy : enemies)
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

Enemy::~Enemy()
{
	delete position;
	destroySprite(sprite);
}
