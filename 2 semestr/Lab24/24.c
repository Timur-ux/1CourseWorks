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

Stack * stringToStack()
{
    Stack * result = NULL;
    int buff = 0;
    int lastNum = 0, isNegative = 0;
    char c, c_prev;
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
                result = sumStacks(inner_stack, result);
                result = Push(result, op);
            }
        }
        else if(isOperator(c))
        {
            result = Push(result, (Item){c, operator});
        }
        else if(isDigit(c))
        {
            if(result != NULL && c_prev == '-')
            {
                Pop(&result);
                if(result != NULL)
                {
                    result = Push(result, (Item){'+', operator});
                }
                isNegative = 1;
            }
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
            if(isNegative)
            {
                buff *= -1;
                isNegative = 0;
            }
            if(result == NULL)
            {
                Item item;
                item.T = number;
                item.val.num = buff;
                result = Push(result, item);
            }
            else if(result->item.T == operator)
            {
                Item item;
                item.T = number;
                item.val.num = buff;
                Item op = Pop(&result);
                result = Push(Push(result, item), op);
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
        c_prev = c;
    }
}


void printTree(Node *node, int depth)
{
    if(node->right != NULL)
    {
        printTree(node->right, depth+1);
    }
    for(int i = 0; i < depth; i++)
    {
        printf("\t");
    }
    if(node->item.T == number)
    {
        printf("%d\n", node->item.val.num);
    }
    else
    {
        printf("%c\n", node->item.val.symbol);
    }
    if(node->left != NULL)
    {
        printTree(node->left, depth+1);
    }
}

Node * stackToTree(Stack * stack)
{
    Node * result = (Node *)malloc(sizeof(Node));
    Item item = Pop(&stack);
    result->item = item;
    result->left = NULL;
    result->right = NULL;
    result->parent = NULL;
    Node * cur_node = result;
    int findEmpty = 0;
    while(1)
    {
        if(stack == NULL && findEmpty == 0)
        {
            return result;
        }
        if(findEmpty == 0)
        {
            item = Pop(&stack);
        }
        
        if(item.T == operator)
        {
            if(cur_node->right == NULL)
            {
                findEmpty = 0;
                cur_node->right = (Node *)malloc(sizeof(Node));
                cur_node->right->parent = cur_node;
                cur_node->right->right = NULL;
                cur_node->right->left = NULL;
                cur_node->right->item = item;
                cur_node = cur_node->right;
            }
            else if(cur_node->left == NULL)
            {
                findEmpty = 0;
                cur_node->left = (Node *)malloc(sizeof(Node));
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
                findEmpty = 0;
                cur_node->right = (Node *)malloc(sizeof(Node));
                cur_node->right->parent = cur_node;
                cur_node->right->right = NULL;
                cur_node->right->left = NULL;
                cur_node->right->item = item;
            }
            else if(cur_node->left == NULL)
            {
                findEmpty = 0;
                cur_node->left = (Node *)malloc(sizeof(Node));
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

int findSumTree(Node *node)
{
    if(node == NULL || (node->item.T == operator && (node->item.val.symbol == '*' ||node->item.val.symbol == '/')))
    {
        return 0;
    }
    int result = 0;
    if(node->item.T == number)
    {
        result += node->item.val.num;
    }
    return result + findSumTree(node->left) + findSumTree(node->right);
}
void doSumTree(Node * node);
void deleteAllNum(Node *node);
int insertNum(Node *node, int num);

void deleteAllNum(Node *node)
{
    if(node->left->item.T == number)
    {
        free(node->left);
        node->left = NULL;
    }
    if(node->right->item.T == number)
    {
        free(node->right);
        node->right = NULL;
    }
    if(node->left != NULL && node->left->item.T == operator)
    {
        if(node->left->item.val.symbol == '+' || node->left->item.val.symbol == '-')
        {
            deleteAllNum(node->left);
        }
        else
        {
            doSumTree(node->left);
        }
    }
    if(node->right != NULL && node->right->item.T == operator)
    {
        if(node->right->item.val.symbol == '+' || node->right->item.val.symbol == '-')
        {
            deleteAllNum(node->right);
        }
        else
        {
            doSumTree(node->right);
        }
    }
}
int insertNum(Node *node, int num)
{
    if(node == NULL || node->item.T != operator)
    {
        return 0;
    }
    if(node->right == NULL)
    {
        node->right = (Node*)malloc(sizeof(Node));
        Item item;
        item.T = number;
        item.val.num = num;
        node->right->item = item;
        node->right->left = NULL;
        node->right->right = NULL;
        node->right->parent = node;
        return 1;
    }
    else if(node->left == NULL)
    {
        node->left = (Node*)malloc(sizeof(Node));
        Item item;
        item.T = number;
        item.val.num = num;
        node->left->item = item;
        node->left->left = NULL;
        node->left->right = NULL;
        node->left->parent = node;
        return 1;
    }
    else
    {
        if(!insertNum(node->right, num))
        {
            insertNum(node->left, num);
        }
    }
}

void doSumTree(Node * node)
{
    if(node->item.T == operator && (node->item.val.symbol == '*' || node->item.val.symbol == '/'))
    {
        doSumTree(node->left);
        doSumTree(node->right);
    }
    else if(node->item.T == operator)//+ or -
    {
        int sumTree = findSumTree(node);
        deleteAllNum(node);
        insertNum(node, sumTree);
    }
}
void repairTree(Node ** node)
{
    if((*node)->left != NULL && ((*node)->left->item.T == operator))
    {
        repairTree(&((*node)->left));
    }
    if((*node)->right == NULL && (*node)->left == NULL)
    {
        //printf("1#%c#1\n", (*node)->item.val.symbol);
        if((*node)->item.T == operator)
        {
            if((*node)->parent == NULL)
            {
                (*node) = NULL;
                return;
            }
            else
            {
                if((*node)->parent->right == (*node))
                {
                    (*node)->parent->right = NULL;
                }
                else
                {
                    (*node)->parent->left = NULL;
                }
            }
            free((*node));
            return;
        }
    }
    else if((*node)->left == NULL)
    {
        if((*node)->item.val.symbol == '+')
        {
            Node * parent = (*node)->parent;
            Node * cur_node = (*node);
            (*node) = (*node)->right;
            (*node)->parent = parent;
            // if(parent != NULL)
            // {
            //     printf("%d %c\n", parent->left->item.val.symbol, cur_node->item.val.symbol);
            //     if(parent->left == cur_node)
            //     {
            //         parent->left == (*node);
            //     }
            //     else
            //     {
            //         parent->right = (*node);
            //     }
            // }
            free(cur_node);
        }
    }
    else if((*node)->right == NULL)
    {
        if((*node)->item.val.symbol == '+')
        {
            Node * parent = (*node)->parent;
            Node * cur_node = (*node);
            (*node) = (*node)->left;
            (*node)->parent = parent;
            // if(parent != NULL)
            // {
            //     if(parent->left == cur_node)
            //     {
            //         parent->left == (*node);
            //     }
            //     else
            //     {
            //         parent->right = (*node);
            //     }
            // }
            free(cur_node);
        }
    }
    if((*node)->right != NULL && ((*node)->right->item.T == operator))
    {
        repairTree(&((*node)->right));
    }
}

void printTreeInString(Node *node)
{
    if(node->item.T == operator && (node->item.val.symbol == '*' || node->item.val.symbol == '/') && node->left->item.T == operator)
    {
        printf("( ");
    }
    if(node->left != NULL)
    {
        printTreeInString(node->left);
    }
    if(node->item.T == operator && (node->item.val.symbol == '*' || node->item.val.symbol == '/') && node->left->item.T == operator)
    {
        printf(") ");
    }
    if(node->item.T == number)
    {
        printf("%d ", node->item.val.num);
    }
    else
    {
        printf("%c ", node->item.val.symbol);
    }
    if(node->item.T == operator && (node->item.val.symbol == '*' || node->item.val.symbol == '/') && node->right->item.T == operator)
    {
        printf("( ");
    }
    if(node->right != NULL)
    {
        printTreeInString(node->right);
    }
    if(node->item.T == operator && (node->item.val.symbol == '*' || node->item.val.symbol == '/') && node->right->item.T == operator)
    {
        printf(") ");
    }
}
int main()
{
    Stack *stack = stringToStack();
    Node *tree = stackToTree(stack);
    // printTree(tree, 0);
    // printf("^^^^^^^^^^^\n");
    doSumTree(tree);
    // printTree(tree, 0);
    // printf("^^^^^^^^^^^\n");
    repairTree(&tree);
    // printTree(tree, 0);
    printTreeInString(tree);
    return 0;
}