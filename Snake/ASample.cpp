#include "ASample.h"

ASample::ASample(const char * path, const ALLEGRO_PLAYMODE playmode)
{
	this->sample = al_load_sample(path);
	Validate::object_was_initialized(this->sample, "Sample");
	this->playmode = std::move(playmode);
}

void ASample::play_sample() const
{
	al_destroy_sample(this->sample);
}

ASample::~ASample()
{
	al_play_sample(this->sample, 1.0, 0, 1.0, this->playmode, 0);
}
