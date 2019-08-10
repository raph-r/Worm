#include "Square.h"

Square::Square(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const char * name)
{
	this->top_left_x = top_left_x;
	this->top_left_y = top_left_y;
	this->width = width;
	this->height = height;
	this->name = name;
}

Square::~Square(){}

int Square::get_line_top() const
{
	return this->top_left_y;
}

int Square::get_line_botton() const
{
	return this->top_left_y + this->height;
}

int Square::get_line_left() const
{
	return this->top_left_x;
}

int Square::get_line_right() const
{
	return this->top_left_x + this->width;
}

bool Square::is_overlapped(const Square const * object)
{
	if (this->get_line_left() == object->get_line_left()
		&& this->get_line_top() == object->get_line_top()
		&& this->get_line_right() == object->get_line_right()
		&& this->get_line_botton() == object->get_line_botton())
	{
		return true;
	}
	return false;
}

const char * Square::get_name()
{
	return this->name;
}

void Square::add_top_left_x(const int & value)
{
	this->top_left_x += value;
}

void Square::add_top_left_y(const int & value)
{
	this->top_left_y += value;
}
