#include "gamma.h"

typedef struct player {
    ui64 occupied_squares, available_adjacent_squares, area_count;

    bool spent_golden_move;

} player_t;

typedef struct square {
    ui32 owner, last_visit;

    ui64 rank;

    struct square *parent;

} square_t;

typedef struct gamma {
    ui32 width, height, no_of_players, max_area_count, bfs_calls;

    ui64 free_squares;

    player_t *players;

    square_t **board;

} gamma_t;

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

    res->free_squares = width * height;

    res->players = calloc((players + 1), sizeof(player_t));
    if (res->players == NULL)
        return NULL;

    res->board = malloc((width + 1) * sizeof(square_t *));
    if (res->board == NULL)
        return NULL;

    for (int i = 0; i < width; i++) {
        res->board[i] = calloc((height + 1), sizeof(square_t));
        if (res->board[i] == NULL)
            return NULL;
    }

    return res;
}

void gamma_delete(gamma_t *g) {
    if (g == NULL)
        return;

    free(g->players);

    delete_2_dimension_array(g->board, g->width + 1);

    free(g);
}

square_t *find(gamma_t *g, square_t *a) {
    if (a == a->parent)
        return a;

    return a->parent = find(g, a->parent);
}

void union_squares(gamma_t *g, square_t *a, square_t *b) {
    square_t *a_rep = find(g, a);
    square_t *b_rep = find(g, b);

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

bool are_in_union(gamma_t *g, point_t a, point_t b) {
    square_t *a_square = &g->board[a.x][a.y];
    square_t *b_square = &g->board[a.x][a.y];

    return find(g, a_square) == find(g, b_square);
}

void make_union(gamma_t *g, point_t a, point_t b) {
    union_squares(g, &g->board[a.x][a.y], &g->board[b.x][b.y]);
}

bool gamma_square_out_of_bounds(gamma_t *g, point_t square) {
    if (square.x <= 0 || square.x > g->width || square.y <= 0 ||
        square.y > g->height)
        return true;
    else
        return false;
}

ui32 gamma_square_owner(gamma_t *g, point_t square) {
    if (gamma_square_out_of_bounds(g, square))
        return 0;
    else
        return g->board[square.x][square.y].owner;
}

ui32 gamma_square_last_visit(gamma_t *g, point_t square) {
    if (gamma_square_out_of_bounds(g, square))
        return g->bfs_calls;
    else
        return g->board[square.x][square.y].last_visit;
}

void gamma_increase_area_count(gamma_t *g, ui32 player) {
    g->players[player].area_count++;
}

void gamma_decrease_area_count(gamma_t *g, ui32 player) {
    g->players[player].area_count--;
}

void gamma_mark_visit(gamma_t *g, point_t square) {
    g->board[square.x][square.y].last_visit = g->bfs_calls;
}

bool gamma_recently_visited(gamma_t *g, point_t square) {
    return g->board[square.x][square.y].last_visit == g->bfs_calls;
}

void gamma_give_square_to_player(gamma_t *g, point_t square, ui32 player) {
    g->board[square.x][square.y].owner = player;
    g->board[square.x][square.y].parent = &g->board[square.x][square.y];
    g->players[player].occupied_squares++;
    g->free_squares--;
}

bool gamma_area_limit_reached(gamma_t *g, ui32 player) {
    return g->players[player].area_count >= g->max_area_count;
}

bool gamma_area_limit_exceeded(gamma_t *g, ui32 player) {
    return g->players[player].area_count > g->max_area_count;
}

bool gamma_square_adjacent_to_player(gamma_t *g, point_t square, ui32 player) {
    int target_owner_squares = 0;

    for (int i = 0; i < 4; i++)
        if (gamma_square_owner(g, point_add(square, COMPASS_ROSE[i])) == player)
            target_owner_squares++;

    return target_owner_squares != 0;
}

void update_free_adjacent(gamma_t *g, ui32 player, point_t square,
                          point_t relative_position) {
    point_t target = point_add(square, relative_position);

    if (gamma_square_owner(g, target) != 0)
        return;

    for (int i = 0; i < 4; i++)
        if (gamma_square_owner(g, point_add(target, COMPASS_ROSE[i])) == player)
            return;

    g->players[player].available_adjacent_squares++;
}

bool gamma_area_limit_allows(gamma_t *g, ui32 player, point_t square) {
    return gamma_square_adjacent_to_player(g, square, player) ||
           !gamma_area_limit_reached(g, player);
}

bool gamma_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    point_t target = make_point(x, y);

    if (g == NULL || player <= 0 || gamma_square_out_of_bounds(g, target) ||
        gamma_square_owner(g, target) != 0)
        return false;

    if (!gamma_area_limit_allows(g, player, target))
        return false;

    if (!gamma_square_adjacent_to_player(g, target, player))
        gamma_increase_area_count(g, player);

    for (int i = 0; i < 4; i++)
        update_free_adjacent(g, player, target, COMPASS_ROSE[i]);

    gamma_give_square_to_player(g, target, player);

    for (int i = 0; i < 4; i++) {
        point_t tmp = point_add(target, COMPASS_ROSE[i]);

        if (gamma_square_owner(g, tmp) == player) {
            if (!are_in_union(g, target, tmp))
                g->players[player].area_count--;

            make_union(g, target, tmp);
        }
    }
}

uint64_t gamma_busy_fields(gamma_t *g, uint32_t player) {
    if (g == NULL || player <= 0)
        return 0;

    return g->players[player].occupied_squares;
}

uint64_t gamma_free_fields(gamma_t *g, uint32_t player) {
    if (g == NULL || player <= 0)
        return 0;

    if (gamma_area_limit_reached)
        return g->players[player].available_adjacent_squares;
}

bool gamma_golden_possible(gamma_t *g, uint32_t player) {
    if (g == NULL || player <= 0)
        return false;

    if (g->players[player].spent_golden_move)
        return false;

    for (int i = 1; i <= g->no_of_players; i++)
        if (i != player && g->players[i].occupied_squares > 0)
            return true;

    return false;
}

void gamma_forget_parents_in_area(gamma_t *g, ui32 player, point_t start) {
    list_t list = list_init();
    list_add(list, start);

    g->bfs_calls++;

    point_t square;

    while (!list_empty(list)) {
        square = list_pop(list);

        g->board[square.x][square.y].parent = &g->board[square.x][square.y];

        point_t tmp;
        for (int i = 0; i < 4; i++) {
            tmp = point_add(square, COMPASS_ROSE[i]);
            if (!gamma_recently_visited(g, tmp) &&
                gamma_square_owner(g, tmp) == player) {
                list_add(list, point_add(square, COMPASS_ROSE[i]));
                gamma_mark_visit(g, tmp);
            }
        }
    }

    list_delete(list);
}

void gamma_recalc_areas_and_parents(gamma_t *g, ui32 player, point_t start) {
    list_t list = list_init();
    point_t square;
    for (int i = 0; i < 4; i++) {
        square = point_add(start, COMPASS_ROSE[i]);
        if (gamma_square_owner(g, square) == player) {
            list_add(list, square);
            gamma_increase_area_count(g, player);
        }
    }

    g->bfs_calls++;

    point_t tmp;
    while (!list_empty(list)) {
        square = list_pop(list);

        for (int i = 0; i < 4; i++) {
            tmp = point_add(square, COMPASS_ROSE[i]);

            if (gamma_square_owner(g, tmp) == player) {
                if (gamma_recently_visited(g, tmp)) {
                    if (!are_in_union(g, square, tmp)) {
                        gamma_decrease_area_count(g, player);
                        make_union(g, square, tmp);
                    }
                } else {
                    list_add(list, tmp);
                    gamma_mark_visit(g, tmp);
                }
            }
        }
    }

    list_delete(list);
}

bool gamma_golden_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    point_t target = make_point(x, y);

    if (!gamma_golden_possible(g, player) ||
        gamma_square_out_of_bounds(g, target) ||
        gamma_square_owner(g, target) == 0 ||
        gamma_square_owner(g, target) == player ||
        !gamma_area_limit_allows(g, player, target))
        return false;

    ui32 old_owner = gamma_square_owner(g, target);

    // bfs czyszczacy f&u
    gamma_forget_parents_in_area(g, player, target);

    // zwolnienie pola i zmniejszenie liczby spojnych gracza2
    g->board[x][y].owner = 0;
    gamma_decrease_area_count(g, player);

    // puszczenie bfsa naprawiajacego f&u i liczbe spojnych gracza2 na
    // sasiednich polach
    gamma_recently_visited(g, target);

    // sprawdzenie czy gracz 2 przekracza liczbe obszarow
    if (gamma_area_limit_exceeded(g, old_owner)) {
        // tak - gamma_move(pole, gracz2)
        gamma_move(g, old_owner, x, y);
    } else {
        // nie - sprawdzenie czy sasiednie pola wolne sa dalej dostepne dla
        // gracza2
        // gamma_move(pole, gracz)
        for (int i = 0; i < 4; i++) {
            point_t tmp = point_add(target, COMPASS_ROSE[i]);
            if (gamma_square_owner(g, tmp) != old_owner &&
                !gamma_square_adjacent_to_player(g, tmp, old_owner)) {
                g->players[old_owner].available_adjacent_squares--;
            }
        }

        gamma_move(g, player, x, y);
    }
}