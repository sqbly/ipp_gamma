/** @file
 * Interfejs biblioteki obsługującej tryb interaktywny
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 7.05.2020
 */

#ifndef GAMMA_INTERACTIVE_H
#define GAMMA_INTERACTIVE_H

#include "ansi_escape_utils.h"
#include "gamma.h"
#include "input.h"

/** @brief Przeprowadza rozgrywkę w trybie interaktywnym.
 * @param[in,out] game          – wskaźnik na strukturę przechowującą stan gry
 * @param[in,out] line_counter  – wskaźnik na zmienną, liczącą wiersze
 *                                na wejściu
 */
void init_interactive_mode(gamma_t *game);

#endif /* GAMMA_INTERACTIVE_H */