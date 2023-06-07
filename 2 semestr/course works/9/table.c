#include "Table.h"
#include <stdio.h>
#include <string.h>

void Create(Table * l)
{
    l->head = (Item*)malloc(sizeof(Item)*100);
    l->size = 0;
    return;
}


void Swap(Item* a, Item* b)
{
    Item *temp = (Item*)malloc(sizeof(Item));
    temp->key = malloc(sizeof(char)*(strlen(a->key)+1));
    memcpy(temp->key, a->key, strlen(a->key)+1);
    temp->data = a->data;
    memcpy(a->key, b->key, strlen(b->key)+1);
    a->data = b->data;
    memcpy(b->key, temp->key, strlen(temp->key)+1);
    b->data = temp->data;
    return;
}

void add(Table *l, char *key, int data)
{
    Item res;
    res.key = (char*)malloc(sizeof(char)*strlen(key)+1);
    memcpy(res.key, key, strlen(key));
    res.key[strlen(key)] = '\0';
    res.data = data;
    l->head[l->size] = res;
    l->size++;
    return;
}
int getValue(char* key)
{
    int res = 0;
    for(int i = 0; i < strlen(key); i++)
    {
        res += (int)key[i];
    }
    return res;
}
Item * min(Table *T, int start)
{
    Item *min = &(T->head[start]);
    for(int i = start+1; i < T->size; i++)
    {
        if(getValue(T->head[i].key) < getValue(min->key))
        {
            min = &(T->head[i]);
        }
    }
    return min;
}
void LinChangeSort(Table *T)
{
    for(int i = 0; i < T->size; i++)
    {
        Item* Min = min(T, i);
        Swap(&(T->head[i]), Min);
    }
    return;
}
void print(Table T)
{
    printf("---------------------------------\n");
    for(int i = 0; i < T.size; i++)
    {
        printf("|\t%s\t|\t%d\t|\n", T.head[i].key, T.head[i].data);
    }
    printf("---------------------------------\n");
    return;
}
int search(Table T, char*key)
{
    int l = 0, r = T.size;
    while(l <= r)
    {
        int m = (l+r)/2;
        if(getValue(T.head[m].key) == getValue(key))
        {
            return T.head[m].data;
        }
        if(getValue(T.head[m].key) < getValue(key))
        {
            l = m+1;
        }
        else
        {
            r = m-1;
        }
    }
    return -1e9;
}