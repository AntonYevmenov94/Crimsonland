#pragma once
#include "Position.h"
#include "Framework.h"
#include "Object.h"

class Player : public Object
{
	int display_w, display_h;
	bool isMoving = false;
	FRKey key;
public:
	
	Player(float start_x, float start_y, float speed, int disp_w, int disp_h);

	void Move(FRKey key = FRKey::COUNT, bool isPressed = true);

	bool Moving();

	void Shot();

	~Player();

};

