#pragma once
class Position
{
	int x, y;
public:
	Position(int x, int y);

	int getX();
	int getY();

	void changePosition(int x, int y);
};

