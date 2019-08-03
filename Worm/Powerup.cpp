#include "Powerup.h"

Powerup::Powerup(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const char * name) : Object(top_left_x, top_left_y, width, height, name){}

Powerup::~Powerup(){}

void Powerup::draw(ALLEGRO_COLOR * color)
{
	al_draw_filled_rectangle(this->collision_line_left(), this->collision_line_top(), this->collision_line_right(), this->collision_line_botton(), *color);
}

void Powerup::change_location()
{
	this->top_left_x = rand() % ((640 - 20) - this->width) + 10; // screen width - margin left and right - object width
	this->top_left_y = rand() % ((480 - 20) - this->height) + 10; // screen height - margin top and botton - object height
}
