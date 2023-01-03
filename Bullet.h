#pragma once
#include "Object.h"
#include "Enemy.h"

class Bullet :public Object
{
	float step_x, step_y;
public:
	Bullet(int start_x, int start_y, int end_x, int end_y, float speed);

	void Move();

	void Destroy(Enemy* enemy);

	~Bullet();

};