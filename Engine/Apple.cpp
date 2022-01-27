#include "Apple.h"

void Apple::Draw(Board& brd)
{
	brd.DrawCell({ x, y }, Colors::Red);
}

Location Apple::GetLoc()
{
	Location loc;
	loc = { x, y };
	return loc;
}