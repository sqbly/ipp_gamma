/** @file
 * Nagłówek zawierający funkcje korzystające z ansi escape codes.
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 7.05.2020
 */

#ifndef ANSI_ESCAPE_H
#define ANSI_ESCAPE_H

#include <stdio.h>

/** @brief Czyści konsolę od kursora w dół.
 */
static inline void clear_screen_to_bottom() {
    printf("\x1b[0J");
}

/** @brief Przesuwa kursor na zadaną pozycję.
 * Przesuwa kursor na zadaną pozycję. Nie sprawdza poprawności argumentów.
 * Wiersze i kolumny numerowane są od 1.
 * @param[in] row       – nr wiersza, do którego ma być przesunięty kursor,
 * @param[in] col       – nr kolumny, do której ma być przesunięty kursor.
 */
static inline void move_cursor(int row, int col) {
    printf("\x1b[%d;%df", row, col);
}

/** @brief Przesuwa kursor w górę.
 * Przesuwa kursor o jeden wiersz w górę.
 */
static inline void move_up() {
    printf("\033[1A");
}

/** @brief Przesuwa kursor w dół.
 * Przesuwa kursor o jeden wiersz w dół.
 */
static inline void move_down() {
    printf("\033[1B");
}

/** @brief Przesuwa kursor w prawo.
 * Przesuwa kursor o jedną kolumnę w prawo.
 */
static inline void move_right() {
    printf("\033[1C");
}

/** @brief Przesuwa kursor w lewo.
 * Przesuwa kursor o jedną kolumnę w lewo.
 */
static inline void move_left() {
    printf("\033[1D");
}

#endif /* ANSI_ESCAPE_H */
