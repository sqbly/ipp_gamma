/** @file
 * Implementacja biblioteki obsługującej tryb wsadowy
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 7.05.2020
 */

#include "gamma_batch_mode.h"

/**
 * Tablica przechowująca dopuszczane instrukcje.
 */
static const char command_types[] = {'m', 'g', 'b', 'f', 'q', 'p'};

/**
 * Tablica przechowująca liczbę argumentów wymaganych przez instrukcje na
 * odpowiadających pozycjach w tabeli @p command_types .
 */
static const int proper_arg_number[] = {3, 3, 1, 1, 1, 0};

/**
 * Stała przechowująca liczbę typów instrukcji.
 */
static const int COMMAND_TYPE_NUMBER = sizeof command_types / sizeof(char);

/** @brief Odnotowuje błąd na wyjściu diagnostycznym.
 * Raportuje błąd i podaje nr_wiersza, w którym pojawiło się niepoprawne
 * polecenie.
 * @param[in] line_number      – nr wiersza.
 */
static void report_error(int line_number) {
    fprintf(stderr, "ERROR %d\n", line_number);
}

/** @brief Sprawdza czy wczytany typ instrukcji i liczba podanych argumentów się
 * zgadzają.
 * @param[in] type         – typ instrukcji,
 * @param[in] number_count – liczba argumentów
 * @return Wartość @p true jeśli funkcja otrzymała adekwatną liczbę argumentów,
 * wartość @p false w przeciwnym przypadku.
 */
bool type_and_number_count_match(char type, int number_count) {
    for (int i = 0; i < COMMAND_TYPE_NUMBER; i++)
        if (type == command_types[i] && number_count == proper_arg_number[i])
            return true;

    return false;
}

/** @brief Interpretuje instrukcję i wykonuje ją.
 * Interpretuje instrukcję i wykonuje ją. Zakłada, że typ instrukcji i liczba
 * parametrów są poprawne. Ignoruje parametry, które nie były potrzebne w danym
 * wykonaniu funkcji. Wypisuje wynik funkcji na standardowe wyjście, przy czym
 * wartość @p true wypisuje jako 1, a @p false jako 0.
 * @param[in,out] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] type        – typ instrukcji,
 * @param[in] player      – numer gracza, w przypadku gdy instrukcja go wymaga,
 * @param[in] x           – numer kolumny, w przypadku gdy instrukcja go wymaga,
 * @param[in] y           – numer wiersza, w przypadku gdy instrukcja go wymaga,
 * @param[in] line_number – nr wiersza, w którym została podana instrukcja.
 */
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