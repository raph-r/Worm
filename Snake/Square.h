#pragma once
#include <memory>

/**
 * <EN>
 * Abstract object that represents a square
 *
 * <PT-Br>
 * Objeto abstrato que representar um quadrado
*/
class Square
{
	protected:
		int top_left_x = 0;
		int top_left_y = 0;
		int width = 0;
		int height = 0;
		const char * name;

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
		Square(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const char * name);

		/**
		 * <EN>
		 * Class desconstructor

		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~Square();

		/**
		 * <EN>
		 * Get the position of top line of square
		 * @return position of top line of square
		 *
		 * <PT-Br>
		 * Captura a posicao da linha superior do quadrado
		 * @return posicao da linha superior do quadrado
		*/
		int get_line_top() const;

		/**
		 * <EN>
		 * Get the position of botton line of square
		 * @return position of botton line of square
		 *
		 * <PT-Br>
		 * Captura a posicao da linha inferior do quadrado
		 * @return posicao da linha inferior do quadrado
		*/
		int get_line_botton() const;

		/**
		 * <EN>
		 * Get the position of left line of square
		 * @return position of left line of square
		 *
		 * <PT-Br>
		 * Captura a posicao da linha esquerda do quadrado
		 * @return posicao da linha esquerda do quadrado
		*/
		int get_line_left() const;

		/**
		 * <EN>
		 * Get the position of right line of square
		 * @return position of right line of square
		 *
		 * <PT-Br>
		 * Captura a posicao da linha direita do quadrado
		 * @return posicao da linha direita do quadrado
		*/
		int get_line_right() const;

		/**
		 * <EN>
		 * Verify if the current Square its been overlapped by 'other_square'
		 * @param[in] other_square - Square that will be used to compare
		 * @return True if the Squares are overlapped. Otherwise false.
		 *
		 * <PT-Br>
		 * Verifica se este Square esta sendo sobreposto por 'other_square'
		 * @param[in] other_square - Square que sera utilizado para comparacao
		 * @return True se os objetos estao sobrepostos. Caso contrario, false.
		*/
		bool is_overlapped(const Square const * other_square);

		/**
		 * <EN>
		 * Get the name of square
		 * @return name of square
		 *
		 * <PT-Br>
		 * Captura o nome do quadrado
		 * @return nome do quadrado
		*/
		const char * get_name();

		/**
		 * <EN>
		 * Add value to Square::top_left_x
		 * @param value - quantity to add
		 *
		 * <PT-Br>
		 * Adiciona value a Square::top_left_x
		 * @param[in] value - quantidade para adicionar
		*/
		void add_top_left_x(const int& value);

		/**
		 * <EN>
		 * Add value to Square::top_left_y
		 * @param value - quantity to add
		 *
		 * <PT-Br>
		 * Adiciona value a Square::top_left_y
		 * @param[in] value - quantidade para adicionar
		*/
		void add_top_left_y(const int& value);
};
