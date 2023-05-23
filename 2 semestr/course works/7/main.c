#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct it
{
    double data;
    int col;
    int nextIndex;
    struct it *prev;
    struct it *next;
} Item_l;


typedef struct
{
    Item_l *first;
    Item_l *last;
} List;

void Create(List* l)
{
    l->first = l->last = (Item_l*)malloc(sizeof(Item_l));
    l->last->prev = l->first;
    l->last->next = l->first;
}
void Add(List *l, int column, double data, int nextIndex)
{
    Item_l *last = l->last;
    l->last = (Item_l*)malloc(sizeof(Item_l));
    l->last->data = data;
    l->last->col = column;
    l->last->nextIndex = nextIndex;
    l->last->prev = last;
    last->next = l->last;
}
bool Empty(List l)
{
    return l.first == l.last;
}

Item_l* getKthEl(List *l, List *m, int index)
{
    Item_l* indLine = m->first->next;
    int curInd = indLine->col;
    for(Item_l *it = l->first->next; it != l->last->next; it = it->next)
    {
        if(curInd > index)
        {
            return NULL;
        }
        if(curInd == index)
        {
            return it;
        }
        if(it->nextIndex == 0)
        {
            indLine = indLine->next;
            curInd = indLine->col;
        }
        else
        {
            curInd = it->nextIndex;
        }
    }
    return NULL;
}
int main()
{
    FILE *input = fopen("input.txt", "r");
    int m, n;
    fscanf(input, "%d %d", &m, &n);
    double c;
    List M; Create(&M);
    List A; Create(&A);
    int curA = 0, curM = 0;
    for(int i = 0; i < m; i++)
    {
        bool beginned = false;
        for(int j = 0; j < n; j++)
        {
            int temp;
            fscanf(input, "%d", &temp);
            c = (double)temp;
            if(c != 0)
            {
                Add(&A, j, c, 0);
                if(!Empty(A) && beginned)
                {
                    A.last->prev->nextIndex = n*i+j;
                }
                if(!beginned)
                {
                    Add(&M, i*n+j, 0, 0);
                    beginned = true;
                }
            }
            else
            {
                continue;
            }
        }
    }/* Collect input data from file */
    for(Item_l *it = A.first->next; it != A.last->next; it = it->next)
    {
        printf("%lf ", it->data);
    }
    printf("\n--------------\n");
    int Max = 0;
    for(Item_l *it = A.first->next; it != A.last->next; it = it->next)
    {
        if(abs(it->data) > abs(Max))
        {
            Max = it->data;
        }
    }/* find Max el by abs */
    if(Max != 0)
    {
        Item_l *indLine = M.first->next;
        for(Item_l *it = A.first->next; it != A.last->next; it = it->next)
        {
            if(it->data == Max)
            {
                Item_l *it2 = getKthEl(&A, &M, indLine->col);
                if(it2 == NULL)
                {
                    printf("ERROR: wrong line begining\n");
                }       
                while(it2->nextIndex != 0)
                {
                    it2->data /= Max;
                    it2 = it2->next;
                }
                it2->data /= Max;
                it = it2;
            }
            if(it->nextIndex == 0)
            {
                indLine = indLine->next;
            }
        }
    }
    for(Item_l *it = A.first->next; it != A.last->next; it = it->next)
    {
        printf("%f ", it->data);
    }
    
}