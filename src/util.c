#include "util.h"

uint32_t **new_uint32_2_dimension_array(uint32_t width, uint32_t height) {
    uint32_t **res = malloc(width * sizeof(uint32_t *));
    for (int i = 0; i < width; i++)
        res[i] = calloc(height * sizeof(uint32_t));

    return res;
}