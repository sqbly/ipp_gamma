/** @file
 * Nagłówek zawierający funkcje korzystające z ansi escape codes.
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 7.05.2020
 */

#ifndef ANSI_ESCAPE_H
#define ANSI_ESCAPE_H

#include <stdio.h>

/** Kod do resetowania koloru tła lub tekstu.
 */
#define RESET_COLOR 0

/** Kod do zmienienia koloru tła na magentę.
 */
#define MAGENTA_BKG 45

/** Kod do zmienienia koloru tekstu na żółty.
 */
#define YELLOW_TXT 33

/** Kod do zmienienia koloru tekstu na czerwony.
 */
#define RED_TXT 31

/** Kod do zmienienia koloru tekstu na zielony.
 */
#define GREEN_TXT 32

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

/** @brief Zmienia kolor tła tekstu.
 * Zmienia kolor tła tekstu na ten podany za pomocą @p code.
 * @param[in] code      – nr koloru tła.
 */
static inline void set_background_color(int code) {
    printf("\x1b[%dm", code);
}

/** @brief Zmienia kolor tekstu.
 * Zmienia kolor tekstu na ten podany za pomocą @p code.
 * @param[in] code      – nr koloru.
 */
static inline void set_text_color(int code) {
    printf("\x1b[%dm", code);
}

/** @brief Chowa kursor.
 * Chowa kursor.
 */
static inline void hide_coursor() {
    printf("\x1b[?25l");
}

/** @brief Pokazuje kursor.
 * Pokazuje kursor.
 */
static inline void show_coursor() {
    printf("\x1b[?25h");
}

#endif /* ANSI_ESCAPE_H */
