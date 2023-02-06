
#include "Framework.h"
#include "Bullet.h"
#include <iostream>
#include "Player.h"
#include "Aim.h"

/* Test Framework realization */
class MyFramework : public Framework {
	
	bool begin = true;
	bool win, lose;
	int sec;
	bool gameOver = false;
	unsigned tick;
	Player* player;
	std::vector<Enemy*> enemies;
	Bullet* b;
	Position cursor;
	Aim* aim;
	Sprite* s_1;
	Sprite* s_2;
	Sprite* s_3;
	Sprite* s_go;
	Sprite* s_lose;
	Sprite* s_win;

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
			enemies.push_back(new Enemy(1000, 800, 1, player, &enemies));
		}
		aim = new Aim;
		s_1 = createSprite("data/1.png");
		s_2 = createSprite("data/2.png");
		s_3 = createSprite("data/3.png");
		s_go = createSprite("data/go.png");
		s_lose = createSprite("data/lose.png");
		s_win = createSprite("data/win.png");
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
		player->DrawShots(enemies);

		if (gameOver)
		{
			int x, y, w, h;
			getScreenSize(w, h);
			if (lose)
			{
				getSpriteSize(s_lose, x, y);
				drawSprite(s_lose, (w - x) / 2, (h - y) / 2);
				for (auto enemy : enemies)
					enemy->Draw();
			}
			else
			{
				getSpriteSize(s_win, x, y);
				drawSprite(s_win, (w - x) / 2, (h - y) / 2);
			}
			
			return false;
		}

		if (begin)
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
		}
			
		if (!enemies.empty())
		{
			for (auto enemy : enemies)
			{
				enemy->Draw();
				enemy->Move(player->getPosition(), &enemies);
				if (enemy->CatchUpPlayer(player->getPosition()))
				{
					gameOver = true;
					lose = true;
				}
			}
		}
		else
		{
			gameOver = true;
			win = true;
		}
		
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
		if (begin || gameOver)
			return;
		player->Move(k, 1);
	}

	virtual void onKeyReleased(FRKey k) 
	{
		if (begin || gameOver)
			return;
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
