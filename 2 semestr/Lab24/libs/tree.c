#include <stdlib.h>
#include "tree.h"
#include "item.h"

Node *CreateNode(Item value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->l = NULL;
    node->r = NULL;
    return node;
}
