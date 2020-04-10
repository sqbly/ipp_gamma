#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t ui32;
typedef uint64_t ui64;

typedef struct point {
    ui32 x, y;
} point_t;

point_t make_point(ui32 x, ui32 y);

point_t point_add(point_t a, point_t b);

point_t compass_rose(int i);

bool point_equal(point_t a, point_t b);

point_t point_above(point_t p);

point_t point_below(point_t p);

point_t point_to_right(point_t p);

point_t point_to_left(point_t p);

uint32_t **new_uint32_2_dimension_array(uint32_t width, uint32_t height);

void delete_2_dimension_array(void **arr, ui32 size);

ui32 get_number_length(ui32 num);

char get_ith_digit_in_number(ui32 num, ui32 i);

#endif