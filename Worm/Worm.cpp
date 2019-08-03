#include "Worm.h"



Worm::Worm(const int& width, const int& height)
{
	for (int i = 1; i <= 5; i++)
	{
		this->VUPOWormBody.push_back(
			std::make_unique<Object>(
				(640 / 2) - (width * 5 / 2),
				(480 / 2) - (height / 2),
				i * width,
				height,
				""
			)
		);
	}
}


Worm::~Worm()
{
}

void Worm::add_size()
{
	// TODO
}

void Worm::draw(ALLEGRO_COLOR * color)
{
	for (auto &part : this->VUPOWormBody)
	{
		al_draw_filled_rectangle(part->collision_line_left(), part->collision_line_top(), part->collision_line_right(), part->collision_line_botton(), *color);
	}
}
