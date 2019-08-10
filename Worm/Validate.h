#pragma once
#include <stdio.h>
#include <stdlib.h>

/**
 * <EN>
 * Namespace of validation methods
 * <PT-Br>
 * Namespace de metodos de validacao
*/
namespace Validate
{
	/**
	 * <EN>
	 * If the received value is false, print following message:
	 *  'object_name' wasn`t initialized.	
	 * Then, close the game
	 * @param[in] result_to_validate - Value to validate
	 * @param[in] object_name - Object name
	 *
	 * <PT-Br>
	 * Caso o valor recebido for false, imprime a mensagem:
	 *  'object_name' wasn`t initialized.
	 * Entao fecha o jogo
	 * @param[in] result_to_validate - valor para validar
	 * @param[in] object_name - Nome do objeto
	*/
	void object_was_initialized(const bool& result_to_validate, const char* object_name);
}
