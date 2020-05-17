/** @file
 * Implementacja funkcji pomocniczych z pliku util.h .
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 14.04.2020
 */

#include "util.h"

point_t make_point(uint32_t x, uint32_t y) {
    point_t res;
    res.x = x;
    res.y = y;
    return res;
}

point_t point_add(point_t a, point_t b) {
    return make_point(a.x + b.x, a.y + b.y);
}

/**
 * "Róża wiatrów" - tablica zmiany współrzędnych przy poruszaniu się w kolejnych
 * kierunach.
 */
static point_t COMPASS_ROSE[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

point_t compass_rose(int i) {
    if (i < 0 || i > 3)
        return make_point(0, 0);

    return COMPASS_ROSE[i];
}

bool point_equal(point_t a, point_t b) {
    return a.x == b.x && a.y == b.y;
}

void delete_2_dimension_array(void **arr, uint32_t size) {
    if (arr == NULL)
        return;

    for (uint32_t i = 0; i < size; i++) {
        free(arr[i]);
        arr[i] = NULL;
    }

    free(arr);

    arr = NULL;
}

uint32_t get_number_length(uint32_t num) {
    uint32_t res = 1;

    while (num > 9) {
        num /= 10;
        res++;
    }

    return res;
}

char get_ith_digit_in_number(uint32_t num, uint32_t i) {
    uint32_t num_len = get_number_length(num);

    if (i >= num_len)
        return 0;

    uint32_t rev_index = num_len - i - 1;

    while (rev_index > 0) {
        num /= 10;
        rev_index--;
    }

    return '0' + num % 10;
}
