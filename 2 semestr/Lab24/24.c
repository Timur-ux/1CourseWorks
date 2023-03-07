#include <stdio.h>
#include <malloc.h>
#include <string.h>

// typedef struct tree
// {
//     char* val;//'0' is number, '1' is letter, '+' or '-' or '/'... is operation
//     struct tree* left;
//     struct tree* right;
//     struct tree* parent;
// } Node;

typedef struct stack
{
    char * val[10];
    struct stack *prev;
} Stack;

Stack * create_stack(char *val[])
{
    Stack *result = malloc(sizeof(Stack));
    memcpy(result->val, val, strlen(val));
    result->prev = NULL;
    return result;
}

Stack * Push(Stack *source, char * val[])
{
    Stack *result = malloc(sizeof(Stack));
    memcpy(result->val, val, strlen(val));
    result->prev = source;
    return result;
}

const char * Pop(Stack **source)
{
    char * result;
    memcpy(result, (**source)->val, sizeof((**source)->val));
    (*source) = (**sorce)->prev;
    return result;
}

char * getword(char * s)
{
    i = 0;
    while(*(s+i+1) != ' ' || *(s+i+1) != '\n')
    {
        i++;
    }
    char * result;
    memcpy(result, s, i);
    return result;
}

Stack * string2Stack(char * s[])
{
    return NULL;
}

int main()
{
    return 0;
}