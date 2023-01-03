
#include "Framework.h"
#include <Windows.h>
#include "Bullet.h"
#include <iostream>

/* Test Framework realization */
class MyFramework : public Framework {
	Bullet* b;
	Bullet* b2;
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
		b2 = new Bullet(400, 300, cursor.getX(), cursor.getY(), 5);
		return true;
	}

	virtual void Close() 
	{

	}

	virtual bool Tick() 
	{
		drawTestBackground();
		drawSprite(b2->getSprite(), b2->getPosition()->getX(), b2->getPosition()->getY());
		if (b != nullptr)
		{
			drawSprite(b->getSprite(), b->getPosition()->getX(), b->getPosition()->getY());
			b->Move();
		}
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) 
	{
		cursor.setPosition(x, y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) 
	{
		if (!isReleased)
		{
			std::cout << cursor.getX() << ':' << cursor.getY() << std::endl;
			b = new Bullet(400, 300, cursor.getX(), cursor.getY(), 5);
		}
	}

	virtual void onKeyPressed(FRKey k) 
	{

	}

	virtual void onKeyReleased(FRKey k) 
	{

	}
};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
