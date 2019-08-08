#include "Util.h"

bool  Util::is_horizontal(const unsigned int & direction)
{
	if (direction == ALLEGRO_KEY_LEFT || direction == ALLEGRO_KEY_RIGHT)
	{
		return true;
	}
	return false;
}
