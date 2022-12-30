
#include "Framework.h"
#include <Windows.h>
#include "Bullet.h"

/* Test Framework realization */
class MyFramework : public Framework {
	Bullet* b;
public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 800;
		height = 600;
		fullscreen = false;
	}

	virtual bool Init() 
	{
		b = new Bullet(400, 300, 1);
		return true;
	}

	virtual void Close() 
	{

	}

	virtual bool Tick() 
	{
        drawTestBackground();
		drawSprite(b->getSprite(), b->getPosition()->getX(), b->getPosition()->getY());
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) 
	{

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) 
	{

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
