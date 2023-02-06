#include "Player.h"

Player::Player(float start_x, float start_y, float speed, int clip_size, int disp_w, int disp_h)
{
	start_x -= 32;
	start_y -= 32;
	display_w = disp_w;
	display_h = disp_h;
	position = new Position(start_x, start_y);
	sprite = createSprite("data/avatar.jpg");
	getSpriteSize(sprite, sprite_w, sprite_h);
	this->speed = speed;
	clip = clip_size;
}

void Player::Move(int& bg_pos_x, int& bg_pos_y, std::vector<Enemy*>& enemies, FRKey key, bool isPressed)
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
		if (bg_pos_x > -200)
		{
			bg_pos_x -= speed;
			for (auto enemy : enemies)
				enemy->getPosition()->changePosition(-speed, 0);
			break;
		}
		if ((position->getX() + sprite_w) + speed < display_w)
			position->changePosition(speed, 0);
		else
			position->changePosition(display_w - (position->getX() + sprite_w), 0);
		break;
	case FRKey::LEFT:
		if (bg_pos_x < 0)
		{
			bg_pos_x += speed;
			for (auto enemy : enemies)
				enemy->getPosition()->changePosition(speed, 0);
			break;
		}
		if (position->getX() - speed > 0)
			position->changePosition(-speed, 0);
		else
			position->changePosition(- position->getX(), 0);
		break;
	case FRKey::DOWN:
		if (bg_pos_y > -200)
		{
			bg_pos_y -= speed;
			for (auto enemy : enemies)
				enemy->getPosition()->changePosition(0, -speed);
			break;
		}
		if ((position->getY() + sprite_h) + speed < display_h)
			position->changePosition(0, speed);
		else
			position->changePosition(0, display_h - (position->getY() + sprite_h));
		break;
	case FRKey::UP:
		if (bg_pos_y < 0)
		{
			bg_pos_y += speed;
			for (auto enemy : enemies)
				enemy->getPosition()->changePosition(0, speed);
			break;
		}
		if (position->getY() - speed > 0)
			position->changePosition(0, -speed);
		else
			position->changePosition(0, -position->getY());
		break;
	default:
		break;
	}
}

void Player::Shot(Position* cursor)
{
	if (shot == clip && shots.empty() && !can_shot)
	{
		can_shot = true;
		shot = 0;
	}
	if (can_shot)
	{
		shots.push_back(new Bullet(position->getX() + (sprite_w / 2), position->getY() + (sprite_h / 2), cursor->getX(), cursor->getY(), 5, display_w, display_h));
		shot++;
	}
	if (shot == clip)
		can_shot = false;
}

bool Player::Moving()
{
	return isMoving ? true : false;
}

Player::~Player()
{
	delete position;
	destroySprite(sprite);
}

void Player::DrawShots(std::vector<Enemy*> &enemies)
{
	if (!shots.empty())
	{
		std::vector<Bullet*>::iterator it = shots.begin();
		for (int i = 0; i < shots.size(); i++)
		{
			shots[i]->Draw();
			if (!shots[i]->Move(enemies))
			{
				delete shots[i];
				shots.erase(it + i);
			}
		}
	}
}