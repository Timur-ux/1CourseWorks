#ifndef __UDT_H__
#define __UDT_H__
#include <stdbool.h>
#include <stddef.h>

typedef struct 
{
    int key;
    double value;
} data_type;

typedef struct Item
{
    data_type item;
    struct Item * front;
    struct Item * back;
} Item;

typedef struct
{
    Item *top;
    Item *bot;
    int size;
} udt;

void udt_create(udt **, data_type );
bool udt_is_empty(const udt *);
void udt_push_front(udt **, data_type);
void udt_push_back(udt **, data_type);
void udt_pop_front(udt **);
void udt_pop_back(udt **);
void udt_print(const udt *);
size_t udt_size(const udt *);
void udt_insert(udt **, const data_type);
void udt_erase(udt **, const int);
udt * sum_udt(udt *, udt *);
udt * hoar_qsort(udt *);

#endif