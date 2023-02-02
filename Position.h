#pragma once
class Position
{
	float x, y;
public:
	Position(int x = 0, int y = 0);

	float getX();
	float getY();

	void setPosition(float x, float y);

	void changePosition(float x, float y);
};

