/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),

	rng(std::random_device()()),
	loc_xDist(0, brd.GetGridWidth()),
	loc_yDist(0, brd.GetGridHeight()),

	snake({ 18, 13 })

{
	for (int i = 0; i < maxApples; ++i)
	{
		apple[i].Init(loc_xDist(rng), loc_yDist(rng));
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();	
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	// Motion 
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		if (!motionDbn && currentDirection != 2)
		{
			currentDirection = 0;
			motionDbn = true;
		}

	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (!motionDbn && currentDirection != 3)
		{
			currentDirection = 1;
			motionDbn = true;
		}
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (!motionDbn && currentDirection != 0)
		{
			currentDirection = 2;
			motionDbn = true;
		}
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (!motionDbn && currentDirection != 1)
		{
			currentDirection = 3;
			motionDbn = true;
		}

	}

	if (currentDirection == 0) { delta_loc = { 0, -1 }; }
	if (currentDirection == 1) { delta_loc = { 1, 0 }; }
	if (currentDirection == 2) { delta_loc = { 0, 1 }; }
	if (currentDirection == 3) { delta_loc = { -1, 0 }; }

	// Tick operations
	currentTick -= ft.Mark();

	if (currentTick <= 0)
	{
		// Test for snake collision
		//if (wnd.kbd.KeyIsPressed(VK_CONTROL))
		//{
		//	    snake.Grow();
		//}
		if (snake.collisionTest(brd, apple[currentApples])) 
		{ 
			snake.Grow(); 
			++currentApples; 
			if (secondsPerTick > 0.08) 
			{ 
				secondsPerTick *= 0.9;
			} 
		}
		snake.MoveBy(delta_loc);
		motionDbn = false;
		currentTick = secondsPerTick;
	}
}
void Game::ComposeFrame()
{

	// Entity Loading
	if (!brd.GetGameOver())
	{
		apple[currentApples].Draw(brd);
		snake.Draw(brd);
	}

	// Map Loading

	int thickness = 3;
	int dimension = 20;
	Color map_color = Colors::Black;

	for (int i = 0; i < Graphics::ScreenWidth / 20; ++i)
	{
		gfx.DrawRectDim((i * 20 + 20 - thickness), 0, thickness, Graphics::ScreenHeight, map_color);
	}
	for (int i = 0; i < Graphics::ScreenHeight / 20; ++i)
	{
		gfx.DrawRectDim(0, (i * 20 + 20 - thickness), Graphics::ScreenWidth, thickness, map_color);
	} 

	sprite.DrawLogo(384, 16, gfx);

	// top outline
	gfx.DrawRectDim(3 * dimension - 2 * thickness, 3 * dimension - 2 * thickness, Graphics::ScreenWidth - 6 * dimension + 3 * thickness, thickness, Colors::Blue);
	// left outline
	gfx.DrawRectDim(3 * dimension - 2 * thickness, 3 * dimension - thickness, thickness, Graphics::ScreenHeight - 6 * dimension + thickness, Colors::Blue);
	// bottom outline
	gfx.DrawRectDim(3 * dimension - 2 * thickness, Graphics::ScreenHeight - 3 * dimension, Graphics::ScreenWidth - 6 * dimension + 3 * thickness, thickness, Colors::Blue);
	// right outline
	gfx.DrawRectDim(Graphics::ScreenWidth -  3 * dimension, 3 * dimension - thickness, thickness, Graphics::ScreenHeight - 6 * dimension + thickness, Colors::Blue);
	if (brd.GetGameOver())
	{
		sprite.DrawGameOver(360, 240, gfx);
	}
}
