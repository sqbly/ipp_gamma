
#ifndef ANSI_ESCAPE_H
#define ANSI_ESCAPE_H

#include <stdio.h>

static inline void clear_screen_to_bottom() {
    printf("\x1b[0J");
}

static inline void move_cursor(int row, int col) {
    printf("\x1b[%d;%df", row, col);
}

static inline void move_up() {
    printf("\033[1A");
}

static inline void move_down() {
    printf("\033[1B");
}

static inline void move_right() {
    printf("\033[1C");
}

static inline void move_left() {
    printf("\033[1D");
}

static inline void save_cursor_position() {
    printf("\x1b%d", 7);
}

static inline void restore_cursor_position() {
    printf("\x1b%d", 8);
}

#endif /* ANSI_ESCAPE_H */
