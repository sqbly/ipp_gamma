#include "gamma_interactive_mode.h"

typedef struct visual_board {
    gamma_t *g;
    uint32_t cursor_x, cursor_y, players, width, height, current_player,
        field_width;
    bool game_ended;

} visual_board_t;

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

void refresh_cursor(visual_board_t *board) {
    move_cursor(board->cursor_y + 1, board->cursor_x + 1);
}

void switch_to_next_player(visual_board_t *board) {
    if (board->current_player == board->players)
        board->current_player = 1;
    else
        board->current_player++;
}

void board_move_up(visual_board_t *board) {
    if (board->cursor_y > 0) {
        move_up();
        board->cursor_y--;
    }
}

void board_move_down(visual_board_t *board) {
    if (board->cursor_y < board->height - 1) {
        move_down();
        board->cursor_y++;
    }
}

void board_move_left(visual_board_t *board) {
    if (board->cursor_x > 0) {
        move_left();
        board->cursor_x -= board->field_width;
    }
}

void board_move_right(visual_board_t *board) {
    if (board->cursor_x < board->field_width * (board->width - 1)) {
        move_right();
        board->cursor_x += board->field_width;
    }
}

void print_player_info(visual_board_t *board) {
    printf("PLAYER %u\nBusy fields: %lu\nFree fields: %lu\n",
           board->current_player,
           gamma_busy_fields(board->g, board->current_player),
           gamma_free_fields(board->g, board->current_player));

    if (gamma_golden_possible(board->g, board->current_player))
        printf("Golden move available");

    printf("\n");
}

void print_board_simple(visual_board_t *board) {
    char *board_state = gamma_board(board->g);

    if (board_state == NULL) {
        gamma_delete(board->g);
        exit(1);
    }

    printf("%s", board_state);
    free(board_state);
}

void print_initial_visuals(visual_board_t *board) {
    move_cursor(0, 0);

    clear_screen_to_bottom();

    print_board_simple(board);

    printf("SOMEBODY MAKE A MOVE\n");

    print_player_info(board);

    move_cursor(0, 0);
}

void refresh(visual_board_t *board) {
    move_cursor(0, 0);

    clear_screen_to_bottom();

    print_board_simple(board);

    print_player_info(board);

    refresh_cursor(board);
}

void print_player_summary(visual_board_t *board, uint32_t player) {
    printf("PLAYER %d: %lu points\n\n", player,
           gamma_busy_fields(board->g, player));
}

void print_summary(visual_board_t *board) {
    move_cursor(0, 0);

    clear_screen_to_bottom();

    print_board_simple(board);

    printf("SOMEBODY MADE A MOVE\n\n");

    for (uint32_t i = 1; i <= board->players; i++)
        print_player_summary(board, i);
}

bool interpret_movement(visual_board_t *board, char *c) {
    if (*c == '\033') {
        refresh(board);

        if ((*c = get_char_raw()) != '[')
            return false;

        refresh(board);

        switch (*c = get_char_raw()) {
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

uint32_t get_column_number(visual_board_t *board) {
    return (board->cursor_x) / (board->field_width);
}

uint32_t get_row_number(visual_board_t *board) {
    return (board->height) - (board->cursor_y) - 1;
}

bool interpret_command(visual_board_t *board, char c) {
    if (c == ' ')
        return gamma_move(board->g, board->current_player,
                          get_column_number(board), get_row_number(board));

    if (c == 'G' || c == 'g')
        return gamma_golden_move(board->g, board->current_player,
                                 get_column_number(board),
                                 get_row_number(board));

    if (c == 'C' || c == 'c' || c == 4)
        return true;

    return false;
}

bool get_players_move(visual_board_t *board) {
    gamma_t *game = board->g;
    uint32_t player = board->current_player;

    if (!gamma_golden_possible(game, player) &&
        gamma_free_fields(game, player) == 0)
        return false;

    char c;
    bool move_made = false;

    while (!move_made && ((c = get_char_raw()) != 4)) {
        if (!interpret_movement(board, &c))
            move_made = interpret_command(board, c);

        refresh(board);
    }

    if (c == 4)
        board->game_ended = true;

    refresh(board);

    return true;
}

void init_interactive_mode(gamma_t *game) {
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
}