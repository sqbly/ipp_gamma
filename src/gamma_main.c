/** @file
 * Implementacja gry gamma.
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 7.05.2020
 */

#include "gamma.h"
#include "gamma_batch_mode.h"
#include "gamma_interactive_mode.h"
#include "input.h"

typedef struct game_parameters {
    uint32_t width, height, players, areas;
} game_parameters;

void set_game_parameters_value(game_parameters *parameters, uint64_t width,
                               uint64_t height, uint64_t players,
                               uint64_t areas) {
    parameters->width = (uint32_t)width;
    parameters->height = (uint32_t)height;
    parameters->players = (uint32_t)players;
    parameters->areas = (uint32_t)areas;
}

game_parameters new_game_parameters() {
    game_parameters res;
    set_game_parameters_value(&res, 0, 0, 0, 0);
    return res;
}

static void report_error(int line_number) {
    fprintf(stderr, "ERROR %d\n", line_number);
}

static void report_ok(int line_number) {
    printf("OK %d\n", line_number);
}

bool determine_game_mode(char *mode, game_parameters *parameters,
                         int *line_counter) {
    uint64_t width, height, players, areas;
    int number_count = -1;
    *mode = 'A';

    while (
        read_command(mode, &width, &height, &players, &areas, &number_count)) {
        *line_counter = *line_counter + 1;

        if ((*mode == 'B' || *mode == 'I') && number_count == 4) {
            set_game_parameters_value(parameters, width, height, players,
                                      areas);
            return true;
        }
        else {
            if (number_count != IGNORE) {
                report_error(*line_counter);
            }
        }
    }

    if (number_count != IGNORE) {
        *line_counter = *line_counter + 1;

        report_error(*line_counter);
    }

    *mode = 'A';
    return false;
}

int main() {
    char type;
    game_parameters parameters = new_game_parameters();
    int line_counter = 0;
    bool game_created = false;
    gamma_t *game;

    while (!game_created &&
           determine_game_mode(&type, &parameters, &line_counter)) {
        if (type == 'B') {
            game = gamma_new(parameters.width, parameters.height,
                             parameters.players, parameters.areas);

            if (game != NULL) {
                game_created = true;
                report_ok(line_counter);
                init_batch_mode(game, &line_counter);
                gamma_delete(game);
            }
            else {
                report_error(line_counter);
            }
        }

        if (type == 'I') {
            game = gamma_new(parameters.width, parameters.height,
                             parameters.players, parameters.areas);

            if (game != NULL) {
                game_created = true;
                init_interactive_mode(game);
                gamma_delete(game);
            }
            else {
                report_error(line_counter);
            }
        }
    }
}