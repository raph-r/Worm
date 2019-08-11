#pragma once
#include "Square.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include <cstdlib>
#include <time.h>
#include "Constant.h"

/**
 * <EN>
 * Food that snake need to eat
 * <PT-Br>
 * Comida que a cobra devera comer para crescer
*/
class Food : public Square
{
	public:
		/**
			* <EN>
			* Class constructor
			*
			* <PT-Br>
			* Construtor da classe
		*/
		Food();

		/**
		 * <EN>
		 * Class desconstructor
		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~Food();

		/**
		 * <EN>
		 * Draw itself on screen
		 * <PT-Br>
		 * Desenha a si mesmo na tela
		*/
		void draw(ALLEGRO_COLOR * color);

		/**
		 * <EN>
		 * Change the location of itself to a new random location
		 * <PT-Br>
		 * Altera a sua propria localizacao para uma nova localizacao aletoria
		*/
		void change_location();
};