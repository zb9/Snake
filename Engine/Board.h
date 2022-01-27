#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);

	void DrawCell(const Location& loc, Color c);
	int GetGridWidth();
	int GetGridHeight();

	bool GetGameOver();
	void SetGameOver(bool in);

private:
	static constexpr int dimension = 20;
	static constexpr int width = 33;
	static constexpr int height = 23;

	bool gameOver = false;
	Graphics& gfx;
};