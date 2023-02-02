
#include "Framework.h"
#include <Windows.h>
#include "Bullet.h"
#include <iostream>
#include "Player.h"
#include "Aim.h"

/* Test Framework realization */
class MyFramework : public Framework {
	Player* player;
	std::vector<Enemy*> enemies;
	Bullet* b;
	Position cursor;
	Aim* aim;
public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 1000;
		height = 800;
		fullscreen = false;
	}

	virtual bool Init() 
	{
		srand(time(0));
		player = new Player(500, 400, 3, 5, 1000, 800);
		for (int i = 0; i < 5; i++)
		{
			enemies.push_back(new Enemy(1000, 800, 1, player->getPosition(), &enemies));
		}
		aim = new Aim;
		return true;
	}

	virtual void Close() 
	{

	}

	virtual bool Tick() 
	{
		drawTestBackground();

		aim->Draw();
		player->Draw();

		for (auto enemy : enemies)
		{
			enemy->Draw();
			enemy->Move(player->getPosition(), &enemies);
		}

		if (player->Moving())
			player->Move();

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) 
	{
		aim->setPosition(x, y);
		cursor.setPosition(x, y);
		std::cout << x << ":" << y << std::endl;
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) 
	{
		if (!isReleased && button == FRMouseButton::LEFT)
		{
			player->Shot(&cursor);
		}
		if (button == FRMouseButton::RIGHT)
		{
			system("cls");
			std::cout << player->getPosition()->getX() << std::endl;
		}
	}

	virtual void onKeyPressed(FRKey k) 
	{
		player->Move(k, 1);
		std::cout << player->getPosition()->getX() << ":" << player->getPosition()->getY() << std::endl;
	}

	virtual void onKeyReleased(FRKey k) 
	{
		player->Move(k, 0);
	}
};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
