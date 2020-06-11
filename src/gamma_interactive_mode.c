/** @file
 * Implementacja biblioteki obsługującej tryb interaktywny
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 7.05.2020
 */

#include "gamma_interactive_mode.h"

/**
 * Struktura przechowująca informacje o wyświetlanej grze.
 */
typedef struct visual_board {
    gamma_t *g;          ///< wskaźnik na strukturę przechowującą stan gry
    uint32_t cursor_x,   ///< współrzędna x pozycji kursora
        cursor_y,        ///< współrzędna y pozycji kursora
        players,         ///< liczba graczy w grze
        width,           ///< szerokość planszy w grze
        height,          ///< wysokość planszy w grze
        current_player,  ///< nr gracza, który aktualnie wykonuje ruch
        field_width;     ///< szerokość jaką zajmują pojedyncze pola
    bool game_ended;  ///< informacja czy wczytano instrukcję kończącą grę

} visual_board_t;

/** @brief Tworzy strukturę wyświetlanej planszy.
 * Tworzy strukturę wyświetlanej planszy i poprawnie wypełnia ją informacjami o
 * podanej grze.
 * @param[in] game   – wskaźnik na strukturę przechowującą stan gry.
 * @return Wypełniona struktura typu visual_board_t.
 */
visual_board_t new_visual_board(gamma_t *game) {
    visual_board_t res;

    res.g = game;
    res.current_player = 1;
    res.cursor_x = 0;
    res.cursor_y = 0;
    res.players = gamma_get_player_number(game);
    res.height = gamma_get_height(game);
    res.width = gamma_get_width(game);
    res.field_width = get_number_length(res.players) + (res.players > 9);
    res.game_ended = false;

    return res;
}

/** @brief Zwiększa numer aktualnie wyświetlanego gracza (zapętla).
 * Jeśli numer aktualnie wyświetlanego gracza nie jest równy liczbie graczy w
 * grze to zwiększa go o jeden, wpp ustawia na 1.
 * @param[in,out] board   – wskaźnik na strukturę przechowującą stan
 *                          wyświetlanej planszy.
 */
void switch_to_next_player(visual_board_t *board) {
    if (board == NULL)
        return;

    if (board->current_player == board->players)
        board->current_player = 1;
    else
        board->current_player++;
}

/** @brief Przesuwa kursor o jeden wiersz w górę.
 * Przesuwa kursor o jeden wiersz w górę. Nie pozwala na wyjście poza planszę.
 * Zakłada poprawność argumentów.
 * @param[in,out] board   – wskaźnik na strukturę przechowującą stan
 *                      wyświetlanej planszy.
 */
void board_move_up(visual_board_t *board) {
    if (board->cursor_y > 0) {
        move_up();
        board->cursor_y--;
    }
}

/** @brief Przesuwa kursor o jeden wiersz w dół.
 * Przesuwa kursor o jeden wiersz w dół. Nie pozwala na wyjście poza planszę.
 * Zakłada poprawność argumentów.
 * @param[in,out] board   – wskaźnik na strukturę przechowującą stan
 *                      wyświetlanej planszy.
 */
void board_move_down(visual_board_t *board) {
    if (board->cursor_y < board->height - 1) {
        move_down();
        board->cursor_y++;
    }
}

/** @brief Przesuwa kursor o jedną kolumnę w lewo.
 * Przesuwa kursor o jedną kolumnę w lewo. Nie pozwala na wyjście poza planszę.
 * Zakłada poprawność argumentów.
 * @param[in,out] board   – wskaźnik na strukturę przechowującą stan
 *                      wyświetlanej planszy.
 */
void board_move_left(visual_board_t *board) {
    if (board->cursor_x > 0) {
        move_left();
        board->cursor_x -= board->field_width;
    }
}

/** @brief Przesuwa kursor o jedną kolumnę w prawo.
 * Przesuwa kursor o jedną kolumnę w prawo. Nie pozwala na wyjście poza planszę.
 * Zakłada poprawność argumentów.
 * @param[in,out] board   – wskaźnik na strukturę przechowującą stan
 *                      wyświetlanej planszy.
 */
void board_move_right(visual_board_t *board) {
    if (board->cursor_x < board->field_width * (board->width - 1)) {
        move_right();
        board->cursor_x += board->field_width;
    }
}

/** @brief Wyświetla informacje o graczu aktualnie wykonującym ruch.
 * Wyświetla informacje o graczu aktualnie wykonującym ruch: liczbę zajętych
 * pól, liczbę pól, które jeszcze może zająć i informację czy może wykonać złoty
 * ruch. Zakłada poprawność argumentów.
 * @param[in] board   – wskaźnik na strukturę przechowującą stan
 *                      wyświetlanej planszy.
 */
void print_player_info(visual_board_t *board) {
    printf("Player %u\nBusy fields: %lu\nFree fields: %lu\n",
           board->current_player,
           gamma_busy_fields(board->g, board->current_player),
           gamma_free_fields(board->g, board->current_player));

    if (gamma_golden_possible(board->g, board->current_player))
        printf("Golden move available");

    printf("\n");
}

/** @brief Zwraca numer kolumny, w której znajduje się kursor.
 * Zwraca numer kolumny, w której znajduje się kursor. Zakłada poprawność
 * argumentów.
 * @param[in,out] board   – wskaźnik na strukturę przechowującą stan
 *                          wyświetlanej planszy.
 * @return Numer kolumny, w której znajduje się kursor.
 */
uint32_t get_column_number(visual_board_t *board) {
    return (board->cursor_x) / (board->field_width);
}

/** @brief Zwraca numer wiersza, w którym znajduje się kursor.
 * Zwraca numer wiersza, w którym znajduje się kursor. Zakłada poprawność
 * argumentów.
 * @param[in,out] board   – wskaźnik na strukturę przechowującą stan
 *                          wyświetlanej planszy.
 * @return Numer wiersza, w którym znajduje się kursor.
 */
uint32_t get_row_number(visual_board_t *board) {
    return (board->height) - (board->cursor_y) - 1;
}

/** @brief Wyświetla planszę w miejscu, w którym znajduje się kursor i nie cofa
 * go.
 * Wyświetla planszę w miejscu, w którym znajduje się kursor i nie cofa go.
 * Zakłada poprawność argumentów.
 * @param[in] board   – wskaźnik na strukturę przechowującą stan
 *                      wyświetlanej planszy.
 */
void print_board_simple(visual_board_t *board) {
    char *board_state = gamma_board(board->g);

    if (board_state == NULL) {
        gamma_delete(board->g);
        show_coursor();
        exit(1);
    }

    uint64_t index = 0;
    for (uint32_t i = 0; i < board->height; i++) {
        for (uint32_t j = 0; j < board->width; j++) {
            if (get_row_number(board) == board->height - i - 1 &&
                get_column_number(board) == j)
                set_background_color(MAGENTA);

            for (uint32_t k = 0; k < board->field_width; k++) {
                if (k == board->field_width - 1 && k > 0)
                    set_background_color(NO_COLOR);

                printf("%c", board_state[index]);
                index++;
            }
            set_background_color(NO_COLOR);
        }
        printf("%c", board_state[index]);
        index++;
    }

    free(board_state);
}

/** @brief Czyści konsolę i wyświetla informacje o grze. Ustawia kursor w lewym
 * górnym rogu.
 * Czyści konsolę i wyświetla informacje o grze: planszę i informacje o
 * pierwszym graczu. Ustawia kursor w lewym górnym rogu. Zakłada poprawność
 * argumentów.
 * @param[in] board   – wskaźnik na strukturę przechowującą stan
 *                      wyświetlanej planszy.
 */
void print_initial_visuals(visual_board_t *board) {
    move_cursor(0, 0);

    clear_screen_to_bottom();

    print_board_simple(board);

    print_player_info(board);

    move_cursor(0, 0);
}

/** @brief "Odświeża" wyświetlone informacje o grze.
 * Czyści konsolę i wyświetla informacje o grze: planszę i informacje o
 * graczu aktualnie wykonującym ruch. Pozostawia kursor w tej samej pozycji, w
 * której był. Zakłada poprawność argumentów.
 * @param[in] board   – wskaźnik na strukturę przechowującą stan
 *                      wyświetlanej planszy.
 */
void refresh(visual_board_t *board) {
    move_cursor(0, 0);

    clear_screen_to_bottom();

    print_board_simple(board);

    print_player_info(board);
}

/** @brief Wyświetla podsumowanie zdobytych przez gracza punktów.
 * Wyświetla podsumowanie zdobytych przez gracza punktów. Zakłada poprawność
 * argumentów.
 * @param[in] board   – wskaźnik na strukturę przechowującą stan
 *                      wyświetlanej planszy,
 * @param[in] player  – nr gracza.
 */
void print_player_summary(visual_board_t *board, uint32_t player) {
    printf("Player %d: %lu points\n\n", player,
           gamma_busy_fields(board->g, player));
}

void print_winners(visual_board_t *board) {
    uint64_t max_res = 0;
    uint32_t number_of_winners = 0;

    for (uint32_t i = 1; i <= board->players; i++) {
        if (gamma_busy_fields(board->g, i) > max_res) {
            max_res = gamma_busy_fields(board->g, i);
            number_of_winners = 1;
        }
        else if (gamma_busy_fields(board->g, i) == max_res) {
            number_of_winners++;
        }
    }

    if (number_of_winners > 1) {
        printf("WINNERS:\n\n");
    }
    else {
        printf("WINNER:\n\n");
    }

    for (uint32_t i = 1; i <= board->players; i++) {
        if (gamma_busy_fields(board->g, i) == max_res) {
            printf("Player %d\n", i);
        }
    }

    printf("\n");
}

/** @brief Wyświetla podsumowanie gry.
 * Wyświetla stan planszy pod koniec gry i punkty zdobyte przez wszystkich
 * graczy. Zakłada poprawność argumentów.
 * @param[in] board   – wskaźnik na strukturę przechowującą stan
 *                      wyświetlanej planszy.
 */
void print_summary(visual_board_t *board) {
    move_cursor(0, 0);

    clear_screen_to_bottom();

    board->cursor_x = -1;
    board->cursor_y = -1;

    print_board_simple(board);

    printf("\nRESULTS:\n\n");

    print_winners(board);

    printf("\nSCORES:\n\n");

    for (uint32_t i = 1; i <= board->players; i++)
        print_player_summary(board, i);
}

/** @brief Sprawdza czy wczytany znak rozpoczyna sekwencję opisującą ruch.
 * Sprawdza czy wczytany znak rozpoczyna sekwencję opisującą ruch. Jeśli tak to
 * wczytuje resztę sekwencji i wykonuje go. Wpp lub jeśli sekwencja jest
 * niepoprawna ustawia zmienną @p c na następny znak z wejścia. Zakłada
 * poprawność argumentów.
 * @param[in,out] board   – wskaźnik na strukturę przechowującą stan
 *                          wyświetlanej planszy,
 * @param[in,out] c       – wczytany znak z wejścia.
 * @return Wartość @p true jeśli wczytano i wykonano sekwencję opisującą ruch,
 * wpp @p false .
 */
bool interpret_movement(visual_board_t *board, char *c) {
    if (*c == '\033') {
        refresh(board);

        if ((*c = get_char_raw(board->g)) != '[')
            return false;

        refresh(board);

        switch (*c = get_char_raw(board->g)) {
        case 'A':
            board_move_up(board);
            break;
        case 'B':
            board_move_down(board);
            break;
        case 'C':
            board_move_right(board);
            break;
        case 'D':
            board_move_left(board);
            break;
        default:
            return false;
        }

        return true;
    }
    else {
        return false;
    }
}

/** @brief Interpretuje znak wczytany z wejścia, który nie opisuje ruchu.
 * Interpretuje znak wczytany z wejścia, zakładając, że nie opisuje on ruchu.
 * @param[in,out] board   – wskaźnik na strukturę przechowującą stan
 *                          wyświetlanej planszy,
 * @param[in,out] c       – wczytany znak z wejścia.
 * @return Wartość @p true jeśli wczytano i wykonano ruch, w przeciwnym
 * przypadku wartość @p false .
 */
bool interpret_command(visual_board_t *board, char c) {
    if (c == ' ')
        return gamma_move(board->g, board->current_player,
                          get_column_number(board), get_row_number(board));

    if (c == 'G' || c == 'g')
        return gamma_golden_move(board->g, board->current_player,
                                 get_column_number(board),
                                 get_row_number(board));

    if (c == 'C' || c == 'c' || c == 4 || c == 26)
        return true;

    return false;
}

/** @brief Obsługuje wykonanie ruchu przez gracza.
 * Jeśli gracz może wykonać ruch, wczytuje znaki z wejścia aż zostanie wykonany
 * poprawny ruch lub gra się zakończy. Jeśli gracz nie może wykonać ruchu kończy
 * wykonanie.
 * @param[in,out] board   – wskaźnik na strukturę przechowującą stan
 *                          wyświetlanej planszy.
 * @return Wartość @p true jeśli wczytano i wykonano ruch, w przeciwnym
 * przypadku wartość @p false .
 */
bool get_players_move(visual_board_t *board) {
    gamma_t *game = board->g;
    uint32_t player = board->current_player;

    if (!gamma_golden_possible(game, player) &&
        gamma_free_fields(game, player) == 0)
        return false;

    char c;
    bool move_made = false;

    while (!move_made && ((c = get_char_raw(board->g)) != 4) && c != 26) {
        if (!interpret_movement(board, &c))
            move_made = interpret_command(board, c);

        refresh(board);
    }

    if (c == 4 || c == 26)
        board->game_ended = true;

    refresh(board);

    return true;
}

void init_interactive_mode(gamma_t *game) {
    hide_coursor();
    visual_board_t board = new_visual_board(game);

    print_initial_visuals(&board);

    uint32_t skipped_players = 0;

    while (skipped_players < board.players) {
        if (get_players_move(&board))
            skipped_players = 0;
        else
            skipped_players++;

        switch_to_next_player(&board);

        refresh(&board);

        if (board.game_ended)
            break;
    }

    print_summary(&board);
    show_coursor();
}