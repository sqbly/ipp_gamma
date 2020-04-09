#ifndef LIST_H
#define LIST_H

#include <errno.h>

#include "util.h"

typedef struct node node_t;

struct list {
    node_t *head;
    node_t *back;
};

typedef struct list *list_t;

list_t list_init();

void list_delete(list_t l);

bool list_empty(list_t l);

void list_add(list_t l, point_t a);

point_t list_pop(list_t l);

#endif