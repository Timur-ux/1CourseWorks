#ifndef _TABLE_H_
#define _TABLE_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// typedef struct item
// {
//     char * key;
//     int data;
//     struct item *next;
// } Item;

typedef struct
{
    char * key;
    int data;
} Item;

// typedef struct 
// {
//     Item *node;
// } Iterator;

typedef struct
{
    int size;
    Item *head;
} Table;/* head(terminator) stand before first item */

void Create(Table *);
// Iterator First(Table);/* First element of Table - terminator */
// Iterator Next(Iterator);
// void Insert(Table *, Iterator, char *key, int data);/*Insert element after element which iterator point*/
// void Delete(Table *, Iterator);/* Delete element after element which iterator point */
// int FetchData(Iterator);
// char * FetchKey(Iterator);
// int SizeOf(Table);
// bool Empty(Table);
// bool Equal(Iterator, Iterator);
// void Print(Table);
// void Destroy(Table *);
// Item_arr* LinChangeSort(Table *);
// Iterator findMin(Iterator a, Iterator b);
// void Swap(Iterator a, Iterator b);
// int Find
int getValue(char*);
void add(Table *, char *, int);
void Swap(Item *, Item *);
Item * min(Table *, int);
void LinChangeSort(Table *);
void print(Table);
int search(Table, char *);
#endif