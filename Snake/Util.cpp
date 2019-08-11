#include "Util.h"

bool  Util::is_horizontal(const unsigned int & direction)
{
	if (direction == ALLEGRO_KEY_LEFT || direction == ALLEGRO_KEY_RIGHT)
	{
		return true;
	}
	return false;
}

unsigned int Util::identify_pressed_key(const unsigned char * key)
{
	if (key[ALLEGRO_KEY_UP])
	{
		return ALLEGRO_KEY_UP;
	}
	else if (key[ALLEGRO_KEY_DOWN])
	{
		return ALLEGRO_KEY_DOWN;
	}
	else if (key[ALLEGRO_KEY_LEFT])
	{
		return ALLEGRO_KEY_LEFT;
	}
	else if (key[ALLEGRO_KEY_RIGHT])
	{
		return ALLEGRO_KEY_RIGHT;
	}
	return NULL;
}

void Util::reset_array_of_keys(unsigned char * key)
{
	for (unsigned int i = 0; i < ALLEGRO_KEY_MAX; i++)
	{
		key[i] &= Constant::KEY_SEEN;
	}
}
