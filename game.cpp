
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
	Sprite* background;
	int bg_pos_x, bg_pos_y;

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 1000;
		height = 800;
		fullscreen = false;
	}

	virtual bool Init() 
	{
		//showCursor(false);
		srand(time(0));
		
		background = createSprite("data/bg.jpg");
		bg_pos_x = bg_pos_y = -500;

		player = new Player(500, 400, 3, 5, 1000, 800);
		aim = new Aim;
		for (int i = 0; i < 5; i++)
		{
			enemies.push_back(new Enemy(1000, 800, 1, player, &enemies));
		}
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
		delete player;
		delete aim;
		destroySprite(s_lose);
		destroySprite(s_win);
		destroySprite(background);
		if (!enemies.empty())
		{
			for (auto enemy : enemies)
				delete enemy;

			enemies.clear();
		}
		gameOver = false;
		begin = true;
		win = lose = false;
		Init();
	}

	virtual bool Tick() 
	{
		drawTestBackground();
	
		drawSprite(background, bg_pos_x, bg_pos_y);

		aim->Draw();
		player->Draw();
		player->DrawShots(enemies);
		
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

		if (gameOver)
		{
			if (getTickCount() < tick + 3000)
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
			else
				Close();
			
		}
			
		if (!enemies.empty())
		{
			for (auto enemy : enemies)
			{
				enemy->Draw();
				enemy->Move(player->getPosition(), &enemies);
				if (enemy->CatchUpPlayer(player->getPosition()))
				{
					tick = getTickCount();
					gameOver = true;
					lose = true;
				}
			}
		}
		else
		{
			tick = getTickCount();
			gameOver = true;
			win = true;
		}
		
		if (player->Moving())
			player->Move(bg_pos_x, bg_pos_y, enemies);

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) 
	{
		aim->setPosition(x, y);
		cursor.setPosition(x, y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) 
	{
		if (!isReleased && button == FRMouseButton::LEFT && !gameOver && !begin)
		{
			player->Shot(&cursor);
		}
	}

	virtual void onKeyPressed(FRKey k) 
	{
		if (begin || gameOver)
			return;
		player->Move(bg_pos_x, bg_pos_y, enemies, k, 1);
	}

	virtual void onKeyReleased(FRKey k) 
	{
		if (begin || gameOver)
			return;
		player->Move(bg_pos_x, bg_pos_y, enemies, k, 0);
	}

	int DrawBegin(int sec)
	{
		int x, y, w, h;
		getScreenSize(w, h);
		switch (sec)
		{
		case 3:
			getSpriteSize(s_3, x, y);
			drawSprite(s_3, (w - x) / 2, (h - y) / 2);
			return getTickCount();
		case 2:
			getSpriteSize(s_2, x, y);
			drawSprite(s_2, (w - x) / 2, (h - y) / 2);
			return getTickCount();
		case 1:
			getSpriteSize(s_1, x, y);
			drawSprite(s_1, (w - x) / 2, (h - y) / 2);
			return getTickCount();
		case 0:
			getSpriteSize(s_go, x, y);
			drawSprite(s_go, (w - x) / 2, (h - y) / 2);
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
