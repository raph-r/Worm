#include "ATimer.h"
#include "ADisplay.h"
#include "AEventQueue.h"
#include "ATTFFont.h"
#include "ASample.h"
#include "Square.h"
#include "Food.h"
#include "Snake.h"
#include <memory>

/**
 * <EN>
 * Draw the initial scene of game
 * @param[in] color - Color that will be used to draw
 * @param[in] font - ATTFFont that will be used to draw
 *
 * <PT-Br>
 * Desenha a cena inicial do jogo
 * @param[in] color - Cor que devera ser utilizada para desenhar
 * @param[in] font - ATTFFont que sera utilizada para desenhar
*/
void draw_initial_scene(const ALLEGRO_COLOR& color, const std::shared_ptr<const ATTFFont>& font)
{
	al_draw_textf(
		font->getFont(),
		color,
		Constant::HALF_SCREEN_WIDTH,
		Constant::HALF_SCREEN_HEIGHT - (al_get_font_line_height(font->getFont()) / 2),
		ALLEGRO_ALIGN_CENTER,
		Constant::MSG_TO_PLAY
	);
}

/**
 * <EN>
 * Draw the initial scene of game
 * @param[in] color - Color that will be used to draw
 * @param[in] font - ATTFFont that will be used to draw
 * @param[in] score - Player`s score
 *
 * <PT-Br>
 * Desenha a cena inicial do jogo
 * @param[in] color - Cor que devera ser utilizada para desenhar
 * @param[in] font - ATTFFont que sera utilizada para desenhar
 * @param[in] score - Pontuacao do jogador
*/
void draw_score(const ALLEGRO_COLOR& color, const std::shared_ptr<const ATTFFont>& font, const unsigned int * score)
{
	al_draw_textf(
		font->getFont(),
		color,
		Constant::HALF_SCREEN_WIDTH,
		(Constant::SCORE_HEIGHT / 2) - (al_get_font_line_height(font->getFont()) / 2),
		ALLEGRO_ALIGN_CENTER,
		"%u",
		*score
	);
}

/**
 * <EN>
 * Draw the end scene of game
 * @param[in] color - Color that will be used to draw
 * @param[in] font - ATTFFont that will be used to draw
 * @param[in] score - Player`s score
 *
 * <PT-Br>
 * Desenha a cena final do jogo
 * @param[in] color - Cor que devera ser utilizada para desenhar
 * @param[in] font - ATTFFont que sera utilizada para desenhar
 * @param[in] score - Pontuacao do jogador
*/
void draw_endgame(const ALLEGRO_COLOR& color, const std::shared_ptr<const ATTFFont>& font, const unsigned int * score)
{
	al_draw_textf(font->getFont(), color, Constant::HALF_SCREEN_WIDTH, Constant::HALF_SCREEN_HEIGHT - al_get_font_line_height(font->getFont()), ALLEGRO_ALIGN_CENTER, "Your score: %u", *score);
	al_draw_textf(font->getFont(), color, Constant::HALF_SCREEN_WIDTH, Constant::HALF_SCREEN_HEIGHT, ALLEGRO_ALIGN_CENTER, "Press Enter to play again");
}

int main(int argn, char** argv)
{
	bool continue_to_play = true;
	bool draw = false;

	// Initialize the basics objects of Allegro
	Validate::object_was_initialized(al_init(), "Allegro");
	Validate::object_was_initialized(al_install_keyboard(), "Keyboard");
	Validate::object_was_initialized(al_init_primitives_addon(), "Primitives Addon");
	Validate::object_was_initialized(al_init_font_addon(), "Font Addon");
	Validate::object_was_initialized(al_init_ttf_addon(), "Font TTF Addon");
	Validate::object_was_initialized(al_install_audio(), "Audio");
	Validate::object_was_initialized(al_init_acodec_addon(), "Audio Codec");

	// Initialize the object of Allegro that had been encapsulated
	std::unique_ptr<ATimer> UPATimer = std::make_unique<ATimer>(1.0 / 14);
	std::unique_ptr<ADisplay> UPADisplay = std::make_unique<ADisplay>();
	std::unique_ptr<AEventQueue> UPAEventQueue = std::make_unique<AEventQueue>();
	std::shared_ptr<ATTFFont> SPFont_24 = std::make_shared<ATTFFont>("Oswald-Medium.ttf", 24);

	al_reserve_samples(2);
	std::unique_ptr<ASample> eat_sound = std::make_unique<ASample>("eat.wav", ALLEGRO_PLAYMODE_ONCE);

	// add source to event queue
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_keyboard_event_source());
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_timer_event_source(UPATimer->getTimer()));
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_display_event_source(UPADisplay->getDisplay()));

	// color palettes
	ALLEGRO_COLOR ACBlack = al_map_rgba_f(0, 0, 0, 0);
	ALLEGRO_COLOR ACWhite = al_map_rgba_f(1, 1, 1, 1);

	// Screen Bounderies
	Square OScreenBoundaries(
		Constant::MARGIN_SCREEN_BOUNDARIES,
		Constant::SCORE_HEIGHT,
		Constant::SCREEN_WIDTH - (Constant::MARGIN_SCREEN_BOUNDARIES * 2),
		Constant::SCREEN_HEIGHT - Constant::SCORE_HEIGHT - Constant::MARGIN_SCREEN_BOUNDARIES,
		"Screen Boundaries"
	);

	Food food;
	std::unique_ptr<Snake> UPSnake;

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
					UPSnake = std::make_unique<Snake>();
					food.change_location();
					scene = 2;
					score = 0;
				}
				else if (scene == 2)
				{
					//Test the key pressed
					if (key[ALLEGRO_KEY_UP] || key[ALLEGRO_KEY_DOWN] || key[ALLEGRO_KEY_LEFT] || key[ALLEGRO_KEY_RIGHT])
					{
						UPSnake->add_direction_to_queue_of_directions(Util::identify_pressed_key(key));
					}

					// If Snake overlap food, add worm size
					if (UPSnake->first_piece_is_overlapping(&food))
					{
						eat_sound->play_sample();
						while(UPSnake->is_overlapping_some_piece(&food)) food.change_location();
						UPSnake->add_size();
						score += 20;
					}

					// Move to End Game Scene
					if (!UPSnake->try_move() || UPSnake->is_collided_screen_boundaries(&OScreenBoundaries))
					{
						scene++;
					}
				}
				
				// exit game
				if (key[ALLEGRO_KEY_ESCAPE])
				{
					continue_to_play = false;
				}

				// Reset array of keys
				Util::reset_array_of_keys(key);

				draw = true;
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				key[event.keyboard.keycode] = Constant::KEY_SEEN | Constant::KEY_RELEASED;
				break;
			case ALLEGRO_EVENT_KEY_UP:
				key[event.keyboard.keycode] &= Constant::KEY_RELEASED;
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
				draw_initial_scene(ACWhite, SPFont_24);
			}
			else if(scene == 2)
			{
				// draw Screen boundaries
				al_draw_rectangle(OScreenBoundaries.get_line_left(), OScreenBoundaries.get_line_top(), OScreenBoundaries.get_line_right(), OScreenBoundaries.get_line_botton(), ACWhite, 1);
				UPSnake->draw(&ACWhite);
				food.draw(&ACWhite);
				draw_score(ACWhite, SPFont_24, &score);
			}
			else
			{
				// draw starter screen
				draw_endgame(ACWhite, SPFont_24, &score);
			}
			al_flip_display();
		}
	}
	return 0;
}