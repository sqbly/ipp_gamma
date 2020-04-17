/** @file
 * Implementacja funkcji pomocniczych z pliku util.h .
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 14.04.2020
 */

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
    if (i < 0 || i > 3)
        return make_point(0, 0);

    point_t COMPASS_ROSE[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    return COMPASS_ROSE[i];
}

bool point_equal(point_t a, point_t b) {
    return a.x == b.x && a.y == b.y;
}

void delete_2_dimension_array(void **arr, ui32 size) {
    if (arr == NULL)
        return;

    for (ui32 i = 0; i < size; i++) {
        free(arr[i]);
        arr[i] = NULL;
    }

    free(arr);

    arr = NULL;
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

    if (i >= num_len)
        return 0;

    ui32 rev_index = num_len - i - 1;

    while (rev_index > 0) {
        num /= 10;
        rev_index--;
    }

    return '0' + num % 10;
}
