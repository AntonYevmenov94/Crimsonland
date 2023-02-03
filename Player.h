#pragma once
#include "Position.h"
#include "Framework.h"
#include "Object.h"
#include "Bullet.h"

class Player : public Object
{
	int display_w, display_h;
	bool isMoving = false;
	bool can_shot = true;
	int shot = 0;
	FRKey key;
	int clip = 0;
	std::vector<Bullet*> shots;
public:
	
	Player(float start_x, float start_y, float speed, int clip_size, int disp_w, int disp_h);

	void Move(FRKey key = FRKey::COUNT, bool isPressed = true);

	bool Moving();

	void Shot(Position* cursor);

	void Draw();

	~Player();

};

