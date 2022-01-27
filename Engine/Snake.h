#pragma once
#include "Board.h"
#include "Keyboard.h"
#include "Apple.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(int in_nSegments);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;

		Location GetLoc();

	private:
		Location loc;
		Color c;
	};
public:

	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow();

	bool collisionTest(Board& brd, Apple& apple);

	void Draw(Board& brd) const;

private:
	static constexpr Color head_color = Colors::Yellow;
	static constexpr Color body_color = Colors::Green;
	static constexpr Color secondary_body_color = Color(0, 100, 0);
	static constexpr int maxSegments = 100;

	Segment segments[maxSegments];

	int nSegments = 1;
};