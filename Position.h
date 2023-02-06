#pragma once
class Position
{
	float x, y;
public:
	Position(float x = 0, float y = 0);

	float getX();
	float getY();

	void setPosition(float x, float y);

	void changePosition(float x, float y);
};

