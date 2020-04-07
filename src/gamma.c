#include "gamma.h"

typedef uint32_t ui32;
typedef uint64_t ui64;

typedef struct point {
    ui32 x, y;
} point_t;

typedef struct player {
    ui64 occupied_area, available_adjacent_area, available_area;

    bool spent_golden_move;

} player_t;

typedef struct gamma {
    ui32 width, height, no_of_players, max_area_count;

    player_t *players;

    ui32 **board, **last_visit;

    point_t **parents;

} gamma_t;

gamma_t *gamma_new(uint32_t width, uint32_t height, uint32_t players,
                   uint32_t areas) {
    gamma_t *res = malloc(sizeof(gamma_t));

    res->width = width;
    res->height = height;
    res->no_of_players = players;
    res->max_area_count = areas;

    res->players = calloc(players, sizeof(player_t));

    res->board = new_uint32_2_dimension_array(width, height);
    res->last_visit = new_uint32_2_dimension_array(width, height);

    res->parents = malloc(width * sizeof(player_t *));
    for (int i = 0; i < width; i++)
        res->parents[i] = calloc(height * sizeof(player_t));

    return res;
}