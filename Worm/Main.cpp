#include "ATimer.h"
#include "ADisplay.h"
#include "AEventQueue.h"
#include "Validate.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include <memory>

#define KEY_SEEN 1
#define KEY_RELEASED 2
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argn, char** argv)
{
	bool continue_to_play = true;
	bool draw = false;
	bool has_winner = false;

	// Initialize the basics objects of Allegro
	Validate::object_was_initialized(al_init(), "Allegro");
	Validate::object_was_initialized(al_install_keyboard(), "Keyboard");
	Validate::object_was_initialized(al_init_primitives_addon(), "Primitives");

	// Initialize the object of Allegro that has encapsulation
	std::unique_ptr<ATimer> UPATimer = std::make_unique<ATimer>(1.0 / 60);
	std::unique_ptr<ADisplay> UPADisplay = std::make_unique<ADisplay>(SCREEN_WIDTH, SCREEN_HEIGHT);
	std::unique_ptr<AEventQueue> UPAEventQueue = std::make_unique<AEventQueue>();
	ALLEGRO_FONT * font = al_create_builtin_font();
	Validate::object_was_initialized(font, "Font");

	// add source to event queue
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_keyboard_event_source());
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_timer_event_source(UPATimer->getTimer()));
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_display_event_source(UPADisplay->getDisplay()));

	// color palettes
	ALLEGRO_COLOR ACBlack = al_map_rgba_f(0, 0, 0, 0);
	ALLEGRO_COLOR ACWhite = al_map_rgba_f(1, 1, 1, 1);
	
	//captures the current event
	ALLEGRO_EVENT event;
	
	//user input
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));

	bool starter_menu = true;

	UPATimer->startTimer();
	while (continue_to_play)
	{
		al_wait_for_event(UPAEventQueue->getEventQueue(), &event);

		switch (event.type)
		{
			case ALLEGRO_EVENT_TIMER:
				//Exit game
				if (key[ALLEGRO_KEY_ESCAPE])
				{
					continue_to_play = false;
				}
				// Reset array of keys
				for (unsigned int i = 0; i < ALLEGRO_KEY_MAX; i++)
				{
					key[i] &= KEY_SEEN;
				}
				draw = true;
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
				break;
			case ALLEGRO_EVENT_KEY_UP:
				key[event.keyboard.keycode] &= KEY_RELEASED;
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				continue_to_play = false;
				break;
			default:
				break;
		}

		if (draw && al_is_event_queue_empty(UPAEventQueue->getEventQueue()))
		{
			draw = false;
			al_clear_to_color(ACBlack);
			//draw
			al_flip_display();
		}
	}
	al_destroy_font(font);
	return 0;
}