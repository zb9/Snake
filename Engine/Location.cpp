#include "Location.h"

void Location::Add(const Location& delta_val)
{
	x += delta_val.x;
	y += delta_val.y;
}