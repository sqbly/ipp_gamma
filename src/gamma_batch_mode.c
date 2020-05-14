#include "gamma_batch_mode.h"

static const char command_types[] = {'m', 'g', 'b', 'f', 'q', 'p'};
static const int proper_arg_number[] = {3, 3, 1, 1, 1, 0};
static const int COMMAND_TYPE_NUMBER = sizeof command_types / sizeof(char);

static void report_error(int line_number) {
    fprintf(stderr, "ERROR %d\n", line_number);
}

bool type_and_number_count_match(char type, int number_count) {
    for (int i = 0; i < COMMAND_TYPE_NUMBER; i++)
        if (type == command_types[i] && number_count == proper_arg_number[i])
            return true;

    return false;
}

void execute_command(gamma_t *g, char type, uint32_t player, uint32_t x,
                     uint32_t y, int line_number) {
    char *board;
    switch (type) {
    case 'm':
        printf("%d\n", gamma_move(g, player, x, y));
        break;
    case 'g':
        printf("%d\n", gamma_golden_move(g, player, x, y));
        break;
    case 'b':
        printf("%ld\n", gamma_busy_fields(g, player));
        break;
    case 'f':
        printf("%ld\n", gamma_free_fields(g, player));
        break;
    case 'q':
        printf("%d\n", gamma_golden_possible(g, player));
        break;
    case 'p':
        board = gamma_board(g);
        if (board == NULL)
            report_error(line_number);
        else
            printf("%s", board);
        free(board);
        break;
    }
}

void init_batch_mode(gamma_t *game, int *line_counter) {
    char type = 0;
    uint64_t player, x, y, foo;
    int number_count;

    while (read_command(&type, &player, &x, &y, &foo, &number_count)) {
        *line_counter = *line_counter + 1;

        if (number_count == -2)
            continue;

        if (!type_and_number_count_match(type, number_count)) {
            report_error(*line_counter);
            continue;
        }

        execute_command(game, type, (uint32_t)player, (uint32_t)x, (uint32_t)y,
                        *line_counter);
    }

    if (number_count != -2) {
        *line_counter = *line_counter + 1;

        report_error(*line_counter);
    }
}