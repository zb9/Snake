#pragma once

struct Location
{
	void Add(const Location& delta_val);
	int x;
	int y;
};