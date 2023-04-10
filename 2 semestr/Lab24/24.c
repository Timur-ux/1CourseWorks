#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "libs/item.h"
#include "libs/stack.c"
#include "libs/tree.c"
bool IsDigit(char c) {
    return c >= '0' && c <= '9';
}
void printStack(Stack * stack);
bool IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == ')';
}

bool IsLetter(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

double DoOperation(double a, double b, char operator) {
    double c;
    if (operator == '+') {
        c = a + b;
    } else if (operator == '-') {
        c = a - b;
    } else if (operator == '*') {
        c = a * b;
    } else if (operator == '/') {
        c = a / b;
    } else if (operator == '^') {
        c = pow(a, b);
    }
    return c;
}

int CheckPriorety(char c) {
    int result;
    if (c == '+' || c == '-') {
        result = 1;
    } else if (c == '*' || c == '/') {
        result = 2;
    } else if (c == '^') {
        result = 3;
    } else if (c == ')') {
        result = -1;
    } else if (c == '(') {
        result = 0;
    }
    return result;
}

void ReadToStack(Stack **stk) {
    Stack *bufStk = NULL;
    bool isNumTyped = false;
    bool isNotStarted = true;
    bool isFractional = false;
    bool nextIsOp = false;
    double buff = 0.0;
    int sign = 1;
    double p = 1.0;
    while (1) {
        char c = getchar();
        if (c == ' ') {
            continue;
        }
        if (IsDigit(c) || c == '.' || (c == '+' || c == '-') && isNotStarted && !nextIsOp) {
            isNotStarted = false;
            if (IsDigit(c)) {
                isNumTyped = true;
                buff = buff * 10 + (c - '0');
                if (isFractional) {
                    p *= 0.1;
                }
            } else if (c == '.') {
                isFractional = true;
            } else if (c == '-') {
                sign = -1;
            }
        } else if (IsOperator(c) || c == EOF || c == '\n') {
            isNumTyped = false;
            Value v;
            if (!nextIsOp) {
                buff = buff * p * sign;
                v.number = buff;
                StackPush(stk, (Item){v, NUMBER});
            }
            isNotStarted = true;
            sign = 1;
            buff = 0.0;
            p = 1.0;
            nextIsOp = false;
            isFractional = false;
            int priorety = CheckPriorety(c);
            while (!StackIsEmpty(&bufStk)) {
                if (CheckPriorety(StackTop(&bufStk).value.symbol) > priorety || c == EOF || c == '\n') {
                    if (StackTop(&bufStk).value.symbol != '(') {
                        StackPush(stk, StackTop(&bufStk));
                    }
                    else {
                        StackPop(&bufStk);
                        break;
                    }
                    StackPop(&bufStk);
                } else {
                    break;
                }
            }
            if (c == ')' || c == EOF || c == '\n') {
                nextIsOp = true;
            } else {
                v.symbol = c;
                StackPush(&bufStk, (Item){v, OPERATOR});
            }

        } else if (c == '(') {
            Value v;
            v.symbol = c;
            StackPush(&bufStk, (Item){v, OPERATOR});
        } else if (IsLetter(c)) {
            nextIsOp = true;
            Value v;
            v.symbol = c;
            StackPush(stk, (Item){v, VARIABLE});
            if (!isNotStarted) {
                if (!isNumTyped) {
                    buff = 1.0;
                }
                buff *= p * sign;
                v.number = buff;
                StackPush(stk, (Item){v, NUMBER});
                v.symbol = '*';
                StackPush(stk, (Item){v, OPERATOR});
            }
            isNumTyped = true;
        }

        if (c == '\n' || c == EOF) {
            break;
        }
        
    }
}

void BuildTree(Node **root, Stack **expr, Node * parent) {
    if (StackIsEmpty(expr)) {
        return;
    }

    (*root) = CreateNode(StackTop(expr));
    (*root)->p = parent;
    
    StackPop(expr);
    if ((*root)->value.type == OPERATOR) {
        BuildTree(&(*root)->r, expr, (*root));
        BuildTree(&(*root)->l, expr, (*root));
    }

}
double findSumTree(Node *node)
{
    if(node == NULL || (node->value.type == OPERATOR && CheckPriorety(node->value.value.symbol) >=2))
    {
        return 0;
    }
    double result = 0;
    if(node->value.type == NUMBER)
    {
        if(node->p->value.value.symbol == '-' && node->p->r == node)
        {
            result -= node->value.value.number;
        }
        else
        {
            result += node->value.value.number;
        }
    }
    return result + findSumTree(node->l) + findSumTree(node->r);
}
void doSumTree(Node * node);
void deleteAllNum(Node *node);
int insertNum(Node *node, double num);

void deleteAllNum(Node *node)
{
    if(node->l->value.type == NUMBER)
    {
        free(node->l);
        node->l = NULL;
    }
    if(node->r->value.type == NUMBER)
    {
        free(node->r);
        node->r = NULL;
    }
    if(node->l != NULL && node->l->value.type == OPERATOR)
    {
        if(CheckPriorety(node->l->value.value.symbol) == 1)
        {
            deleteAllNum(node->l);
        }
        else
        {
            doSumTree(node->l);
        }
    }
    if(node->r != NULL && node->r->value.type == OPERATOR)
    {
        if(CheckPriorety(node->r->value.value.symbol) == 1)
        {
            deleteAllNum(node->r);
        }
        else
        {
            doSumTree(node->r);
        }
    }
}
int insertNum(Node *node, double num)
{
    if(node == NULL || node->value.type != OPERATOR)
    {
        return 0;
    }
    if(node->r == NULL)
    {
        node->r = (Node*)malloc(sizeof(Node));
        Item item;
        item.type = NUMBER;
        item.value.number = num;
        node->r->value = item;
        node->r->l = NULL;
        node->r->r = NULL;
        node->r->p = node;
        return 1;
    }
    else if(node->l == NULL)
    {
        node->l = (Node*)malloc(sizeof(Node));
        Item item;
        item.type = NUMBER;
        item.value.number = num;
        node->l->value = item;
        node->l->l = NULL;
        node->l->r = NULL;
        node->l->p = node;
        return 1;
    }
    else
    {
        if(!insertNum(node->r, num))
        {
            insertNum(node->l, num);
        }
    }
}

void doSumTree(Node * node)
{
    if(node->value.type == OPERATOR && CheckPriorety(node->value.value.symbol) >= 2)
    {
        doSumTree(node->l);
        doSumTree(node->r);
    }
    else if(node->value.type == OPERATOR)//+ or -
    {
        double sumTree = findSumTree(node);
        deleteAllNum(node);
        insertNum(node, sumTree);
    }
}
Node * repairTree(Node * node)
{
    if(node->l != NULL && node->l->value.type == OPERATOR)
    {
        node->l = repairTree(node->l);
    }
    if(node->value.type != OPERATOR)
    {
        return node;
    }
    Node * parent = node->p;
    if(node->l == NULL && node->r == NULL)
    {
        if(parent == NULL)
        {
            return NULL;
        }
        if(parent->l == node)
        {
            parent->l = NULL;
            return NULL;
        }
        else
        {
            parent->r = NULL;
            return NULL;
        }
    }
    else if(node->l == NULL)
    {
        if(CheckPriorety(node->value.value.symbol)==1)
        {
            if(parent == NULL)
            {
                return node->r;
            }
            else if(parent->l == node)
            {
                parent->l = node->r;
                node->r->p = parent;
            }
            else
            {
                parent->r = node->r;
                node->r->p = parent;
            }
            return node->r;
        }
    }
    else if(node->r == NULL)
    {
        if(CheckPriorety(node->value.value.symbol)==1)
        {
            if(parent == NULL)
            {
                return node->l;
                
            }
            else if(parent->l == node)
            {
                parent->l = node->l;
                node->l->p = parent;
            }
            else
            {
                parent->r = node->l;
                node->l->p = parent;
            }
            return node->l;
        }
    }
    if(node->r != NULL && node->r->value.type == OPERATOR)
    {
        node->r = repairTree(node->r);
    }
    return node;
}
void PrintTree(Node *root, int depth) {
    if (root != NULL) {
        if (root->value.type == OPERATOR) {
            // if (root->l->value.type == OPERATOR) {
            //     if (CheckPriorety(root->value.value.symbol) > CheckPriorety(root->l->value.value.symbol)) {
            //         printf("(");
            //     }
            // }

            PrintTree(root->l, depth+1);

            // if (root->l->value.type == OPERATOR) {
            //     if (CheckPriorety(root->value.value.symbol) > CheckPriorety(root->l->value.value.symbol)) {
            //         printf(")");
            //     }
            // }
            for(int i = 0; i < depth; i++)
            {
                printf("\t");
            }
            printf(" %c \n", root->value.value.symbol);

            // if (root->r->value.type == OPERATOR) {
            //     if (CheckPriorety(root->value.value.symbol) > CheckPriorety(root->r->value.value.symbol)) {
            //         printf("(");
            //     }
            // }

            PrintTree(root->r, depth+1);

            // if (root->r->value.type == OPERATOR) {
            //     if (CheckPriorety(root->value.value.symbol) > CheckPriorety(root->r->value.value.symbol)) {
            //         printf(")");
            //     }
            // }
        } else if (root->value.type == VARIABLE) {
            for(int i = 0; i < depth; i++)
            {
                printf("\t");
            }
            printf("%c\n", root->value.value.symbol);
        } else {
            for(int i = 0; i < depth; i++)
            {
                printf("\t");
            }
            printf("%f\n", root->value.value.number);
        }
    } else {
        printf("\n");
    }
}
void PrintTreeInString(Node *root) {
    if (root != NULL) {
        if (root->l != NULL && root->l->value.type == OPERATOR) {
            if (CheckPriorety(root->value.value.symbol) > CheckPriorety(root->l->value.value.symbol)) {
                printf("( ");
            }
        }

        PrintTreeInString(root->l);

        if (root->l != NULL && root->l->value.type == OPERATOR) {
            if (CheckPriorety(root->value.value.symbol) > CheckPriorety(root->l->value.value.symbol)) {
                printf(") ");
            }
        }
        if(root->value.type == NUMBER)
        {
            if(root->value.value.number == 0)
            {
                return;
            }
            printf("%f ", root->value.value.number);
        }
        else
        {
            if(root->value.type != OPERATOR || root->l != NULL && root->r != NULL)
            {
                printf("%c ", root->value.value.symbol);
            }
        }
        if (root->r != NULL && root->r->value.type == OPERATOR) {
            if (CheckPriorety(root->value.value.symbol) > CheckPriorety(root->r->value.value.symbol)) {
                printf("( ");
            }
        }

        PrintTreeInString(root->r);

        if (root->r != NULL && root->r->value.type == OPERATOR) {
            if (CheckPriorety(root->value.value.symbol) > CheckPriorety(root->r->value.value.symbol)) {
                printf(") ");
            }
        }
    }
}
void printStack(Stack * stack)
{
    while(stack != NULL)
    {
        if(stack->value.type != NUMBER)
        {
            printf("%c\n", stack->value.value.symbol);
        }
        else
        {
            printf("%f\n", stack->value.value.number);
        }
        stack = stack->next;
    }
}
int main() {
    while(1)
    {
        printf(">>> ");    
        Stack *stk = NULL;
        Value v;
        v.number = 5;
        Node *root = NULL;
        ReadToStack(&stk);
        // printStack(stk);
        BuildTree(&root, &stk, NULL);
        // PrintTree(root, 0);
        // printf("^^^^^^^^^^^\n");
        doSumTree(root);
        // PrintTree(root, 0);
        // printf("^^^^^^^^^^^\n");
        root = repairTree(root);
        // PrintTree(root, 0);
        // printf("^^^^^^^\n");
        printf("<<< ");
        PrintTreeInString(root);
        printf("\n");
    }
}