
#include "Framework.h"
#include <Windows.h>
#include "Bullet.h"
#include <iostream>
#include "Player.h"

/* Test Framework realization */
class MyFramework : public Framework {
	Player* player;
	Bullet* b;
	Position cursor;
	int k = 0;
public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 800;
		height = 600;
		fullscreen = false;
	}

	virtual bool Init() 
	{
		player = new Player(400, 300, 3, 5, 800, 600);
		return true;
	}

	virtual void Close() 
	{

	}

	virtual bool Tick() 
	{
		drawTestBackground();
		player->Draw();

		if (player->Moving())
			player->Move();
		/*if (b != nullptr)
		{
			b->Draw();
			if (!b->Move())
			{
				delete b;
				b = nullptr;
			}
		}*/
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) 
	{
		cursor.setPosition(x, y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) 
	{
		if (!isReleased && button == FRMouseButton::LEFT)
		{
			//std::cout << cursor.getX() << ':' << cursor.getY() << std::endl;
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
