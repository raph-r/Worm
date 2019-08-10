#pragma once
#include "allegro5/allegro.h"

/**
 * <EN>
 * Namespace of methods to general use
 * <PT-Br>
 * Namespace de metodos para uso geral
*/
namespace Util
{
	/**
	 * <EN>
	 * Use only with: ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN
	 * Verify if the received direction is horizontal(ALLEGRO_KEY_LEFT ou ALLEGRO_KEY_RIGHT)
	 * @param[in] direction - ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_UP or ALLEGRO_KEY_DOWN 
	 * @return - True if it is equal, otherwise false
	 *
	 * <PT-Br>
	 * Utilizar apenas com: ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN 
	 * Verifica se a direcao recebida e horizontal(ALLEGRO_KEY_LEFT ou ALLEGRO_KEY_RIGHT)
	 * @param[in] direction - ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_UP ou ALLEGRO_KEY_DOWN 
	 * @return - True se for igual, caso contrario false
	*/
	bool is_horizontal(const unsigned int & direction);
}
