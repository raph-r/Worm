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

bool Object::is_overlapped(const Object const * object)
{
	if (this->collision_line_left() == object->collision_line_left()
		&& this->collision_line_top() == object->collision_line_top()
		&& this->collision_line_right() == object->collision_line_right()
		&& this->collision_line_botton() == object->collision_line_botton())
	{
		return true;
	}
	return false;
}

const char * Object::get_name()
{
	return this->name;
}

void Object::add_top_left_x(const int & value)
{
	this->top_left_x += value;
}

void Object::add_top_left_y(const int & value)
{
	this->top_left_y += value;
}
