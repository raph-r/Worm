#include "ATimer.h"

ATimer::ATimer(const float& fps)
{
	this->timer = al_create_timer(fps);
	Validate::object_was_initialized(this->timer, "Timer");
}

ATimer::~ATimer()
{
	al_destroy_timer(this->timer);
}

ALLEGRO_TIMER * ATimer::getTimer() const
{
	return this->timer;
}

void ATimer::startTimer()
{
	al_start_timer(this->timer);
}
