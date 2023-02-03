#pragma once
#include "Object.h"
#include <cstdlib>
#include <ctime>

class Enemy : public Object
{
	int start_x = 0, start_y = 0;
	int P_sprite_w, P_sprite_h;

public:
	Enemy(int disp_w, int disp_h, int speed, Object* player, std::vector<Enemy*>* enemies);

	void Move(Position* player, std::vector<Enemy*>* enemies);

	bool CatchUpPlayer(Position* player);

	~Enemy();
};

