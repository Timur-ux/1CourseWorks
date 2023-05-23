#include "List.h"

void Create(List * l)
{
    l->head = (Item *)malloc(sizeof(Item));
    l->head->next = l->head;
    l->size = 0;
}

Iterator First(List l)
{
    Iterator res = {l.head};
    return res;
}

Iterator Next(Iterator i)
{
    i.node = i.node->next;
    return i;
}


void Insert(List *l, Iterator i, double data)
{
    Iterator res = {malloc(sizeof(Item))};
    res.node->data = data;
    res.node->next = i.node->next;
    i.node->next = res.node;
    l->size++;
}

void Delete(List *l, Iterator i)
{
    if(Equal(Next(i), First(*l)))
    {
        Delete(l, Next(i));
        return;
    }
    Iterator ItemToDel = Next(i);
    i.node->next = ItemToDel.node->next;
    l->size--;
    free(ItemToDel.node);
}

double Fetch(Iterator i)
{
    return i.node->data;
}

int SizeOf(List l)
{
    return l.size;
}

bool Empty(List l)
{
    return Equal(First(l), Next(First(l)));
}

bool Equal(Iterator a, Iterator b)
{
    return a.node == b.node;
}

void Print(List l)
{
    printf("[ ");
    for(Iterator i = Next(First(l)); !Equal(i, First(l)); i = Next(i))
    {
        printf("%lf ", Fetch(i));
    }
    printf("]\n");
}

void Destroy(List *l)
{
    int lsize = SizeOf(*l);
    for(int i = 0; i < lsize; i++)
    {
        Delete(l, First(*l));
    }
}

void DestroyIfEqual(List *l, double key)
{
    for(Iterator i = Next(First(*l)); !Equal(i, First(*l)); i = Next(i))
    {
        if(Fetch(i) == key)
        {
            printf("Key was found in list. So list will be destroyed\n");
            Destroy(l);
            return;
        }
    }
    printf("Key wasn't found. So list hasn't changed\n");
}