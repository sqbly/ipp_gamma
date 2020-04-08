#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t ui32;
typedef uint64_t ui64;

typedef struct point {
    ui32 x, y;
} point_t;

point_t make_point(ui32 x, ui32 y);

point_t COMPASS_ROSE[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

point_t add_points(point_t a, point_t b);

bool point_equal(point_t a, point_t b);

point_t point_above(point_t p);

point_t point_below(point_t p);

point_t point_to_right(point_t p);

point_t point_to_left(point_t p);

uint32_t **new_uint32_2_dimension_array(uint32_t width, uint32_t height);

void delete_2_dimension_array(void **arr, ui32 size);
