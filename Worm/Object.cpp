#include "Object.h"

Object::Object(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const char * name)
{
	this->top_left_x = top_left_x;
	this->top_left_y = top_left_y;
	this->width = width;
	this->height = height;
	this->name = name;
}

Object::~Object(){}

int Object::collision_line_top() const
{
	return this->top_left_y;
}

int Object::collision_line_botton() const
{
	return this->top_left_y + this->height;
}

int Object::collision_line_left() const
{
	return this->top_left_x;
}

int Object::collision_line_right() const
{
	return this->top_left_x + this->width;
}

const char * Object::get_name()
{
	return this->name;
}