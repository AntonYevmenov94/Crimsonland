#pragma once
#include "Object.h"
#include <cstdlib>
#include <ctime>

class Enemy : public Object
{
	int start_x, start_y;
public:
	Enemy(int start_x, int start_y, int disp_w, int disp_h);

	bool Move();

	~Enemy();
};

