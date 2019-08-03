#pragma once
#include "Object.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>

class Powerup : public Object
{
	public:
		Powerup(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const char * name);
		~Powerup();
		void draw(ALLEGRO_COLOR * color);
		void change_location();
};