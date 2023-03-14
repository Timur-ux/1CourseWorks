#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct tree
{
    char* val;//'0' is number, '1' is letter, '+' or '-' or '/'... is operation
    struct tree* left;
    struct tree* right;
    struct tree* parent;
} Node;

Node * createNode(const char * val)
{
    Node * result = malloc(sizeof(Node));
    result->parent = NULL;
    result->left = NULL;
    result->right = NULL;
    result->val = malloc((strlen(val)+1)*sizeof(char));
    memcpy(result->val, val, strlen(val)+1);
    return result;
}

typedef struct stack
{
    char * val;
    struct stack *prev;
} Stack;

Stack * create_stack(const char *val)
{
    Stack *result = malloc(sizeof(Stack));
    result->val = malloc(sizeof(char)*strlen(val)+1);
    memcpy(result->val, val, strlen(val)*sizeof(char)+1);
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
    result->val = malloc(sizeof(char)*strlen(val)+1);
    memmove(result->val, val, strlen(val)+1);
    result->prev = *source;
    (*source) = result;
}

const char * Pop(Stack **source)//pop first element from stack and return his value.
{
    char * result = malloc(strlen((*source)->val)+1);
    memcpy(result, (*source)->val, strlen((*source)->val)+1);
    Stack * prev = (*source)->prev;
    free((*source));
    (*source) = prev;
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

const char * slice(const char * s, int a, int b)
{
    int len = b-a;
    char * result = malloc(len+1);
    memcpy(result, s+a, len);
    *(result+len) = 0;
    return result;
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

void stringToStack(Stack **stack, const char *s)
{
    int begin = 0;
    for(unsigned int i = 0; i < strlen(s)+1; i++)
    {
        
        if(*(s+i) == ' ' || *(s+i) == '\0')
        {
            Push(stack, slice(s, begin, i));
            begin = i + 1;
        }
    }
}

Stack * copyStack(Stack *stack)
{
    if(stack == NULL)
    {
        return NULL;
    }
    Stack * result = malloc(sizeof(Stack));
    result->val = malloc(strlen(stack->val)+1);
    memcpy(result->val, stack->val, strlen(stack->val)+1);
    result->prev = copyStack(stack->prev);
    return result;
}
Stack * findLower(Stack *stack)
{
    while(*stack->prev->val != '(')
    {
        stack = stack->prev;
    }
    return stack->prev;
}
int in(char el, const char * s)
{
    for(int i = 0; i < strlen(s); i++)
    {
        if(*(s+i) == el)
        {
            return 1;
        }
    }
    return 0;
}
Stack * convToPrefForm(Stack *stack)
{
    Stack * result = NULL;
    const char * val;
    Stack * cur_stack = copyStack(stack);
    while(1)
    {
        if(cur_stack == NULL)
        {
            return result;
        }
        val = Pop(&cur_stack);
        if(in(*val, "+-*/"))
        {
            Push(&result, val);
        }
        else if(*val == ')')
        {
            Stack * temp_stack = cur_stack;
            cur_stack = (findLower(cur_stack))->prev;
            Stack * inner_stack = convToPrefForm(temp_stack);
            if(result == NULL)
            {
                sumStacks(inner_stack, result);
                result = inner_stack;
            }
            else
            {
                const char * op = Pop(&result);
                sumStacks(inner_stack, result);
                result = inner_stack;
                Push(&result, op);
            }
        }
        else if (*val == '(')
        {
            return result;
            
        }
        else
        {
            if(result == NULL)
            {
                Push(&result, val);
            }
            else
            {
                const char * op = Pop(&result);
                Push(&result, val);
                Push(&result, op);
            }
        }
    }
}

Node * PrefStackToTree(Stack * stack)
{
    const char *val = Pop(&stack);
    Node * result = create_stack(val);
    Node * cur_node = result;
    while(stack != NULL)
    {
        val = Pop(&stack);
        if(in(*val, "+-*/"))
        {
                if(cur_node->left == NULL)
                {
                    cur_node->left = malloc(sizeof(Node));
                    cur_node->left->left = NULL;
                    cur_node->left->right = NULL;
                    cur_node->left->parent = cur_node;
                    cur_node = cur_node->left;
                    cur_node->val = malloc(sizeof(char)*(strlen(val)+1));
                    memcpy(cur_node->val, val, strlen(val)+1);
                }
                else
                {
                    cur_node->right = malloc(sizeof(Node));
                    cur_node->right->left = NULL;
                    cur_node->right->right = NULL;
                    cur_node->right->parent = cur_node;
                    cur_node = cur_node->right;
                    cur_node->val = malloc(sizeof(char)*(strlen(val)+1));
                    memcpy(cur_node->val, val, strlen(val)+1);
                }
        }
        else
        {
            if()
        }
    }
}

int main()
{
    const char *s = "( 2 + 3 - 333 ) * k";
    Stack * stack = NULL;
    stringToStack(&stack, s);
    stack = convToPrefForm(stack);
    printStack(stack);
    return 0;
}
