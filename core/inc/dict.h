#pragma once

#include <stdint.h>

typedef struct dict_node
{
    int key;
    void *value;
}
dict_node;

typedef struct dict
{
    dict_node *nodes;
    size_t type;
    int count;
}
dict;

dict *dict_new(size_t t);

void dict_free(dict *d);

void dict_node_free(dict_node *dn);

void dict_append(dict *d, int key, void *value);

dict_node *dict_at(dict *d, int index);

dict_node *dict_last(dict *d);

dict_node *dict_by_key(dict *d, int key);

int valid_index(dict *d, int index);

void *dict_value_at(dict *d, int index);

void *dict_value_by_key(dict *d, int key);

int dict_contains_key(dict *d, int key);

int dict_remove(dict *d, int key);