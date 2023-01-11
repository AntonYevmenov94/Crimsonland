#include "Player.h"

Player::Player(float start_x, float start_y, float speed, int disp_w, int disp_h)
{
	start_x -= 32;
	start_y -= 32;
	display_w = disp_w;
	display_h = disp_h;
	position = new Position(start_x, start_y);
	sprite = createSprite("data/avatar.jpg");
	getSpriteSize(sprite, sprite_w, sprite_h);
	this->speed = speed;
}

void Player::Move(FRKey key, bool isPressed)
{
	if (isPressed)
	{
		isMoving = true;
		if (key != FRKey::COUNT)
			this->key = key;
	}
	else
	{
		if (this->key == key)
		{
			isMoving = false;
			return;
		}
	}
	switch (this->key)
	{
	case FRKey::RIGHT:
		if ((position->getX() + sprite_w) + speed < display_w)
			position->changePosition(speed, 0);
		else
			position->changePosition(display_w - (position->getX() + sprite_w), 0);
		break;
	case FRKey::LEFT:
		if (position->getX() - speed > 0)
			position->changePosition(-speed, 0);
		else
			position->changePosition(- position->getX(), 0);
		break;
	case FRKey::DOWN:
		if ((position->getY() + sprite_h) + speed < display_h)
			position->changePosition(0, speed);
		else
			position->changePosition(0, display_h - (position->getY() + sprite_h));
		break;
	case FRKey::UP:
		if (position->getY() - speed > 0)
			position->changePosition(0, -speed);
		else
			position->changePosition(0, -position->getY());
		break;
	default:
		break;
	}
}

void Player::Shot()
{
}

bool Player::Moving()
{
	return isMoving ? true : false;
}
