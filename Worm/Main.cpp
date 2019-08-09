#include "ATimer.h"
#include "ADisplay.h"
#include "AEventQueue.h"
#include "Validate.h"
#include "Object.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "Powerup.h"
#include "Worm.h"
#include <memory>

#define KEY_SEEN 1
#define KEY_RELEASED 2
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void draw_starter_menu(const ALLEGRO_COLOR& color, const ALLEGRO_FONT * font)
{
	char msg[] = "Press Enter to Play";
	al_draw_textf(font, color, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - (al_get_font_line_height(font) / 2), ALLEGRO_ALIGN_CENTER, msg);
}

void draw_score(const ALLEGRO_COLOR& color, const ALLEGRO_FONT * font, const unsigned int * score)
{
	
	al_draw_textf(font, color, (SCREEN_WIDTH / 2), 25 - (al_get_font_line_height(font) / 2), ALLEGRO_ALIGN_CENTER, "%u", *score);
}

void draw_endgame(const ALLEGRO_COLOR& color, const ALLEGRO_FONT * font, const unsigned int * score)
{
	al_draw_textf(font, color, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - al_get_font_line_height(font), ALLEGRO_ALIGN_CENTER, "Your score: %u", *score);
	al_draw_textf(font, color, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), ALLEGRO_ALIGN_CENTER, "Press Enter to play again");
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
	Validate::object_was_initialized(al_init_font_addon(), "Font");
	Validate::object_was_initialized(al_init_ttf_addon(), "Font TTF");

	// Initialize the object of Allegro that has encapsulation
	std::unique_ptr<ATimer> UPATimer = std::make_unique<ATimer>(1.0 / 14);
	std::unique_ptr<ADisplay> UPADisplay = std::make_unique<ADisplay>(SCREEN_WIDTH, SCREEN_HEIGHT);
	std::unique_ptr<AEventQueue> UPAEventQueue = std::make_unique<AEventQueue>();
	ALLEGRO_FONT * font = al_load_ttf_font("Oswald-Medium.ttf", 24, ALLEGRO_TTF_NO_KERNING);
	Validate::object_was_initialized(font, "Font");

	// add source to event queue
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_keyboard_event_source());
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_timer_event_source(UPATimer->getTimer()));
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_display_event_source(UPADisplay->getDisplay()));

	// color palettes
	ALLEGRO_COLOR ACBlack = al_map_rgba_f(0, 0, 0, 0);
	ALLEGRO_COLOR ACWhite = al_map_rgba_f(1, 1, 1, 1);

	// Screen Bounderies
	Object OScreenBoundaries(10, 50, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 60, "Screen Boundaries");

	// Power up
	Powerup powerup(50, 50, 10, 10, "Power up");
	
	// Worm
	std::unique_ptr<Worm> UPWorm;

	//captures the current event
	ALLEGRO_EVENT event;
	
	//user input
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));

	//player score
	unsigned int score = 0;

	//current scene of game
	unsigned int scene = 1;

	UPATimer->startTimer();
	while (continue_to_play)
	{
		al_wait_for_event(UPAEventQueue->getEventQueue(), &event);

		switch (event.type)
		{
			case ALLEGRO_EVENT_TIMER:
				// Starter Scene and End Game Scene will return to game play, if player press Enter
				if ((scene == 1 || scene == 3) && key[ALLEGRO_KEY_ENTER])
				{
					UPWorm = std::make_unique<Worm>(10, 10);
					powerup.change_location();
					scene = 2;
					score = 0;
				}
				else if (scene == 2)
				{
					//Test the key pressed
					if (key[ALLEGRO_KEY_UP])
					{
						UPWorm->add_move_command(ALLEGRO_KEY_UP);
					}
					else if (key[ALLEGRO_KEY_DOWN])
					{
						UPWorm->add_move_command(ALLEGRO_KEY_DOWN);
					}
					else if (key[ALLEGRO_KEY_LEFT])
					{
						UPWorm->add_move_command(ALLEGRO_KEY_LEFT);
					}
					else if (key[ALLEGRO_KEY_RIGHT])
					{
						UPWorm->add_move_command(ALLEGRO_KEY_RIGHT);
					}

					// If Worm overlap powerup, add worm size
					if (UPWorm->first_piece_is_overlapping(&powerup))
					{
						while(UPWorm->is_overlapping_some_piece(&powerup)) powerup.change_location();
						UPWorm->add_size();
						score += 20;
					}

					// Move to End Game Scene
					if (!UPWorm->try_move() || UPWorm->is_collided_screen_boundaries(&OScreenBoundaries))
					{
						scene++;
					}
				}
				else if (key[ALLEGRO_KEY_ESCAPE])
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

			if(scene == 1)
			{
				// draw starter screen
				draw_starter_menu(ACWhite, font);
			}
			else if(scene == 2)
			{
				// draw Screen boundaries
				al_draw_rectangle(OScreenBoundaries.collision_line_left(), OScreenBoundaries.collision_line_top(), OScreenBoundaries.collision_line_right(), OScreenBoundaries.collision_line_botton(), ACWhite, 1);
				UPWorm->draw(&ACWhite);
				powerup.draw(&ACWhite);
				draw_score(ACWhite, font, &score);
			}
			else
			{
				// draw starter screen
				draw_endgame(ACWhite, font, &score);
			}
			al_flip_display();
		}
	}
	//al_destroy_font(font);
	return 0;
}