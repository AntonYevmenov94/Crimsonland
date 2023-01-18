
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
	int k = 0;
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
			int start_x = 1 + rand() % 1000;
			int start_y = 1 + rand() % 800;
			enemies.push_back(new Enemy(start_x, start_y, 1000, 800));
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
		
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Draw();
		}
		/*for(auto enemy:enemies)
			enemy->Draw();*/

		if (player->Moving())
			player->Move();

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) 
	{
		aim->setPosition(x, y);
		cursor.setPosition(x, y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) 
	{
		if (!isReleased && button == FRMouseButton::LEFT)
		{
			player->Shot(&cursor);
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
