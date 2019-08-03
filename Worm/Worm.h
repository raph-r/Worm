#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "allegro5/allegro_primitives.h"

class Worm
{
private:
	std::vector<std::unique_ptr<Object>> VUPOWormBody;
	bool is_move_horizontal = true;
public:
	Worm(const int& width, const int& height);
	~Worm();

	void add_size();
	void draw(ALLEGRO_COLOR * color);
};

