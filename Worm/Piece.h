#pragma once
#include "Square.h"
#include "Util.h"

class Piece : public Square
{
	private:
		unsigned int direction = ALLEGRO_KEY_RIGHT;
		unsigned int acceleration = 10;
		void up();
		void left();
		void right();
		void down();

	public:
		Piece(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const char * name);
		~Piece();
		void set_direction(const unsigned int& direction);
		void move();
		unsigned int get_direction();
};

