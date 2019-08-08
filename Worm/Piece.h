#pragma once
#include "Object.h"
#include "allegro5/allegro.h"

class Piece : public Object
{
	private:
		unsigned int direction = ALLEGRO_KEY_RIGHT;
		unsigned int acceleration = 10;
		void up();
		void left();
		void right();
		void down();
		bool is_horizontal(const unsigned int& direction);

	public:
		Piece(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const char * name);
		~Piece();
		void add_top_left_x(const int& value);
		void add_top_left_y(const int& value);
		void set_direction(const unsigned int& direction);
		void move();
		unsigned int get_direction();
};

