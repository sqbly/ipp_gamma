/** @file
 * Implementacja struktury listy jednokierunkowej z pliku list.h .
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 14.04.2020
 */

#include "list.h"

/** Struktura przechowująca listę jednokierunkową.
 */
struct list {
    uint64_t size;   ///< zaalokowany rozmiar listy
    uint64_t head;   ///< indeks pierwszego zajętego elementu
    uint64_t tail;   ///< indeks następnego wolnego elementu
    point_t *nodes;  ///< tablica przechowująca elementy listy
};

list_t *list_init(uint64_t size) {
    list_t *res = malloc(sizeof(list_t));
    if (res == NULL)
        return NULL;

    res->size = size;
    res->head = 0;
    res->tail = 0;
    res->nodes = calloc(size, sizeof(point_t));
    if (res->nodes == NULL) {
        free(res);
        return NULL;
    }

    return res;
}

void list_delete(list_t *l) {
    if (l == NULL)
        return;

    free(l->nodes);
    l->nodes = NULL;

    free(l);
    l = NULL;
}

bool list_empty(list_t *l) {
    if (l == NULL)
        return false;

    return l->head == l->tail;
}

void list_add(list_t *l, point_t a) {
    l->nodes[l->tail] = a;

    l->tail++;
    if (l->tail == l->size)
        l->tail = 0;
}

point_t list_pop(list_t *l) {
    if (list_empty(l))
        return make_point(UINT32_MAX, UINT32_MAX);

    point_t res = l->nodes[l->head];

    l->head++;
    if (l->head == l->size)
        l->head = 0;

    return res;
}