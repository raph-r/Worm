#include "ATimer.h"
#include "ADisplay.h"
#include "AEventQueue.h"
#include "Validate.h"
#include "Object.h"
#include "allegro5/allegro_font.h"
#include "Powerup.h"
#include "Worm.h"
#include <memory>

#define KEY_SEEN 1
#define KEY_RELEASED 2
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void draw_starter_menu(const ALLEGRO_COLOR& ACWhite, const ALLEGRO_FONT * font)
{
	char msg[] = "Press Enter to Play";
	al_draw_textf(font, ACWhite, (SCREEN_WIDTH / 2) - (al_get_text_width(font, msg) / 2), (SCREEN_HEIGHT / 2) - al_get_font_line_height(font) / 2, 0, msg);
}

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
	std::unique_ptr<ATimer> UPATimer = std::make_unique<ATimer>(1.0 / 14);
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

	// Screen Bounderies
	Object OScreenBoundaries(10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, "Screen Boundaries");

	// Power up
	Powerup powerup(50, 50, 10, 10, "Power up");
	
	// Worm
	Worm worm(10, 10);

	//captures the current event
	ALLEGRO_EVENT event;
	
	//user input
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));

	unsigned int scene = 1;

	UPATimer->startTimer();
	while (continue_to_play)
	{
		al_wait_for_event(UPAEventQueue->getEventQueue(), &event);

		switch (event.type)
		{
			case ALLEGRO_EVENT_TIMER:
				// Starter screen
				if (scene == 1 && key[ALLEGRO_KEY_ENTER])
				{
					scene++;
				}
				else if (scene == 2)
				{
					//Test the key pressed
					if (key[ALLEGRO_KEY_UP])
					{
						worm.add_move_command(ALLEGRO_KEY_UP);
					}
					else if (key[ALLEGRO_KEY_DOWN])
					{
						worm.add_move_command(ALLEGRO_KEY_DOWN);
					}
					else if (key[ALLEGRO_KEY_LEFT])
					{
						worm.add_move_command(ALLEGRO_KEY_LEFT);
					}
					else if (key[ALLEGRO_KEY_RIGHT])
					{
						worm.add_move_command(ALLEGRO_KEY_RIGHT);
					}

					// If Worm overlap powerup, add worm size
					if (worm.first_piece_is_overlapping(&powerup))
					{
						powerup.change_location();
						worm.add_size();
					}

					// Exit game
					if (key[ALLEGRO_KEY_ESCAPE] || !worm.try_move() || worm.is_collided_screen_boundaries(&OScreenBoundaries))
					{
						continue_to_play = false;
					}
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

			if(scene == 1)
			{
				// draw starter screen
				draw_starter_menu(ACWhite, font);
			}
			else
			{
				// draw Screen boundaries
				al_draw_rectangle(OScreenBoundaries.collision_line_left(), OScreenBoundaries.collision_line_top(), OScreenBoundaries.collision_line_right(), OScreenBoundaries.collision_line_botton(), ACWhite, 1);
				worm.draw(&ACWhite);
				powerup.draw(&ACWhite);
			}
			al_flip_display();
		}
	}
	al_destroy_font(font);
	return 0;
}