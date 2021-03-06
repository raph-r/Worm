#include "Piece.h"

Piece::Piece(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const char * name) : Square(top_left_x, top_left_y, width, height, name){}

Piece::~Piece(){}

void Piece::set_direction(const unsigned int & new_direction)
{
	if (this->direction != new_direction && Util::is_horizontal(this->direction) != Util::is_horizontal(new_direction))
	{
		this->direction = new_direction;
	}
}

void Piece::move()
{
	switch (this->direction)
	{
	case ALLEGRO_KEY_UP:
		this->up();
		break;
	case ALLEGRO_KEY_DOWN:
		this->down();
		break;
	case ALLEGRO_KEY_LEFT:
		this->left();
		break;
	case ALLEGRO_KEY_RIGHT:
		this->right();
		break;
	default:
		break;
	}
}

unsigned int Piece::get_direction()
{
	return this->direction;
}

void Piece::up()
{
	this->top_left_y -= Constant::ACCELERATION_OF_PIECE;
}

void Piece::left()
{
	this->top_left_x -= Constant::ACCELERATION_OF_PIECE;
}

void Piece::right()
{
	this->top_left_x += Constant::ACCELERATION_OF_PIECE;
}

void Piece::down()
{
	this->top_left_y += Constant::ACCELERATION_OF_PIECE;
}
