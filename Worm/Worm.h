#pragma once
#include <deque>
#include <memory>
#include "Piece.h"
#include "allegro5/allegro_primitives.h"
#include <iostream>

class Worm
{
private:
	std::deque<std::shared_ptr<Piece>> DSPPWormBody;
	std::deque<std::pair<unsigned int, unsigned int>> move_command;
	int piece_width = 0;
	int piece_height = 0;
	
public:
	Worm(const int& width, const int& height);
	~Worm();
	bool try_move();
	void add_size();
	void draw(ALLEGRO_COLOR * color);
	void add_move_command(const unsigned int& command);
	bool first_piece_is_overlapping_itself();
	bool is_collided_screen_boundaries(const Square const * screen_boundaries);
	bool is_overlapping_some_piece(const Square const * object);
	bool first_piece_is_overlapping(const Square const * powerup);
};

