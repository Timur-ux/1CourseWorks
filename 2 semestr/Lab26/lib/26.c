#include <stdio.h>
#include <malloc.h>
#include "26.h"
#include <stdlib.h>

void udt_create(udt ** dek, data_type item)
{
    udt * result = malloc(sizeof(udt));
    Item *it = malloc(sizeof(Item));
    it->item = item;
    it->back = NULL;
    it->front = NULL;
    result->top = it;
    result->bot = it;
    result->size = 1;
    (*dek) = result;
}

bool udt_is_empty(const udt * dek)
{
    return dek == NULL;
}

void udt_pop_front(udt ** dek)
{
    udt * cur_dek = (*dek);
    if(udt_is_empty(cur_dek))
    {
        return;
    }
    if(cur_dek->top->back == cur_dek->bot->front)
    {
        (*dek) = NULL;
        free(cur_dek);
    }
    else
    {
        Item * top = cur_dek->top;
        cur_dek->top = cur_dek->top->back;
        cur_dek->top->front = NULL;
        free(top);
        cur_dek->size--;
    }
}

void udt_pop_back(udt ** dek)
{
    udt * cur_dek = (*dek);
    if(udt_is_empty(cur_dek))
    {
        return;
    }
    if(cur_dek->top->back == cur_dek->bot->front)
    {
        (*dek) = NULL;
        free(cur_dek);
    }
    else
    {
        Item * bot = cur_dek->bot;
        cur_dek->bot = cur_dek->bot->front;
        cur_dek->bot->back = NULL;
        free(bot);
        cur_dek->size--;
    }
}

void udt_push_front(udt ** dek, data_type item)
{
    udt * cur_dek = (*dek);
    if(udt_is_empty(cur_dek))
    {
        udt * result;
        udt_create(&result, item);
        (*dek) = result;
        return;
    }
    Item * old_top = cur_dek->top;
    cur_dek->top = malloc(sizeof(Item));
    cur_dek->top->item = item;
    cur_dek->top->front = NULL;
    cur_dek->top->back = old_top;
    old_top->front = cur_dek->top;
    (*dek) = cur_dek;
    (*dek)->size++;
}
void udt_push_back(udt ** dek, data_type item)
{
    udt * cur_dek = (*dek);
    if(udt_is_empty(cur_dek))
    {
        udt * result;
        udt_create(&result, item);
        (*dek) = result;
        return;
    }
    Item * old_bot = cur_dek->bot;
    cur_dek->bot = malloc(sizeof(Item));
    cur_dek->bot->item = item;
    cur_dek->bot->back = NULL;
    cur_dek->bot->front = old_bot;
    old_bot->back = cur_dek->bot;
    (*dek) = cur_dek;
    (*dek)->size++;
}

void udt_print(const udt * dek)
{
    if(udt_is_empty(dek))
    {
        return;
    }
    Item *it = dek->top; 
    do
    {
        printf("value: %f, key: %d\n", it->item.value, it->item.key);
        it = it->back;
    } while (it != NULL);
}

size_t udt_size(const udt * dek)
{
    if(udt_is_empty(dek))
    {
        return 0;
    }
    return dek->size;
}

void udt_insert(udt ** dek, const data_type item)
{
    udt_push_front(dek, item);
}

void udt_erase(udt ** dek, const int key)
{
    if(udt_size((*dek)) == 1)
    {
        if((*dek)->top->item.key == key)
        {
            udt * temp = (*dek);
            (*dek) = NULL;
            free(temp);
        }
    }
    else
    {
        Item * cur_dek = (*dek)->bot;
        do
        {
            if(cur_dek->item.key == key)
            {
                Item * temp = cur_dek;
                cur_dek = cur_dek->front;
                cur_dek->back = cur_dek->back->back;
                free(temp);
                (*dek)->size--;
            }
            else
            {
                cur_dek = cur_dek->front;
            }
        } while (cur_dek->front != NULL);   
    }
}

udt * sum_udt(udt * a, udt * b)//put dek a over dek b and return pointer on top of dek a
{
    if(udt_is_empty(a))
    {
        return b;
    }
    if(udt_is_empty(b))
    {
        return a;
    }
    a->bot->back = b->top;
    b->top->front = a->bot;
    a->bot = b->bot;
    return a;
}

udt * hoar_qsort(udt * dek)
{
    if(udt_size(dek) < 2)
    {
        return dek;
    }
    udt * high = NULL;
    udt * low = NULL;
    udt * equal = NULL;
    Item *it = dek->top;
    udt_push_front(&equal, it->item);
    while(it->back != NULL)
    {
        it = it->back;
        if(it->item.value > equal->top->item.value)
        {
            udt_push_front(&high, it->item);
        }
        else if(it->item.value < equal->top->item.value)
        {
            udt_push_front(&low, it->item);
        }
        else
        {
            udt_push_front(&equal, it->item);
        }
    }
    return sum_udt(sum_udt(hoar_qsort(high), equal), hoar_qsort(low));
}
