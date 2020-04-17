/** @file
 * Moduł zawierający funkcje pomocnicze.
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 14.04.2020
 */

#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/** Pomocniczy skrót na uint_32_t
 */
typedef uint32_t ui32;
/** Pomocniczy skrót na uint_64_t
 */
typedef uint64_t ui64;

/**
 * Struktura punktu o dwóch współrzędnych całkowitych nieujemnych.
 */
typedef struct point {
    uint32_t x;  ///< współrzędna na osi odciętych,
    uint32_t y;  ///< współrzędna na osi rzędnych.
} point_t;

/** @brief Tworzy punkt o podanych współrzędnych.
 * Tworzy punkt o współrzędnych ( @p x, @p y ) .
 *
 * @param[in] x       – współrzędna na osi odciętych,
 * @param[in] y       – współrzędna na osi rzędnych.
 *
 * @return Punkt o wspólrzędnych ( @p x, @p y ).
 */
point_t make_point(uint32_t x, uint32_t y);

/** @brief Dodaje współrzędne dwóch punktów.
 *
 * @param[in] a       – pierwszy czynnik,
 * @param[in] b       – drugi czynnik.
 *
 * @return Punkt o współrzędnych będących sumami współrzędnych punktów @p a i
 * @p b .
 */
point_t point_add(point_t a, point_t b);

/** @brief Podaje wartość o jaką trzeba zwiększyć współrzędne punktu żeby się
 * poruszyć w danym kierunku.
 * Podaje wartość o jaką trzeba zwiększyć współrzędne punktu żeby się
 * poruszyć o jedno pole w kierunku opisanym przez liczbę całkowitą z przedziału
 * [0,3].
 * 0 - w górę,
 * 1 - w dół,
 * 2 - w prawo,
 * 3 - w lewo.
 *
 * @param[in] i       – numer kierunku.
 *
 * @return Wektor zmiany położenia punktu po przejściu w podanym kierunku lub
 * wektor zerowy jeśli argument jest niepoprawny.
 */
point_t compass_rose(int i);

/** @brief Sprawdza równość dwóch punktów.
 * Sprawdza czy punkty @p a i @p b mają takie same współrzędne.
 *
 * @param[in] a       – pierwszy punkt,
 * @param[in] b       – drugi punkt.
 *
 * @return @p true jeśli punkty są takie same lub @p false w przeciwnym
 * przypadku.
 */
bool point_equal(point_t a, point_t b);

/** @brief Usuwa tablice dwuwymiarową.
 * Usuwa z pamięci wskazywaną przez @p arr tablicę dwuwymiarową dowolnego typu o
 * @p size wierszach.
 *
 * @param[in] arr       – tablica do usunięcia,
 * @param[in] size      – długość w pierwszym wymiarze.
 */
void delete_2_dimension_array(void **arr, uint32_t size);

/** @brief Podaje długość liczby.
 * Podaje długość zapisu dziesiętnego liczby @p num.
 *
 * @param[in] num – liczba do zbadania.
 *
 * @return Długość zapisu dziesiętnego liczby @p num.
 */
uint32_t get_number_length(uint32_t num);

/** @brief Podaje @p i -tą cyfrę liczby.
 * Podaje @p i -tą (licząc od 0) cyfrę liczby @p num.
 *
 * @param[in] num – liczba,
 * @param[in] i   – nr cyfry.
 *
 * @return Znak będący @p i -tą cyfrą zapisu dziesiętnego liczby @p num lub null
 * jeśli @p num ma mniej niż i+1 cyfr.
 */
char get_ith_digit_in_number(uint32_t num, uint32_t i);

#endif