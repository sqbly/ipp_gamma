/** @file
 * Interfejs struktury listy jednokierunkowej.
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 14.04.2020
 */

#ifndef LIST_H
#define LIST_H

#include <errno.h>

#include "util.h"

/**
 * Struktura przechowująca jednokierunkową listę punktów o dwóch współrzędnych.
 */
typedef struct list list_t;

/** @brief Tworzy strukturę przechowującą listę.
 * Alokuje pamięć na nową strukturę listy.
 * Początkowo lista jest pusta.
 * W przypadku niemożności zaalokowania pamięci kończy działanie programu z
 * kodem ENOMEM.
 *
 * @return Wskaźnik na utworzoną strukturę.
 */
list_t *list_init();

/** @brief Usuwa strukturę przechowującą listę.
 * Usuwa z pamięci strukturę wskazywaną przez @p l.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 *
 * @param[in] l       – wskaźnik na usuwaną strukturę.
 */
void list_delete(list_t *l);

/** @brief Sprawdza pustość listy.
 * Sprawdza czy struktura wskazywana przez @p l jest pustą listą.
 *
 * @param[in] l       – wskaźnik na sprawdzaną strukturę.
 *
 * @return Wartość @p true, jeśli wskazywana lista jest pusta, a @p false, jeśli
 * lista nie jest pusta, lub parametr @p l jest niepoprawny.
 */
bool list_empty(list_t *l);

/** @brief Dodaje element na koniec listy.
 * Dodaje element o wartości @p a na koniec listy wskazywanej przez @p l.
 * Nic nie robi jeśli wskaźnik ten ma wartość NULL.
 *
 * @param[in,out] l       – wskaźnik na strukturę listy,
 * @param[in] a       – wartość dodawanego elementu.
 */
void list_add(list_t *l, point_t a);

/** @brief Zwraca i usuwa element z początku listy.
 *
 * @param[in,out] l       – wskaźnik na strukturę listy.
 *
 * @return Wartość pierwszego elementu listy jeśli nie jest ona pusta, punkt
 * (0,0) jeśli lista jest pusta, lub parametr @p l jest niepoprawny.
 */
point_t list_pop(list_t *l);

#endif