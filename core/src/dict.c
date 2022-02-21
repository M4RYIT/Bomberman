#include "dict.h"
#include <string.h>
#include <stdlib.h>

dict *dict_new(size_t t)
{
    dict *d = malloc(sizeof(dict));
    if (!d) return NULL;

    d->type = t;
    d->count = 0;
    d->nodes = NULL;
    return d;
}

void dict_free(dict *d)
{
    for (int i=0; i<d->count; i++)
    {
        dict_node_free(d->nodes+i);
    }
    d->count = 0;
    
    free(d->nodes);    
    free(d);
}

void dict_node_free(dict_node *dn)
{
    dn->key = -1;
    free(dn->value);
}

void dict_append(dict *d, int key, void *value)
{
    d->nodes = realloc(d->nodes, sizeof(dict_node) * (d->count+1));
    d->nodes[d->count].key = key;
    d->nodes[d->count].value = value;
    d->count++;
}

dict_node *dict_at(dict *d, int index)
{
    if (!valid_index(d, index)) return NULL;

    return d->nodes + index;
}

void *dict_value_at(dict *d, int index)
{
    dict_node *dn = dict_at(d, index);
    if (!dn) return NULL;

    return dn->value;
}

int valid_index(dict *d, int index)
{
    if (index < 0 || index >= d->count) return 0;

    return 1;
}

dict_node *dict_last(dict *d)
{
    return dict_at(d, d->count-1);
}

dict_node *dict_by_key(dict *d, int key)
{
    for (int i=0; i<d->count; i++)
    {
        if (d->nodes[i].key == key) return (d->nodes+i);
    }

    return NULL;
}

void *dict_value_by_key(dict *d, int key)
{
    dict_node *dn = dict_by_key(d, key);
    return (dn)? dn->value : NULL;
}

int dict_contains_key(dict *d, int key)
{
    for (int i=0; i<d->count; i++)
    {
        if (d->nodes[i].key == key) return 1;
    }

    return 0;
}

int dict_remove(dict *d, int key)
{
    for (int i=0; i<d->count; i++)
    {
        if (d->nodes[i].key == key)
        {
            dict_node_free(d->nodes+i);

            if (i<d->count-1) memmove(d->nodes+i, d->nodes+i+1, (d->count-1-i)*sizeof(dict_node));

            d->count--;
            return 1;
        }
    }

    return 0;
}