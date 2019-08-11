#pragma once
#include <deque>
#include <memory>
#include "Piece.h"
#include "allegro5/allegro_primitives.h"

/**
 * <EN>
 * Represents the Snake
 *
 * <PT-Br>
 * Representa a Snake
*/
class Snake
{
	private:
		std::deque<std::shared_ptr<Piece>> DSPPWormBody;
		std::deque<std::pair<unsigned int, unsigned int>> DPUiUiQueueOfDirections;
	
	public:
		/**
		 * <EN>
		 * Class constructor
		 *
		 * <PT-Br>
		 * Construtor da classe
		*/
		Snake();

		/**
		 * <EN>
		 * Class desconstructor
		 *
		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~Snake();

		/**
		 * <EN>
		 * Try to move all Pieces in Snake::DSPPWormBody
		 * @return True if success. Otherwise False
		 *
		 * <PT-Br>
		 * Tentar movimentar todos os Piece de Snake::DSPPWormBody
		 * @return True caso tenha tido sucesso. Caso contrario false
		*/
		bool try_move();

		/**
		 * <EN>
		 * Add a Piece to Snake::DSPPWormBody
		 *
		 * <PT-Br>
		 * Adiciona um Piece ao Snake::DSPPWormBody
		*/
		void add_size();

		/**
		 * <EN>
		 * Draw Snake
		 * @param[in] color - Color that will be used to draw
		 *
		 * <PT-Br>
		 * Desenha a Snake
		 * @param[in] color - Cor que devera ser utilizada para desenhar
		*/
		void draw(ALLEGRO_COLOR * color);

		/**
		 * <EN>
		 * Add a new direction to Snake::DPUiUiQueueOfDirections
		 * @param[in] new_direction
		 *
		 * <PT-Br>
		 * Adiciona uma nova direcao a Snake::DPUiUiQueueOfDirections
		 * @param[in] new_direction
		*/
		void add_direction_to_queue_of_directions(const unsigned int& new_direction);

		/**
		 * <EN>
		 * Verify if the first Piece will overlap another Piece of Snake
		 * @return True if first Piece will overlap another Piece of Snake. Otherwise, False
		 *
		 * <PT-Br>
		 * Verifica se o primeiro Piece ira sobrepor outro Piece de Snake
		 * @return True se o primeiro Piece for sobrepor algum outro Piece de Snake. Caso contrario, False
		*/
		bool first_piece_is_overlapping_itself();

		/**
		 * <EN>
		 * Verify if the first Piece will overlap 'screen_boudanries'
		 * @param[in] screen_boudanries
		 * @return True if first Piece will overlap 'screen_boundaries'. Otherwise, False
		 *
		 * <PT-Br>
		 * Verifica se o primeiro Piece ira sobrepor 'screen_boundaries'
		 * @param[in] screen_boudanries
		 * @return True se o primeiro Piece for sobrepor 'screen_boundaries'. Caso contrario, False
		*/
		bool is_collided_screen_boundaries(const Square const * screen_boundaries);

		/**
		 * <EN>
		 * Verify if 'other_square' is overlapping some Piece of Snake::DSPPWormBody
		 * @param[in] other_square
		 * @return True if 'other_square' if overlapping some Piece of Snake::DSPPWormBody'. Otherwise, False
		 *
		 * <PT-Br>
		 * Verifica se 'other_square' esta sobrepondo algum Piece de Snake::DSPPWormBody
		 * @param[in] screen_boudanries
		 * @return True if 'other_square' esta sobrepondo algum Piece de Snake::DSPPWormBody. Caso contrario, False
		*/
		bool is_overlapping_some_piece(const Square const * other_square);

		/**
		 * <EN>
		 * Verify if the first Piece will overlap 'other_square'
		 * @param[in] other_square
		 * @return True if first Piece will overlap 'other_square'. Otherwise, False
		 *
		 * <PT-Br>
		 * Verifica se o primeiro Piece ira sobrepor 'other_square'
		 * @param[in] other_square
		 * @return True se o primeiro Piece for sobrepor 'other_square'. Caso contrario, False
		*/
		bool first_piece_is_overlapping(const Square const * other_square);
};

