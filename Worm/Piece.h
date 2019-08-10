#pragma once
#include "Square.h"
#include "Util.h"
#include "Constant.h"

/**
 * <EN>
 * Represents a piece of snake`s body
 *
 * <PT-Br>
 * Representa uma parte do corpo da cobra
*/
class Piece : public Square
{
	private:
		unsigned int direction = ALLEGRO_KEY_RIGHT;

		/**
		 * <EN>
		 * Move Piece to up
		 *
		 * <PT-Br>
		 * Movimenta Piece para cima
		*/
		void up();

		/**
		 * <EN>
		 * Move Piece to left
		 *
		 * <PT-Br>
		 * Movimenta Piece para esquerda
		*/
		void left();

		/**
		 * <EN>
		 * Move Piece to right
		 *
		 * <PT-Br>
		 * Movimenta Piece para direta
		*/
		void right();

		/**
		 * <EN>
		 * Move Piece to down
		 *
		 * <PT-Br>
		 * Movimenta Piece para baixo
		*/
		void down();

	public:

		/**
		 * <EN>
		 * Class constructor.
		 * @param[in] top_left_x
		 * @param[in] top_left_y
		 * @param[in] width
		 * @param[in] height
		 * @param[in] name
		 *
		 * <PT-Br>
		 * Construtor da classe.
		 * @param[in] top_left_x
		 * @param[in] top_left_y
		 * @param[in] width
		 * @param[in] height
		 * @param[in] name
		*/
		Piece(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const char * name);

		/**
		 * <EN>
		 * Class desconstructor
		 *
		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~Piece();

		/**
		 * <EN>
		 * Set the direction that piece will be moved
		 * @param[in] direction - Direction that piece will move
		 *
		 * <PT-Br>
		 * Define a direcao que Piece devera se mover
		 * @param[in] direction - Direcao que Piece devera se mover
		*/
		void set_direction(const unsigned int& direction);

		/**
		 * <EN>
		 * Movement Piece
		 *
		 * <PT-Br>
		 * Movimenta Piece
		*/
		void move();

		/**
		 * <EN>
		 * Get the direction that Piece was been moved
		 * @return direction - ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_UP or ALLEGRO_KEY_DOWN
		 *
		 * <PT-Br>
		 * Captura a direcao que Piece estava se movendo
		 * @return direcao  - ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_UP ou ALLEGRO_KEY_DOWN
		*/
		unsigned int get_direction();
};

