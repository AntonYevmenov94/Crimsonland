#pragma once
#include "Object.h"
#include "Enemy.h"

class Bullet :public Object
{
	int display_w, display_h;
	float step_x, step_y;
public:
	Bullet(int start_x, int start_y, int end_x, int end_y, float speed, int disp_w, int disp_h);

	bool Move();

	void Destroy(Enemy* enemy);

	~Bullet();

};