#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < maxSegments)
	{
		segments[nSegments].InitBody(nSegments);
		++nSegments;
	}
}

void Snake::RestartInit(Location loc)
{
	nSegments = 1;
	segments[0].InitHead(loc);
}


bool Snake::collisionTest(Board& brd, Apple& apple)
{
	for (int i = 1; i < nSegments; ++i)
	{
		// Game over condition
		if (segments[0].GetLoc().x == segments[i].GetLoc().x && segments[0].GetLoc().y == segments[i].GetLoc().y)
		{
			// assert(false);
			brd.SetGameOver(true);
		}
	}

	if (segments[0].GetLoc().x == apple.GetLoc().x && segments[0].GetLoc().y == apple.GetLoc().y)
	{
		return true;
	} 
	else
	{
		return false;
	}

	// Draw the next cell 
	// brd.DrawCell(segments[0].GetNextLocation(delta_loc), Colors::Blue);
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::head_color;
}

void Snake::Segment::InitBody(int in_nSegments)
{	
	if (in_nSegments % 2 == 0)
	{
		c = Snake::body_color;
	}
	else
	{
		c = Snake::secondary_body_color;
	}
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert((abs(delta_loc.x) + abs(delta_loc.y)) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& brd) const
{
	// if location is in bounds
	if (loc.x >= 0 && loc.x <= brd.GetGridWidth() && loc.y >= 0 && loc.y <= brd.GetGridHeight())
	{
		brd.DrawCell(loc, c);
	}
	else
	{
		brd.SetGameOver(true);
	}
}

Location Snake::Segment::GetLoc()
{
	return loc;
}


