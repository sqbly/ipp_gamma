/** @file
 * Implementacja klasy z nagłówka gamma.h .
 *
 * @author Marcin Peczarski <marpe@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 18.03.2020
 */

#include "gamma.h"

/** Struktura przechowująca stan gracza.
 */
typedef struct player {
    bool spent_golden_move;  ///< czy użył złotego ruchu

    ui64 occupied_fields;            ///< ile pól posiada,
    ui64 available_adjacent_fields;  ///< ile wolnych pól przylega do pionków
                                     ///< gracza,
    ui64 area_count;                 ///< liczba różnych obszarów gracza.

} player_t;

/** Struktura przechowująca stan pola na planszy.
 */
typedef struct field {
    ui32 owner;       ///< numer właściciela,
    ui32 last_visit;  ///< numer ostatniej 'wizyty' przeszukiwaniem grafu,

    ui64 rank;  ///< ranga obszaru, do którego należy pole,

    struct field *parent;  ///< wskaźnik na reprezentanta danego pola.

} field_t;

/**
 * Struktura przechowująca stan gry.
 */
typedef struct gamma {
    ui32 width;           ///< szerokość planszy
    ui32 height;          ///< wysokość planszy
    ui32 no_of_players;   ///< liczba graczy
    ui32 max_area_count;  ///< maksymalna liczba obszarów, jakie może zająć
                          ///< jeden gracz
    ui32 bfs_calls;       ///< liczba wywołań przeszukiwania wszerz

    ui64 free_fields;  ///< liczba wolnych pól na planszy

    player_t *players;  ///< tablica przechowująca stany graczy

    field_t **board;  ///< tablica dwuwymiarowa przechowująca stany pól

} gamma_t;

/** @brief Sprawdza czy pole znajduje się na planszy.
 * Sprawdza czy pole o podanych współrzędnych znajduje się na planszy.
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] field   – struktura przechowująca informacje o polu.
 *
 * @return Wartość @p true, jeśli pole o podanych współrzędnych znajduje się na
 * planszy, a @p false w przeciwnym przypadku.
 */
bool gamma_field_out_of_bounds(gamma_t *g, point_t field);

// Find Union

/** @brief Podaje reprezentanta podanego pola.
 * Podaje reprezentanta zbioru, w którym znajduje się pole wskazane przez @p a .
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] a       – wskaźnik na strukturę przechowująca informacje o polu.
 *
 * @return Wskaźnik na pole będące reprezentantem pola wskazanego przez
 * @p field .
 */
field_t *f_u_find(gamma_t *g, field_t *a) {
    if (a == NULL || a == a->parent)
        return a;

    return a->parent = f_u_find(g, a->parent);
}

/** @brief Łączy zbiory, do których należą wskazane dwa pola.
 * Łączy zbiory, do których należą pola wskazane przez @p a i @p b .
 *
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] a   – wskaźnik na strukturę przechowującą informacje o 1. polu,
 * @param[in] b   – wskaźnik na strukturę przechowującą informacje o 2. polu.
 */
void f_u_union(gamma_t *g, field_t *a, field_t *b) {
    field_t *a_rep = f_u_find(g, a);
    field_t *b_rep = f_u_find(g, b);

    if (a_rep == b_rep)
        return;

    if (a_rep->rank >= b_rep->rank) {
        b_rep->parent = a_rep->parent;
        if (a_rep->rank == b_rep->rank)
            a_rep->rank++;
    } else {
        a_rep->parent = b_rep->parent;
    }
}

/** @brief Sprawdza, czy dwa pola należą do jednego zbioru.
 * Sprawdza, pola @p a i @p b należą do tego samego zbioru.
 *
 * @param[in] g         – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] a         – struktura przechowująca informacje o 1. polu,
 * @param[in] b         – struktura przechowująca informacje o 2. polu.
 *
 * @return Wartość @p true jeśli pola należą do tego samego zbioru, @p false w
 * przeciwnym przypadku.
 */
bool gamma_are_in_union(gamma_t *g, point_t a, point_t b) {
    field_t *a_field = &g->board[a.x][a.y];
    field_t *b_field = &g->board[b.x][b.y];

    return f_u_find(g, a_field) == f_u_find(g, b_field);
}

/** @brief Łączy zbiory, do których należą dwa pola.
 * Łączy zbiory, do których należą pola @p a i @p b .
 *
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] a       – struktura przechowującą informacje o 1. polu,
 * @param[in] b       – struktura przechowującą informacje o 2. polu.
 */
void gamma_union_fields(gamma_t *g, point_t a, point_t b) {
    f_u_union(g, &g->board[a.x][a.y], &g->board[b.x][b.y]);
}

// Gettery

/** @brief Podaje właściciela pola.
 * Podaje numer gracza będącego właścicielem pola @p field .
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] field   – struktura przechowująca informacje o polu.
 *
 * @return Numer gracza będącego właścicielem pola @p field , lub 0 jeśli któryś
 * z paremetrów jest niepoprawny.
 */
ui32 gamma_field_owner(gamma_t *g, point_t field) {
    if (gamma_field_out_of_bounds(g, field))
        return 0;
    else
        return g->board[field.x][field.y].owner;
}

/** @brief Podaje czas ostatnich odwiedzin pola bfs'em.
 * Podaje numer porządkowy przeszukiwania grafu, które jako ostatnie
 * "odwiedziło" podane pole.
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] field   – struktura przechowująca informacje o polu.
 *
 * @return Numer ostatniej wizyty pola @p field bfs'em, lub numer ostatniego
 * wywołania bfs'a jeśli któryś z paremetrów jest niepoprawny.
 */
ui32 gamma_field_last_visit(gamma_t *g, point_t field) {
    if (gamma_field_out_of_bounds(g, field))
        return g->bfs_calls;
    else
        return g->board[field.x][field.y].last_visit;
}

/** @brief Podaje i-ty znak w opisie pola.
 * Podaje @p i -ty z kolei znak opisie pola o współrzędnych @p x , @p y .
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new,
 * @param[in] i       – nr znaku w opisie pola.
 *
 * @return i-ty znak w opisie podanego pola jeśli dane są poprawne.
 * Niezdefiniowane zachowanie dla danych niepoprawnych.
 */
char gamma_ith_char_in_field_description(gamma_t *g, ui32 x, ui32 y, ui32 i) {
    ui32 field_width = get_number_length(g->no_of_players);
    if (field_width > 1)
        field_width++;

    ui32 owner_num = g->board[x][y].owner;

    if (i == field_width && x == g->width)
        return '\n';

    if (owner_num == 0) {
        if (i == 0)
            return '.';
        else
            return ' ';
    } else {
        if (i < get_number_length(owner_num))
            return get_ith_digit_in_number(owner_num, i);
        else
            return ' ';
    }
}

// Checkery

/** @brief Sprawdza czy numer gracza jest poprawny.
 * Sprawdza czy w rozgrywce wskazanej przez @p g  bierze gracz o numerze
 * @p player .
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza
 *
 * @return Wartość @p true jeśli numer gracza jest poprawny, @p false w
 * przeciwnym przypadku.
 */
bool gamma_player_number_correct(gamma_t *g, ui32 player) {
    return player > 0 && player <= g->no_of_players;
}

// Komentarz przy deklaracji.
bool gamma_field_out_of_bounds(gamma_t *g, point_t field) {
    if (field.x <= 0 || field.x > g->width || field.y <= 0 ||
        field.y > g->height)
        return true;
    else
        return false;
}

/** @brief Sprawdza czy pole zostało odwiedzone ostatnim bfs'em.
 * Sprawdza czy pole @p field zostało odwiedzone w ostatnim przeszukiwaniu pól
 * wszerz.
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] field   – struktura przechowująca informacje o polu.
 *
 * @return Wartość @p true jeśli pole zostało odwiedzone ostatnim bfs'em lub
 * dane są niepoprawne, @p false w przeciwnym przypadku.
 */
bool gamma_field_recently_visited(gamma_t *g, point_t field) {
    if (gamma_field_out_of_bounds(g, field))
        return true;
    else
        return g->board[field.x][field.y].last_visit == g->bfs_calls;
}

/** @brief Sprawdza czy pole sąsiaduje z pionkami gracza.
 * Sprawdza czy pole @p field sąsiaduje z jakimkolwiek pionkiem gracza
 * @p player.
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza,
 * @param[in] field   – struktura przechowująca informacje o polu.
 *
 * @return Wartość @p true jeśli dane są poprawne i @p field sąsiaduje z graczem
 * @p player , @p false w przeciwnym przypadku.
 */
bool gamma_field_adjacent_to_player(gamma_t *g, ui32 player, point_t field) {
    if (gamma_field_out_of_bounds(g, field))
        return false;

    int target_owner_fields = 0;

    for (int i = 0; i < 4; i++)
        if (gamma_field_owner(g, point_add(field, compass_rose(i))) == player)
            target_owner_fields++;

    return target_owner_fields != 0;
}

/** @brief Sprawdza czy pole jest wolne.
 * Sprawdza czy na polu @p field można postawić pionek.
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] field   – struktura przechowująca informacje o polu.
 *
 * @return Wartość @p true, jeśli pole @p field jest wolne i dane są poprawne, a
 * @p false w przeciwnym przypadku.
 */
bool gamma_field_is_available(gamma_t *g, point_t field) {
    return !gamma_field_out_of_bounds(g, field) &&
           gamma_field_owner(g, field) == 0;
}

/** @brief Sprawdza czy gracz osiągnął limit obszarów.
 * Sprawdza czy liczba rozłącznych obszarów, z których składa się zbiór pól
 * zajętych przez gracza @p player jest równa maksymalnej dopuszczonej liczbie.
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza.
 *
 * @return Wartość @p true jeśli gracz @p player osiągnął limit obszarów i dane
 * są poprawne, @p false w przeciwnym przypadku.
 */
bool gamma_area_limit_reached(gamma_t *g, ui32 player) {
    return g->players[player].area_count >= g->max_area_count;
}

/** @brief Sprawdza czy gracz przekroczył limit obszarów.
 * Sprawdza czy liczba rozłącznych obszarów, z których składa się zbiór pól
 * zajętych przez gracza @p player przekracza maksymalną dopuszczoną liczbę.
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza.
 *
 * @return Wartość @p true jeśli gracz @p player przekroczył limit obszarów i
 * dane są poprawne, @p false w przeciwnym przypadku.
 */
bool gamma_area_limit_exceeded(gamma_t *g, ui32 player) {
    return g->players[player].area_count > g->max_area_count;
}

/** @brief Sprawdza czy gracz może zająć pole nie przekraczając limitu obszarów.
 * Sprawdza czy liczba rozłącznych obszarów, z których składa się zbiór pól
 * zajętych przez gracza i pola @p field nie przekracza maksymalnej dopuszczonej
 * liczby.
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza,
 * @param[in] field   – struktura przechowująca informacje o polu.
 *
 * @return Wartość @p true jeśli gracz @p player przekroczyłby limit obszarów po
 * zajęciu pola @p field i dane są poprawne, @p false w przeciwnym przypadku.
 */
bool gamma_area_limit_allows(gamma_t *g, ui32 player, point_t field) {
    return gamma_field_adjacent_to_player(g, player, field) ||
           !gamma_area_limit_reached(g, player);
}

/** @brief Sprawdza czy gracz może zająć pole.
 * Sprawdza czy gracz @p player może zajęć pole @p field nie łamiąc zasad gry.
 *
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza,
 * @param[in] field   – struktura przechowująca informacje o polu.
 *
 * @return Wartość @p true jeśli gracz @p player może zająć pole @p field i dane
 * są poprawne, @p false w przeciwnym przypadku.
 */
bool gamma_player_can_take_field(gamma_t *g, ui32 player, point_t field) {
    if (g == NULL || !gamma_player_number_correct(g, player) ||
        gamma_field_out_of_bounds(g, field) ||
        gamma_field_owner(g, field) != 0 ||
        !gamma_area_limit_allows(g, player, field))
        return false;
    else
        return true;
}

// Settery

void gamma_increase_area_count(gamma_t *g, ui32 player) {
    g->players[player].area_count++;
}

void gamma_decrease_area_count(gamma_t *g, ui32 player) {
    g->players[player].area_count--;
}

void gamma_mark_visit(gamma_t *g, point_t field) {
    g->board[field.x][field.y].last_visit = g->bfs_calls;
}

void gamma_mark_field_unavailable(gamma_t *g, point_t field) {
    ui32 already_updated[4], owner;
    point_t tmp;
    bool updated;
    for (int i = 0; i < 4; i++) {
        updated = false;
        tmp = point_add(field, compass_rose(i));
        owner = gamma_field_owner(g, tmp);
        already_updated[i] = owner;

        for (int j = 0; j < i; j++)
            if (already_updated[j] == owner)
                updated = true;

        if (!updated)
            g->players[owner].available_adjacent_fields--;
    }
}

void gamma_mark_field_available(gamma_t *g, point_t field) {
    ui32 already_updated[4], owner;
    point_t tmp;
    bool updated;
    for (int i = 0; i < 4; i++) {
        updated = false;
        tmp = point_add(field, compass_rose(i));
        owner = gamma_field_owner(g, tmp);
        already_updated[i] = owner;

        for (int j = 0; j < i; j++)
            if (already_updated[j] == owner)
                updated = true;

        if (!updated)
            g->players[owner].available_adjacent_fields++;
    }
}

void gamma_union_to_adjacent(gamma_t *g, ui32 player, point_t field) {
    for (int i = 0; i < 4; i++) {
        point_t tmp = point_add(field, compass_rose(i));

        if (gamma_field_owner(g, tmp) == player) {
            if (!gamma_are_in_union(g, field, tmp))
                gamma_decrease_area_count(g, player);

            gamma_union_fields(g, field, tmp);
        }
    }
}

void gamma_add_available_adjacent(gamma_t *g, ui32 player, point_t field) {
    for (int i = 0; i < 4; i++) {
        point_t target = point_add(field, compass_rose(i));

        if (gamma_field_owner(g, target) == 0 &&
            !gamma_field_out_of_bounds(g, target) &&
            !gamma_field_adjacent_to_player(g, player, target))
            g->players[player].available_adjacent_fields++;
    }
}

void gamma_remove_no_longer_available_adjacent(gamma_t *g, ui32 player,
                                               point_t field) {
    if (gamma_field_out_of_bounds(g, field))
        return;

    for (int i = 0; i < 4; i++) {
        point_t tmp = point_add(field, compass_rose(i));

        if (!gamma_field_adjacent_to_player(g, player, tmp) &&
            gamma_field_is_available(g, tmp))
            g->players[player].available_adjacent_fields--;
    }
}

void gamma_mark_players_ownership(gamma_t *g, ui32 player, point_t field) {
    gamma_mark_field_unavailable(g, field);

    g->board[field.x][field.y].owner = player;

    g->board[field.x][field.y].parent = &g->board[field.x][field.y];

    g->players[player].occupied_fields++;

    g->free_fields--;
}

void gamma_remove_players_ownership(gamma_t *g, ui32 player, point_t field) {
    g->board[field.x][field.y].owner = 0;

    gamma_remove_no_longer_available_adjacent(g, player, field);

    gamma_decrease_area_count(g, player);

    g->players[player].occupied_fields--;

    gamma_mark_field_available(g, field);

    g->free_fields++;
}

void gamma_forget_parents_in_area(gamma_t *g, ui32 player, point_t start) {
    list_t *list = list_init();
    list_add(list, start);

    g->bfs_calls++;

    point_t field;

    while (!list_empty(list)) {
        field = list_pop(list);

        g->board[field.x][field.y].parent = &g->board[field.x][field.y];
        g->board[field.x][field.y].rank = 0;

        point_t tmp;
        for (int i = 0; i < 4; i++) {
            tmp = point_add(field, compass_rose(i));
            if (!gamma_field_recently_visited(g, tmp) &&
                gamma_field_owner(g, tmp) == player) {
                list_add(list, point_add(field, compass_rose(i)));
                gamma_mark_visit(g, tmp);
            }
        }
    }

    list_delete(list);
}

void gamma_recalc_areas_and_parents(gamma_t *g, ui32 player, point_t start) {
    list_t *list = list_init();
    point_t field;
    for (int i = 0; i < 4; i++) {
        field = point_add(start, compass_rose(i));
        if (gamma_field_owner(g, field) == player) {
            list_add(list, field);
            gamma_increase_area_count(g, player);
        }
    }

    g->bfs_calls++;

    point_t tmp;
    while (!list_empty(list)) {
        field = list_pop(list);

        for (int i = 0; i < 4; i++) {
            tmp = point_add(field, compass_rose(i));

            if (gamma_field_owner(g, tmp) == player) {
                if (gamma_field_recently_visited(g, tmp)) {
                    if (!gamma_are_in_union(g, field, tmp))
                        gamma_decrease_area_count(g, player);
                } else {
                    list_add(list, tmp);
                    gamma_mark_visit(g, tmp);
                }

                gamma_union_fields(g, field, tmp);
            }
        }
    }

    list_delete(list);
}

// Funkcje eksportowane

gamma_t *gamma_new(uint32_t width, uint32_t height, uint32_t players,
                   uint32_t areas) {
    if (width <= 0 || height <= 0 || players <= 0)
        return NULL;

    gamma_t *res = malloc(sizeof(gamma_t));
    if (res == NULL)
        return NULL;

    res->width = width;
    res->height = height;
    res->no_of_players = players;
    res->max_area_count = areas;
    res->bfs_calls = 0;

    res->free_fields = width * height;

    res->players = calloc((players + 1), sizeof(player_t));
    if (res->players == NULL)
        return NULL;

    res->board = malloc((width + 1) * sizeof(field_t *));
    if (res->board == NULL)
        return NULL;

    for (ui32 i = 0; i <= width; i++) {
        res->board[i] = calloc((height + 1), sizeof(field_t));
        if (res->board[i] == NULL)
            return NULL;
    }

    return res;
}

void gamma_delete(gamma_t *g) {
    if (g == NULL)
        return;

    free(g->players);

    delete_2_dimension_array((void **)g->board, g->width + 1);

    free(g);
}

bool gamma_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    point_t target = make_point(x + 1, y + 1);

    if (!gamma_player_can_take_field(g, player, target))
        return false;

    gamma_add_available_adjacent(g, player, target);

    gamma_mark_players_ownership(g, player, target);

    gamma_increase_area_count(g, player);

    gamma_union_to_adjacent(g, player, target);

    return true;
}

bool gamma_golden_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    point_t target = make_point(x + 1, y + 1);

    if (!gamma_golden_possible(g, player) ||
        gamma_field_out_of_bounds(g, target) ||
        gamma_field_owner(g, target) == 0 ||
        gamma_field_owner(g, target) == player ||
        !gamma_area_limit_allows(g, player, target))
        return false;

    ui32 old_owner = gamma_field_owner(g, target);

    gamma_forget_parents_in_area(g, old_owner, target);

    gamma_remove_players_ownership(g, old_owner, target);

    gamma_recalc_areas_and_parents(g, old_owner, target);

    if (gamma_area_limit_exceeded(g, old_owner)) {
        gamma_move(g, old_owner, x, y);

        return false;
    } else {
        gamma_move(g, player, x, y);
        g->players[player].spent_golden_move = true;

        return true;
    }
}

uint64_t gamma_busy_fields(gamma_t *g, uint32_t player) {
    if (g == NULL || !gamma_player_number_correct(g, player))
        return 0;

    return g->players[player].occupied_fields;
}

uint64_t gamma_free_fields(gamma_t *g, uint32_t player) {
    if (g == NULL || !gamma_player_number_correct(g, player))
        return 0;

    if (gamma_area_limit_reached(g, player))
        return g->players[player].available_adjacent_fields;
    else
        return g->free_fields;
}

bool gamma_golden_possible(gamma_t *g, uint32_t player) {
    if (g == NULL || !gamma_player_number_correct(g, player))
        return false;

    if (g->players[player].spent_golden_move)
        return false;

    for (ui32 i = 1; i <= g->no_of_players; i++)
        if (i != player && g->players[i].occupied_fields > 0)
            return true;

    return false;
}

char *gamma_board(gamma_t *g) {
    if (g == NULL)
        return NULL;

    ui32 field_width = get_number_length(g->no_of_players);

    if (field_width > 1)
        field_width++;

    ui64 res_size = (field_width * g->width + 1) * g->height + 1;

    char *res = malloc(res_size * sizeof(char));
    if (res == NULL)
        return NULL;

    ui64 iter = 0;

    for (ui32 i = g->height; i > 0; i--)
        for (ui32 j = 1; j <= g->width; j++)
            for (ui32 k = 0; k < field_width + (j == g->width); k++)
                res[iter++] = gamma_ith_char_in_field_description(g, j, i, k);

    res[iter] = 0;

    return res;
}