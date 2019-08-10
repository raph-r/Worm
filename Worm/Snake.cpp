#include "Snake.h"

Snake::Snake()
{
	for (int i = 1; i <= 5; i++)
	{
		this->DSPPWormBody.push_back(
			std::make_shared<Piece>(
				320 - (Constant::PIECE_WIDTH * i),
				240 - Constant::PIECE_HEIGHT,
				Constant::PIECE_WIDTH,
				Constant::PIECE_HEIGHT,
				""
			)
		);
	}
}

Snake::~Snake(){}

bool Snake::try_move()
{
	if (this->DPUiUiQueueOfDirections.size() > 0)
	{
		int qtd_to_remove = 0;
		for (auto &command : this->DPUiUiQueueOfDirections)
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
			this->DPUiUiQueueOfDirections.pop_front();
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

void Snake::add_size()
{
	this->DSPPWormBody.push_back(
		std::make_shared<Piece>(
			(*this->DSPPWormBody.back())
		)
	);
	
	switch (this->DSPPWormBody.back()->get_direction())
	{
	case ALLEGRO_KEY_UP:
		this->DSPPWormBody.back()->add_top_left_y(Constant::PIECE_HEIGHT);
		break;
	case ALLEGRO_KEY_DOWN:
		this->DSPPWormBody.back()->add_top_left_y(Constant::PIECE_HEIGHT * -1);
		break;
	case ALLEGRO_KEY_LEFT:
		this->DSPPWormBody.back()->add_top_left_x(Constant::PIECE_WIDTH);
		break;
	case ALLEGRO_KEY_RIGHT:
		this->DSPPWormBody.back()->add_top_left_x(Constant::PIECE_WIDTH * -1);
		break;
	default:
		break;
	}
}

void Snake::draw(ALLEGRO_COLOR * color)
{
	for (auto &part : this->DSPPWormBody)
	{
		al_draw_filled_rectangle(part->get_line_left(), part->get_line_top(), part->get_line_right(), part->get_line_botton(), *color);
	}
}

void Snake::add_direction_to_queue_of_directions(const unsigned int & command)
{
	if (this->DPUiUiQueueOfDirections.size() == 0)
	{
		this->DPUiUiQueueOfDirections.push_back(
			std::make_pair(0, command)
		);
	}
	else if (this->DPUiUiQueueOfDirections.back().second != command)
	{
		this->DPUiUiQueueOfDirections.push_back(
			std::make_pair(0, command)
		);
	}
}

bool Snake::is_collided_screen_boundaries(const Square const * screen_boundaries)
{
	auto first_part = this->DSPPWormBody.front();
	if (first_part->get_line_left() < screen_boundaries->get_line_left()
		|| first_part->get_line_right() > screen_boundaries->get_line_right()
		|| first_part->get_line_top() < screen_boundaries->get_line_top()
		|| first_part->get_line_botton() > screen_boundaries->get_line_botton())
	{
		return true;
	}
	return false;
}

bool Snake::is_overlapping_some_piece(const Square const * object)
{
	for (auto& piece_worm : this->DSPPWormBody)
	{
		if (piece_worm->is_overlapped(object))
		{
			return true;
		}
	}
	return false;
}

bool Snake::first_piece_is_overlapping(const Square const * object)
{
	return this->DSPPWormBody.front()->is_overlapped(object);
}

bool Snake::first_piece_is_overlapping_itself()
{
	Square piece((*this->DSPPWormBody.front()));

	switch (this->DSPPWormBody.front()->get_direction())
	{
	case ALLEGRO_KEY_UP:
		piece.add_top_left_y(Constant::PIECE_HEIGHT * -1);
		break;
	case ALLEGRO_KEY_DOWN:
		piece.add_top_left_y(Constant::PIECE_HEIGHT);
		break;
	case ALLEGRO_KEY_LEFT:
		piece.add_top_left_x(Constant::PIECE_WIDTH * -1);
		break;
	case ALLEGRO_KEY_RIGHT:
		piece.add_top_left_x(Constant::PIECE_WIDTH);
		break;
	default:
		break;
	}

	return this->is_overlapping_some_piece(&piece);
}