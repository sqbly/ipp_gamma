#include "list.h"

typedef struct node {
    struct node *next;
    point_t val;
} node_t;

void check_alloc(void *ptr) {
    if (ptr == NULL)
        exit(ENOMEM);
}

list_t list_init() {
    list_t res = malloc(sizeof(list_t));
    check_alloc(res);

    res->head = NULL;
    res->back = NULL;

    return res;
}

void list_delete(list_t l) {
    if (l == NULL)
        return;

    free(l);
}

bool list_empty(list_t l) {
    return l->head == NULL;
}

void list_add(list_t l, point_t a) {
    if (l->back == NULL) {
        l->back = malloc(sizeof(node_t *));
        check_alloc(l->back);
    } else {
        l->back->next = malloc(sizeof(node_t *));
        check_alloc(l->back->next);

        l->back = l->back->next;
    }

    l->back->val = a;
    l->back->next = NULL;

    if (list_empty(l))
        l->head = l->back;
}

point_t list_pop(list_t l) {
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