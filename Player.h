#pragma once
#include "Position.h"
#include "Framework.h"

class Player
{
	int speed;
	int clipSize;

	Position* position;
	Sprite* sprite = createSprite("data/avatar.jpg");

public:
	Player(int width, int height, int speed, int clipSize);
	
	void Move(FRKey key);
	
	void Shoot();
	
	//�������� ���������� ������
	Position* getPosition();
	
	//�������� ������ ������
	Sprite* getSprite();

	//����������� ������
	void Die();

};

