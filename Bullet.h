#pragma once
#include "Object.h"
#include "Enemy.h"

class Bullet :public Object
{
public:
	Bullet(int start_x, int start_y, float speed);

	void Move();

	void Destroy(Enemy* enemy);

	~Bullet();

};