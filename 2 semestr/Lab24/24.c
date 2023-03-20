#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>

typedef union val
{
    char symbol;
    int num;
} value;

typedef enum {operator, number, letter} type;

typedef struct el
{
    value val;
    type T;
} Item;

typedef struct tree
{
    Item item;
    struct tree* left;
    struct tree* right;
    struct tree* parent;
} Node;

typedef struct stk
{
    Item item;
    struct stk * prev;
} Stack;

int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '^' || c == '/' || c == '(' || c == ')';
}

int isDigit(char c)
{
    return c >= '0' && c <= '9';
}

int isLetter(char c)
{
    return (c >= 'a' && c <= 'z') || ( c >= 'A' && c <= 'Z');
}

int sizeOf(Stack * stack)
{
    if(stack == NULL)
    {
        return 0;
    }
    return 1 + sizeOf(stack->prev);
}

Stack * Push(Stack * stack, Item item)
{
    Stack * result = (Stack *)malloc(sizeof(Stack));
    result->prev = stack;
    result->item = item;
    return result;
}

Item Pop(Stack ** stack)
{
    if(*stack == NULL)
    {
        return NULL;
    }
    Item result = (*stack)->item;
    *stack = (*stack)->prev;
    return result;
}

Stack * sumStacks(Stack *a, Stack *b)
{
    if(a == NULL)
    {
        return b;
    }
    Stack *cur_stack = a;
    while(cur_stack->prev != NULL)
    {
        cur_stack = cur_stack->prev;
    }
    cur_stack->prev = b;
    return a;
}

Stack * stringToStack()
{
    Stack * result = NULL;
    Item item;
    int buff = 0;
    int lastNum = 0;
    char c;
    while(1)
    {
        if(lastNum == 0)
        {
            c = getchar();
        }
        else
        {
            lastNum = 0;
        }
        if(c == EOF || c == '\n')
        {
            return result;
        }
        else if(c == ' ')
        {
            continue;
        }
        else if(isOperator(c) && c == ')')
        {
            return result;
        }
        else if(isOperator(c) && c == '(')
        {
            Stack * inner_stack = stringToStack();
            if(result == NULL)
            {
                result = inner_stack;
            }
            else
            {
                Item op = Pop(&result);
                result = sumStacks(result, inner_stack);
                result = Push(result, op);
            }
        }
        else if(isOperator(c))
        {
            result = Push(result, (Item){c, operator});
        }
        else if(isDigit(c))
        {
            lastNum = 1;
            buff = c - '0';
            while(isDigit(c))
            {
                c = getchar();
                if(isDigit(c))
                {
                    buff = buff * 10 + (c - '0');
                }
            }
            if(result == NULL)
            {
                result = Push(result, (Item){buff, number});
            }
            else if(result->item.T == operator)
            {
                Item op = Pop(&result);
                result = Push(Push(result, (Item){buff, number}), op);
            }
            else
            {
                printf("Неучтённое поведение 1");
            }
        }
        else if (isLetter(c))
        {
            if(result == NULL)
            {
                result = Push(result, (Item){c, letter});
            }
            else if(result->item.T == operator)
            {
                Item op = Pop(&result);
                result = Push(Push(result, (Item){c, letter}), op);
            }
            else
            {
                printf("Неучтённое поведение 2");
            }
        }
    }
}

void printStack(Stack *stack)
{
    if(stack == NULL)
    {
        return;
    }
    if(stack->item.T == number)
    {
        printf("%d\n", stack->item.val.num);
    }
    else
    {
        printf("%c\n", stack->item.val.symbol);
    }
    printStack(stack->prev);
}

Node * stackToTree(Stack * stack)
{
    Node * result = (Node)malloc(sizeof(Node));
    Item item = Pop(&stack);
    result->item = item;
    result->left = NULL;
    result->right = NULL;
    result->parent = NULL;
    Node * cur_node = result;
    int findEmpty = 0;
    while(1)
    {
        if(findEmpty == 0)
        {
            item = Pop(&stack);
        }
        if(item == NULL)
        {
            return result;
        }
        if(item.T == operator)
        {
            if(cur_node->right == NULL)
            {
                findEmpty = 0;
                cur_node->right = (Node)malloc(sizeof(Node));
                cur_node->right->parent = cur_node;
                cur_node->right->right = NULL;
                cur_node->right->left = NULL;
                cur_node->right->item = item;
                cur_node = cur_node->right;
            }
            else if(cur_node->left == NULL)
            {
                findEmpty = 0;
                cur_node->left = (Node)malloc(sizeof(Node));
                cur_node->left->parent = cur_node;
                cur_node->left->right = NULL;
                cur_node->left->left = NULL;
                cur_node->left->item = item;
                cur_node = cur_node->left;
            }
            else
            {
                findEmpty = 1;
                cur_node = cur_node->parent;
            }
        }
        else
        {
            if(cur_node->right == NULL)
            {
                cur_node->right = (Node)malloc(sizeof(Node));
                cur_node->right->parent = cur_node;
                cur_node->right->right = NULL;
                cur_node->right->left = NULL;
                cur_node->right->item = item;
            }
            else if(cur_node->left == NULL)
            {
                cur_node->left = (Node)malloc(sizeof(Node));
                cur_node->left->parent = cur_node;
                cur_node->left->right = NULL;
                cur_node->left->left = NULL;
                cur_node->left->item = item;
            }
            else
            {
                findEmpty = 1;
                cur_node = cur_node->parent;
            }
        }
    }

}

void printTree(Node *node)
{
    if(node->left != NULL)
    {
        printTree(node->left);
    }
    if(node->item.T == number)
    {
        printf("%d ", node->item.val.num);
    }
    else
    {
        printf("%c ", node->item.val.symbol);
    }
    if(node->right != NULL)
    {
        printTree(node->right);
    }
}
int main()
{
    Stack *stack = stringToStack();
    Node *tree = stackToTree(stack);
    printTree(tree);
    return 0;
}
