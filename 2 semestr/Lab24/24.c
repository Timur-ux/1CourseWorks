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
    char * val;
    struct stack *prev;
} Stack;

Stack * create_stack(const char *val)
{
    Stack *result = malloc(sizeof(Stack));
    memcpy(result->val, val, strlen(val)*sizeof(char));
    result->prev = NULL;
    return result;
}

void Push(Stack **source, const char * val)// push new value on stack top;
{
    if(*source == NULL)
    {
        (*source) = create_stack(val);
        return;
    }
    Stack *result = malloc(sizeof(Stack));
    memmove(result->val, val, strlen(val)*sizeof(char));
    result->prev = *source;
    (*source) = result;
}

const char * Pop(Stack **source)//pop first element from stack and return his value.
{
    char * result;
    memcpy(result, (*source)->val, strlen((*source)->val));
    (*source) = (*source)->prev;
    return result;
}

void printStack(Stack * stack)//Print stack from up to down.
{  
    while(stack != NULL)
    {
        printf("%s\n", stack->val);
        stack = stack->prev;
    }
    return;
}

void sumStacks(Stack * A, Stack * B)//place stack A on stack B(A above B).
{
    Stack * cur_stack = A;
    while(cur_stack->prev != NULL)
    {
        cur_stack = cur_stack->prev;
    }
    cur_stack->prev = B;
}

// int isOperand(const char * s)//return 1 if s is number or letter, return 0 otherwise
// {
//     if(*s[0] == '+' || *s[0] == '-' || *s[0] == '/' || *s[0] == '*')
//     {
//         return 0;
//     }
//     return 1;
// }
const char * slice(const char * s, int a, int b)
{
    int len = b - a;
    char * result;
    memmove(result, s+a, len);
    return result;
}

void string2Stack(Stack ** dest, const char *s)
{
    int begin = 0;
    printf("%s\n", slice(s, 0, 1));
    for(int i = 0; i < strlen(s)+1; i++)
    {
        if(*(s+i) == ' ' || *(s+i) == '\0')
        {
            // Push(dest, slice(s, begin, i));
            begin = i + 1;
        }
    }
}





int main()
{
    const char *ss = "2 + 3";
    printf("%s\n", slice(ss, 0, 1));
    Stack * stack = create_stack(ss);
    string2Stack(&stack, ss);
    //printStack(stack);
    return 0;
}
//Какая-то лажа в slice когда она вызывается из функции. При вызове из main работает нормально.
