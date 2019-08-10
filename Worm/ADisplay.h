#pragma once
#include "Validate.h"
#include "allegro5/allegro5.h"

/**
 * <EN>
 * Encapsulate the ALLEGRO_DISPLAY class
 * <PT-Br>
 * Encapsula a classe ALLEGRO_DISPLAY - TTF
*/
class ADisplay
{
	private:
		ALLEGRO_DISPLAY * display = nullptr; // ALEGRO_DISPLAY that instance represents

	public:
		/**
		 * <EN>
		 * Class constructor. Create a screen to game
		 * @param[in] width - Screen
		 * @param[in] height - Screen
		 *
		 * <PT-Br>
		 * Construtor da classe. Cria uma tela para o jogo
		 * @param[in] width - tela
		 * @param[in] height - tela
		*/
		ADisplay(const int& width, const int& height);

		/**
		 * <EN>
		 * Class desconstructor
		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~ADisplay();

		/**
		 * <EN>
		 * Get the font that instance represents
		 * @return Pointer to ALLEGRO_DISPLAY
		 *
		 * <PT-Br>
		 * Captura a fonte que a instancia representa
		 * @return ponteiro para ALLEGRO_DISPLAY
		*/
		ALLEGRO_DISPLAY * getDisplay() const;
};
