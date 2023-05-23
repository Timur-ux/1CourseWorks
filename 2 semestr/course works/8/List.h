#ifndef _LIST_H_
#define _LIST_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct item
{
    double data;
    struct item *next;
} Item;

typedef struct 
{
    Item *node;
} Iterator;

typedef struct
{
    Item *head;
    int size;
} List;/* head(terminator) stand before first item */

void Create(List *);
Iterator First(List);/* First element of list - terminator */
Iterator Next(Iterator);
void Insert(List *, Iterator, double data);/*Insert element after element which iterator point*/
void Delete(List *, Iterator);/* Delete element after element which iterator point */
double Fetch(Iterator);
int SizeOf(List);
bool Empty(List);
bool Equal(Iterator, Iterator);
void Print(List);
void Destroy(List *);
void DestroyIfEqual(List *, double);

#endif