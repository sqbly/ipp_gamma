/** @file
 * Interfejs biblioteki służącej do wczytywania danych
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 7.05.2020
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "ansi_escape_utils.h"

#define IGNORE -2
#define ERROR -1

/** @brief Wczytuje pojedynczą linijke w trybie wsadowym i częściowo sprawdza
 * poprawność.
 * Wczytuje pojedynczą linijkę z wejścia i częściowo sprawdza
 * poprawność. Jeśli linijka składa się z małej litery z ustalonego zbioru
 * instrukcji oraz maksymalnie trzech, oddzielonych spacjami liczb nie
 * przekraczających UINT32_MAX to zapisuje w argumentach parametry komendy. Wpp
 * ustawia @p type na 'i' jeśli linijka ma być zignorowana lub na 'e' jeśli
 * stwierdzono błąd. Nie sprawdza czy czy odpowiednie typu komend wczytały
 * wystarczająco wiele liczb.
 * @param[in,out] type          – wskaźnik na zmienną, do której zostanie
 *                                zapisany typ komendy
 * @param[in,out] arg1          – wskaźnik na zmienną, do której zostanie
 *                                zapisana pierwsza liczba
 * @param[in,out] arg2          – wskaźnik na zmienną, do której zostanie
 *                                zapisana druga liczba
 * @param[in,out] arg3          – wskaźnik na zmienną, do której zostanie
 *                                zapisana trzecia liczba
 * @param[in,out] number_count  – wskaźnik na zmienną, do której zostanie
 *                                zapisana liczba wczytanych liczb
 * @return Wartość @p true jeśli we wczytanej linijce nie znajdował się znak
 * końca pliku, @p false w przeciwnym przypadku.
 */

bool read_command(char *type, uint64_t *arg1, uint64_t *arg2, uint64_t *arg3,
                  uint64_t *arg4, int *number_count);

char get_char_raw();

#endif /* INPUT_H */