#include "Bullet.h"
#include <cmath>

Bullet::Bullet(int start_x, int start_y, int end_x, int end_y, float speed)
{
	this->speed = speed;

	//������� �������
	int sprite_h, sprite_w;
	sprite = createSprite("data/bullet.png");
	getSpriteSize(sprite, sprite_w, sprite_h);

	//��������� ���������� � ������ �������
	start_x -= sprite_w / 2;
	start_y -= sprite_h / 2;
	this->position = new Position(start_x, start_y);

	//������ �������� ����
	end_x -= sprite_w / 2;
	end_y -= sprite_h / 2;
	float length = sqrt(pow((start_x + end_x), 2) + pow((start_y + end_y), 2));
	Position s(end_x - start_x, end_y - start_y);
	step_x = s.getX() / (length / speed);
	step_y = s.getY() / (length / speed);
}

void Bullet::Move()
{
	position->changePosition(step_x, step_y);
}

void Bullet::Destroy(Enemy* enemy)
{
	delete enemy;
}

Bullet::~Bullet()
{
	delete position;
	destroySprite(sprite);
}
