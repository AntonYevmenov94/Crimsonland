
#include "Framework.h"
#include "Bullet.h"
#include <iostream>
#include "Player.h"
#include "Aim.h"

/* Test Framework realization */
class MyFramework : public Framework {
	
	bool begin = true;
	int sec;
	bool gameOver = false;
	int tick;
	Player* player;
	std::vector<Enemy*> enemies;
	Bullet* b;
	Position cursor;
	Aim* aim;
	Sprite* s_1;
	Sprite* s_2;
	Sprite* s_3;
	Sprite* s_go;

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
		for (int i = 0; i < 1; i++)
		{
			enemies.push_back(new Enemy(1000, 800, 1, player, &enemies));
		}
		//enemies[0]->getPosition()->setPosition(445, 400);
		aim = new Aim;
		s_1 = createSprite("data/1.png");
		s_2 = createSprite("data/2.png");
		s_3 = createSprite("data/3.png");
		s_go = createSprite("data/go.png");
		sec = 3;
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

		if (gameOver)
		{
			system("pause");
		}

	/*	if (begin)
		{
			if (sec < 3 && tick > getTickCount()) 
			{
				DrawBegin(sec + 1);
				return false;
			}
			if (sec == -1)
			{
				begin = false;
				destroySprite(s_1);
				destroySprite(s_2);
				destroySprite(s_3);
				destroySprite(s_go);
				return false;
			}
			tick = DrawBegin(sec) + 1000;
			sec--;
			return false;
		}*/
			
		for (auto enemy : enemies)
		{
			enemy->Draw();
			enemy->Move(player->getPosition(), &enemies);
			if(enemy->CatchUpPlayer(player->getPosition()))
				gameOver = true;
		}

		if (player->Moving())
			player->Move();

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) 
	{
		aim->setPosition(x, y);
		cursor.setPosition(x, y);
		//std::cout << x << ":" << y << std::endl;
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
		/*if (begin)
			return;*/
		player->Move(k, 1);
		std::cout << player->getPosition()->getX() << ":" << player->getPosition()->getY() << std::endl;
	}

	virtual void onKeyReleased(FRKey k) 
	{
		/*if (begin)
			return;*/
		player->Move(k, 0);
	}

	int DrawBegin(int sec)
	{
		switch (sec)
		{
		case 3:
			drawSprite(s_3, 450, 230);
			return getTickCount();
		case 2:
			drawSprite(s_2, 450, 230);
			return getTickCount();
		case 1:
			drawSprite(s_1, 450, 230);
			return getTickCount();
		case 0:
			drawSprite(s_go, 450, 280);
			return getTickCount();
		default:
			break;
		}
	}
};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
