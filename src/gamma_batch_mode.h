/** @file
 * Interfejs biblioteki obsługującej tryb wsadowy
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 7.05.2020
 */

#ifndef GAMMA_BATCH_H
#define GAMMA_BATCH_H

#include "gamma.h"
#include "input.h"

/** @brief Przeprowadza rozgrywkę w trybie wsadowym.
 * @param[in,out] game          – wskaźnik na strukturę przechowującą stan gry
 * @param[in,out] line_counter  – wskaźnik na zmienną, liczącą wiersze
 *                                na wejściu
 */
void init_batch_mode(gamma_t *game, int *line_counter);

#endif /* GAMMA_BATCH_H */