#include "Worm.h"

Worm::Worm(const int& width, const int& height)
{
	this->piece_width = std::move(width);
	this->piece_height = std::move(height);
	for (int i = 1; i <= 5; i++)
	{
		this->DSPPWormBody.push_back(
			std::make_shared<Piece>(
				320 - (this->piece_width * i),
				240 - this->piece_height,
				this->piece_width,
				this->piece_height,
				""
			)
		);
	}
}

Worm::~Worm(){}

bool Worm::try_move()
{
	if (this->move_command.size() > 0)
	{
		int qtd_to_remove = 0;
		for (auto &command : this->move_command)
		{
			if (command.first < this->DSPPWormBody.size())
			{
				this->DSPPWormBody[command.first]->set_direction(command.second);
				command.first++;
			}
			else
			{
				qtd_to_remove++;
			}
		}

		for (int i = 0; i < qtd_to_remove; i++)
		{
			this->move_command.pop_front();
		}
	}

	if (this->first_piece_is_overlapping_itself())
	{
		return false;
	}

	for (auto &part : this->DSPPWormBody)
	{
		part->move();
	}

	return true;
}

void Worm::add_size()
{
	this->DSPPWormBody.push_back(
		std::make_shared<Piece>(
			(*this->DSPPWormBody.back())
		)
	);
	
	switch (this->DSPPWormBody.back()->get_direction())
	{
	case ALLEGRO_KEY_UP:
		this->DSPPWormBody.back()->add_top_left_y(this->piece_height);
		break;
	case ALLEGRO_KEY_DOWN:
		this->DSPPWormBody.back()->add_top_left_y(this->piece_height * -1);
		break;
	case ALLEGRO_KEY_LEFT:
		this->DSPPWormBody.back()->add_top_left_x(this->piece_width);
		break;
	case ALLEGRO_KEY_RIGHT:
		this->DSPPWormBody.back()->add_top_left_x(this->piece_width * -1);
		break;
	default:
		break;
	}
}

void Worm::draw(ALLEGRO_COLOR * color)
{
	for (auto &part : this->DSPPWormBody)
	{
		al_draw_filled_rectangle(part->collision_line_left(), part->collision_line_top(), part->collision_line_right(), part->collision_line_botton(), *color);
	}
}

void Worm::add_move_command(const unsigned int & command)
{
	if (this->move_command.size() == 0)
	{
		this->move_command.push_back(
			std::make_pair(0, command)
		);
	}
	else if (this->move_command.back().second != command)
	{
		this->move_command.push_back(
			std::make_pair(0, command)
		);
	}
}

bool Worm::is_collided_screen_boundaries(const Object const * screen_boundaries)
{
	auto first_part = this->DSPPWormBody.front();
	if (first_part->collision_line_left() < screen_boundaries->collision_line_left()
		|| first_part->collision_line_right() > screen_boundaries->collision_line_right()
		|| first_part->collision_line_top() < screen_boundaries->collision_line_top()
		|| first_part->collision_line_botton() > screen_boundaries->collision_line_botton())
	{
		return true;
	}
	return false;
}

bool Worm::first_piece_is_overlapping(const Object const * object)
{
	return this->DSPPWormBody.front()->is_overlapped(object);
}

bool Worm::first_piece_is_overlapping_itself()
{
	Object piece((*this->DSPPWormBody.front()));

	switch (this->DSPPWormBody.front()->get_direction())
	{
	case ALLEGRO_KEY_UP:
		piece.add_top_left_y(this->piece_height * -1);
		break;
	case ALLEGRO_KEY_DOWN:
		piece.add_top_left_y(this->piece_height);
		break;
	case ALLEGRO_KEY_LEFT:
		piece.add_top_left_x(this->piece_width * -1);
		break;
	case ALLEGRO_KEY_RIGHT:
		piece.add_top_left_x(this->piece_width);
		break;
	default:
		break;
	}

	for (auto& piece_worm : this->DSPPWormBody)
	{
		if (piece_worm->is_overlapped(dynamic_cast<Object*>(&piece)))
		{
			return true;
		}
	}
	return false;
}