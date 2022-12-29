
#include "Framework.h"
#include "Player.h"
#include <Windows.h>

/* Test Framework realization */
class MyFramework : public Framework {
	
	Player* player;
public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 800;
		height = 600;
		fullscreen = false;
	}

	virtual bool Init() 
	{
		player = new Player(800, 600, 10, 1);
		return true;
	}

	virtual void Close() 
	{

	}

	virtual bool Tick() 
	{
        drawTestBackground();
		drawSprite(player->getSprite(), player->getPosition()->getX(), player->getPosition()->getY());
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
		player->Move(k);
	}

	virtual void onKeyReleased(FRKey k) 
	{

	}
};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
