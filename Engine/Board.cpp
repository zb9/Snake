#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{

}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x <= width);
	assert(loc.y >= 0);
	assert(loc.y <= height);
	gfx.DrawRectDim(60 + (loc.x * dimension), 60 + (loc.y * dimension), dimension, dimension, c);
}

int Board::GetGridWidth()
{
	return width;
}

int Board::GetGridHeight()
{
	return height;
}

bool Board::GetGameOver()
{
	return gameOver;
}

void Board::SetGameOver(bool in)
{
	gameOver = in;
}
