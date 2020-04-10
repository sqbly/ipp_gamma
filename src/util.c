#include "util.h"

point_t make_point(ui32 x, ui32 y) {
    point_t res;
    res.x = x;
    res.y = y;
    return res;
}

point_t point_add(point_t a, point_t b) {
    return make_point(a.x + b.x, a.y + b.y);
}

point_t compass_rose(int i) {
    const point_t COMPASS_ROSE[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    return COMPASS_ROSE[i];
}

bool point_equal(point_t a, point_t b) {
    return a.x == b.x && a.y == b.y;
}

point_t point_above(point_t p) {
    p.y++;
    return p;
}

point_t point_below(point_t p) {
    p.y--;
    return p;
}

point_t point_to_right(point_t p) {
    p.x++;
    return p;
}

point_t point_to_left(point_t p) {
    p.y--;
    return p;
}

ui32 **new_uint32_2_dimension_array(ui32 width, ui32 height) {
    ui32 **res = malloc(width * sizeof(ui32 *));
    if (res == NULL)
        return NULL;

    for (ui32 i = 0; i < width; i++) {
        res[i] = calloc(height, sizeof(ui32));
        if (res[i] == NULL)
            return NULL;
    }

    return res;
}

void delete_2_dimension_array(void **arr, ui32 size) {
    if (arr == NULL)
        return;

    for (ui32 i = 0; i < size; i++) {
        if (arr[i] != NULL)
            free(arr[i]);
    }

    free(arr);
}

ui32 get_number_length(ui32 num) {
    ui32 res = 1;

    while (num > 9) {
        num /= 10;
        res++;
    }

    return res;
}

char get_ith_digit_in_number(ui32 num, ui32 i) {
    ui32 num_len = get_number_length(num);
    ui32 rev_index = num_len - i - 1;

    while (rev_index > 0) {
        num /= 10;
        rev_index--;
    }

    return num % 10;
}
