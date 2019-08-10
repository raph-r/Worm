#include "Food.h"

Food::Food() : Object(1, 1, Constant::POWERUP_WIDTH, Constant::POWERUP_HEIGHT, "Power-up")
{
	srand(time(NULL));
}

Food::~Food(){}

void Food::draw(ALLEGRO_COLOR * color)
{
	al_draw_filled_rectangle(this->collision_line_left(), this->collision_line_top(), this->collision_line_right(), this->collision_line_botton(), *color);
}

void Food::change_location()
{
	// new_top_left_x = (rand % (screen width - (margin left and right) - powerup width)) + margin left
	this->top_left_x = (rand() % (Constant::SCREEN_WIDTH - (Constant::MARGIN_SCREEN_BOUNDARIES * 2) - this->width)) + Constant::MARGIN_SCREEN_BOUNDARIES;

	// round tha value
	this->top_left_x -= (this->top_left_x % Constant::POWERUP_WIDTH);

	// new_top_left_y = (rand % (screen height - (margin top and botton) - powerup height - score height)) + margin top + score height
	this->top_left_y = (rand() % (Constant::SCREEN_HEIGHT - (Constant::MARGIN_SCREEN_BOUNDARIES * 2) - this->height - Constant::SCORE_HEIGHT)) + Constant::MARGIN_SCREEN_BOUNDARIES + Constant::SCORE_HEIGHT;

	// round tha value
	this->top_left_y -= (this->top_left_y % Constant::POWERUP_HEIGHT);
}