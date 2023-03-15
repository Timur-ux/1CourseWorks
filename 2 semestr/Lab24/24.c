#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef union val
{
    char op;
    char let;
    char bracket;
    int num;
} value;

typedef enum {op, let, bracket, num} type;

typedef struct el
{
    value val;
    type T;
} El;

typedef struct tree
{
    El el;
    struct tree* left;
    struct tree* right;
    struct tree* parent;
} Node;

El createEl(value val, type T)
{
    El result;
    switch (T)
    {
        case (op):
        {
            result.val = val.op;
            break;
        }
        case (let):
        {
            result.val = val.let;
            break;
        }
        case (num):
        {
            result.val = val.num;
            break;
        }
        case (bracket):
        {
            result.val = val.bracket;
            break;
        }
        default:
        {
            printf("ERROR: undefined input data in function 'createEl'\n");
            break;
        }
    }
    result.T = T;
    return result;
}

Node * createNode(value val, type T)
{
    Node * result = malloc(sizeof(Node));
    result->parent = NULL;
    result->left = NULL;
    result->right = NULL;
    result->el = createEl(val, T);
    return result;
}
void printEl(El el)
{
    switch (el.T)
    {
        case (op):
        {
            printf("%c\n", el.val);
            break;
        }
        case (let):
        {
            printf("%c\n", el.val);
            break;
        }
        case (bracket):
        {
            printf("%c\n", el.val)
        }
        case (num):
        {
            printf("%d\n", el.val);
            break;
        }
        default:
        {
            printf("ERROR: undefined input data in function 'printEl'\n");
            break;
        }
    }
}
void printTree(Node* node, int depth)
{
    if(node->right != NULL)
    {
        printTree(node->right, depth+1);
    }
    for(int i = 0; i < depth; i++)
    {
        printf("\t");
    }
    printEl(node->el);
    if(node->left != NULL)
    {
        printTree(node->left, depth+1);
    }
}

typedef struct stack
{
    El el;
    struct stack *prev;
} Stack;

int in(char el, const char * s)
{
    for(unsigned int i = 0; i < strlen(s); i++)
    {
        if(*(s+i) == el)
        {
            return 1;
        }
    }
    return 0;
}

int isDigit(const char * val)
{
    if(*val == '0' || atoi(val) != 0)
    {
        return 1;
    }
    return 0;
}
Stack * create_stack(value val, type T)
{
    Stack *result = malloc(sizeof(Stack));
    result->el = createEl(val, T);
    result->prev = NULL;
    return result;
}

void Push(Stack **source, El el)// push new value on stack top;
{
    if(*source == NULL)
    {
        (*source) = create_stack(el.val, el.T);
        return;
    }
    Stack *result = malloc(sizeof(Stack));
    result->el = el;
    result->prev = *source;
    (*source) = result;
}

El Pop(Stack **source)//pop first element from stack and return his value.
{
    El result = (**source).el;
    Stack * prev = (*source)->prev;
    free((*source));
    (*source) = prev;
    return result;
}

void printStack(Stack * stack)//Print stack from up to down.
{  
    while(stack != NULL)
    {
        printEl(stack->el);
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
    El temp;
    const char * val;
    for(unsigned int i = 0; i < strlen(s)+1; i++)
    {
        if(*(s+i) == ' ' || *(s+i) == '\0')
        {
            val = slice(s, begin, i)
            if(isDigit(val))
            {
                temp.T = num;
                temp.val = atoi(val);
            }
            else if(in(*val, "+-*/"))
            {
                temp.T = op;
                temp.val = val;
            }
            else
            {
                temp.T = let;
                temp.val = val;
            }
            Push(stack, temp);
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
    result->el = stack->el;
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
        if(in(*val, "+-*/") )
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
    Node * result = createNode(val);
    Node * cur_node = result;
    while(stack != NULL)
    {
        val = Pop(&stack);
        if(in(*val, "+-*/"))
        {
            while(!(in(*cur_node->val, "+-*/") && (cur_node->right == NULL || cur_node->left == NULL)))
            {
                cur_node = cur_node->parent;
            }
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
            while(!((cur_node->right == NULL || cur_node->left == NULL) && in(*cur_node->val, "+-*/")))
            {
                cur_node = cur_node->parent;
            }
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
    }
    return result;
}


Node * repairTree(Node * node)
{
    if(*node->val == '-' && strlen(node->val) == 1)
    {
        if(!in(*node->right->val, "+-*/"))
        {
            node->right->val = realloc(node->right->val, strlen(node->right->val)+2);
            memmove(node->right->val+1, node->right->val, strlen(node->right->val)+1);
            memmove(node->right->val, "-", 1);
        }
        else
        {
            node->right->left->val = realloc(node->right->left->val, strlen(node->right->left->val)+2);
            memmove(node->right->left->val+1, node->right->left->val, strlen(node->right->left->val)+1);
            memmove(node->right->left->val, "-", 1);
        }
        node->val = memmove(node->val, "+", 2);
    }
    if(node->left != NULL)
    {
        node->left = repairTree(node->left);
    }
    if(node->right != NULL)
    {
        node->right = repairTree(node->right);
    }
    return node;
}
int intSize(int a)
{
    int result = 0;
    while(a > 0)
    {
        a /= 10;
        result += 1;
    }
}
Node * doSumTree(Node * node)
{
    if(node == NULL)
    {
        return NULL;
    }
    // printTree(node, 0);
    // printf("$$$$$$$$$$\n");
    if(*node->val == '+' && isDigit(node->left->val) && isDigit(node->right->val))
    {
        int newSum = atoi(node->left->val) + atoi(node->right->val);
        printf("$%s$\n", node->val);
        node->val = realloc(node->val, intSize(newSum)+1);
        printf("$%s$\n", node->val);
        sprintf(node->val, "%d", newSum);
        printf("$%s$\n", node->val);
        node->left = NULL;
        node->right = NULL;
    }
    else if(in(*node->val, "*/+"))
    {
        node->left = doSumTree(node->left);
        node->right = doSumTree(node->right);
    }
    return node;
}

int main()
{
    const char *s = "a - 25 + 14";
    Stack * stack = NULL;
    stringToStack(&stack, s);
    stack = convToPrefForm(stack);
    printStack(stack);
    printf("^^^^^^^^^^^^^^\n");
    Node * tree = PrefStackToTree(stack);
    tree = repairTree(tree);
    printTree(tree, 0);
    printf("^^^^^^^^^^^^^^\n");
    tree = doSumTree(tree);
    printf("%d", tree->right->val == NULL);
    //printTree(tree, 0);
    return 0;
}
