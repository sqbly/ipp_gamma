/** @file
 * Implementacja struktury listy jednokierunkowej z pliku list.h .
 *
 * @author Konrad Skublicki <ks418414@students.mimuw.edu.pl>
 * @date 14.04.2020
 */

#include "list.h"

/** Struktura przechowująca element listy.
 */
typedef struct node {
    struct node *next;  ///< wskaźnik na następny element listy
    point_t val;        ///< wartość danego elementu
} node_t;

/** Struktura przechowująca listę jednokierunkową.
 */
struct list {
    node_t *head;  ///< wskaźnik na pierwszy element listy
    node_t *back;  ///< wskaźnik na ostatni element listy
};

/** @brief Sprawdza czy udało się zaalokować pamięć.
 * Sprawdza czy @p ptr wskazuje na miejsce w pamięci.
 * Kończy działanie programu z kodem wyjścia ENOMEM jeśli @p ptr wynosi NULL.
 *
 * @param[in] ptr
 */
void check_alloc(void *ptr) {
    if (ptr == NULL)
        exit(ENOMEM);
}

list_t *list_init() {
    list_t *res = malloc(sizeof(list_t));
    check_alloc(res);

    res->head = NULL;
    res->back = NULL;

    return res;
}

void list_delete(list_t *l) {
    if (l == NULL)
        return;

    free(l);
}

bool list_empty(list_t *l) {
    if (l == NULL)
        return false;

    return l->head == NULL;
}

void list_add(list_t *l, point_t a) {
    if (l->back == NULL) {
        l->back = malloc(sizeof(node_t));
        check_alloc(l->back);
    }
    else {
        l->back->next = malloc(sizeof(node_t));
        check_alloc(l->back->next);

        l->back = l->back->next;
    }

    l->back->val = a;
    l->back->next = NULL;

    if (list_empty(l))
        l->head = l->back;
}

point_t list_pop(list_t *l) {
    if (list_empty(l))
        return make_point(0, 0);

    point_t res = l->head->val;

    node_t *tmp = l->head;

    l->head = l->head->next;

    free(tmp);

    if (l->head == NULL)
        l->back = NULL;

    return res;
}