#pragma once
#include "Object.h"
#include <cstdlib>
#include <ctime>

class Enemy : public Object
{
	int start_x = 0, start_y = 0;
public:
	Enemy(int disp_w, int disp_h, Position* player, std::vector<Enemy*> enemies);

	bool Move();

	~Enemy();
};

