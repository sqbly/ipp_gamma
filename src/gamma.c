#include "gamma.h"

typedef struct player {
    ui64 occupied_squares, available_adjacent_squares, area_count;

    bool spent_golden_move;

} player_t;

typedef struct gamma {
    ui32 width, height, no_of_players, max_area_count;

    ui64 free_squares;

    player_t *players;

    ui32 **board, **last_visit;

    point_t **parents;

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

    res->free_squares = width * height;

    res->players = calloc((players + 1), sizeof(player_t));
    if (res->players == NULL)
        return NULL;

    res->board = new_uint32_2_dimension_array(width + 1, height + 1);
    res->last_visit = new_uint32_2_dimension_array(width + 1, height + 1);

    res->parents = malloc((width + 1) * sizeof(point_t *));
    if (res->board == NULL || res->last_visit == NULL || res->parents == NULL)
        return NULL;

    for (int i = 0; i < width; i++) {
        res->parents[i] = calloc((height + 1), sizeof(point_t));
        if (res->parents[i] == NULL)
            return NULL;
    }

    return res;
}

void gamma_delete(gamma_t *g) {
    if (g == NULL)
        return;

    free(g->players);

    delete_2_dimension_array(g->board, g->width + 1);
    delete_2_dimension_array(g->last_visit, g->width + 1);
    delete_2_dimension_array(g->parents, g->width + 1);

    free(g);
}

void union_squares(gamma_t *g, point_t a, point_t b);

point_t find(gamma_t *g, point_t a);

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
        return g->board[square.x][square.y];
}

void update_free_adjacent(gamma_t *g, ui32 player, point_t square,
                          point_t relative_position) {
    point_t target = add_points(square, relative_position);

    if (gamma_square_owner(g, target) != 0)
        return;

    for (int i = 0; i < 4; i++)
        if (gamma_square_owner(g, add_points(target, COMPASS_ROSE[i])) ==
            player)
            return;

    g->players[player].available_adjacent_squares++;
}

void gamma_increase_area_count(gamma_t *g, uint32_t player) {
    g->players[player].area_count++;
}

void gamma_give_square_to_player(gamma_t *g, point_t square, uint32_t player) {
    g->board[square.x][square.y] = player;
    g->players[player].occupied_squares++;
}

bool gamma_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y) {
    point_t target = make_point(x, y);

    if (g == NULL || player <= 0 || gamma_square_out_of_bounds(g, target) ||
        gamma_square_owner(g, target) != 0)
        return false;

    int same_owner_squares = 0;

    for (int i = 0; i < 4; i++)
        if (gamma_square_owner(g, add_points(target, COMPASS_ROSE[i])) ==
            player)
            same_owner_squares++;

    if (same_owner_squares == 0)
        if (g->players[player].area_count >= g->max_area_count)
            return false;

    gamma_increase_area_count(g, player);

    for (int i = 0; i < 4; i++)
        update_free_adjacent(g, player, target, COMPASS_ROSE[i]);

    gamma_give_square_to_player(g, target, player);

    point_t tmp, par1, par2;
    for (int i = 0; i < 4; i++) {
        tmp = add_points(target, COMPASS_ROSE[i]);
        if (gamma_square_owner(g, tmp) == player) {
            par1 = find(g, target);
            par2 = find(g, tmp);

            if (!point_equal(par1, par2))
                g->players[player].area_count--;

            union_squares(g, target, tmp);
        }
    }
}