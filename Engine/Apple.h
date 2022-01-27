#pragma once
#include "Board.h"

class Apple
{
public:
	void Init(int in_x, int in_y)
	{
		x = in_x;
		y = in_y;
	}

	void Draw(Board& brd);
	Location GetLoc();

private:
	int x;
	int y;
};