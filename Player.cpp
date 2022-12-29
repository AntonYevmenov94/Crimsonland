#include "Player.h"

Player::Player(int width, int height, int speed, int clipSize)
{
	//������ ������
	this->clipSize = clipSize;

	//��������
	this->speed = speed;

	//��������� �������
	position = new Position((width / 2) - 32, (height / 2) - 32);

}

void Player::Move(FRKey key)
{
	switch (key)
	{
	case FRKey::RIGHT:
		position->movePosition(speed, 0);
		break;
	case FRKey::LEFT:
		position->movePosition(-speed, 0);
		break;
	case FRKey::DOWN:
		position->movePosition(0, speed);
		break;
	case FRKey::UP:
		position->movePosition(0, -speed);
		break;
	default:
		break;
	}
}

Position* Player::getPosition()
{
	return position;
}

Sprite* Player::getSprite()
{
	return sprite;
}

void Player::Die()
{
	delete position;
	destroySprite(sprite);
}

