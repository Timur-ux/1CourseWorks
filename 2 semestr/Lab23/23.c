#include <stdio.h>
#include <malloc.h>
typedef struct tree
{
    int val;
    int size;
    struct tree* left;
    struct tree* right;
    struct tree* parent;
} Node;

Node* create_node(int v)
{
    Node * res_node = malloc(sizeof(Node));
    res_node->val = v;
    res_node->parent = NULL;
    res_node->left = NULL;
    res_node->right = NULL;
    res_node->size = 1;
    return res_node;
}
int SizeOf(Node * node)
{
    if(node != NULL)
    {
        return node->size;
    }
    return 0;
}
void Recalc(Node * node)
{
    if(node != NULL)
    {
        node->size = SizeOf(node->left) + SizeOf(node->right) + 1;
    }
}
void add_node(Node* node, int v)
{
    if(v < node->val)
    {
        if(node->left == NULL)
        {
            Node * new_node = malloc(sizeof(Node));
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->parent = node;
            new_node->val = v;
            new_node->size = 1;
            node->left = new_node;
            Recalc(node);
            return;
        }
        else
        {
            add_node(node->left, v);
            Recalc(node);
        }
    }
    else
    {
        if(node->right == NULL)
        {
            Node * new_node = malloc(sizeof(Node));
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->parent = node;
            new_node->val = v;
            new_node->size = 1;
            node->right = new_node;
            Recalc(node);
            return;
        }
        else
        {
            add_node(node->right, v);
            Recalc(node);
        }
    }
    
}

Node* search(Node * node, int v)
{
    if(node->val == v)
    {
        return node;
    }
    if(v < node->val)
    {
        if(node->left == NULL)
        {
            return NULL;
        }
        return search(node->left, v);
    }
    if(node->right == NULL)
    {
        return NULL;
    }
    return search(node->right, v);
}

Node * find_most_left(Node * node)//use this method only if node has right son
{
    while(node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

void setParSonConnection(Node * parent, Node* son, Node* what)
{
    if(son->val >= parent->val)
    {
        parent->right = what;
    }
    else
    {
        parent->left = what;
    }
}
void RepairSizeUp(Node * node)
{
    Recalc(node);
    if(node->parent != NULL)
    {
        RepairSizeUp(node->parent);
    }
}

void delete_node(Node** where, int what)
{
    Node * cur_node = search((*where), what);
    if(cur_node == NULL)
    {
        printf("\nE: %d doesn't in tree\n", what);
        return;
    }
    Node * parent = cur_node->parent;
    Node * left = cur_node->left;
    Node * right = cur_node->right;
    if(left == NULL && right == NULL)
    {
        if(parent != NULL)
        {
            setParSonConnection(parent, cur_node, NULL);
            Recalc(parent);
        }
        else
        {
            (*where) = NULL;
        }
    }
    else if(right == NULL)
    {
        if(parent != NULL)
        {
            setParSonConnection(parent, cur_node, left);
            Recalc(parent);
        }
        else
        {
            (*where) = left;
            Recalc((*where));
        }
        left->parent = parent;
    }
    else if(left == NULL)
    {
        if(parent != NULL)
        {
            setParSonConnection(parent, cur_node, right);
            Recalc(parent);
        }
        else
        {
            (*where) = right;
            Recalc((*where));
        }
        right->parent = parent;
    }
    else
    {
        Node * mln = find_most_left(cur_node->right);// mln - most left node
        Node * mlp_p = mln->parent;
        if(cur_node->right->left != NULL)
        {
            mln->parent->left = mln->right;
            if(mln->right != NULL)
            {
                mln->right->parent = mln->parent;// set right son and mln connection if he exist
            }
            mln->right = cur_node->right;
            cur_node->right->parent = mln;// set right son
        }

        mln->left = cur_node->left;
        cur_node->left->parent = mln; // set left son and mln connection

        mln->parent = cur_node->parent;
        if(cur_node->parent != NULL)
        {
            setParSonConnection(parent, cur_node, mln);
        }// set mln's parent connection
        else
        {
            (*where) = mln;
        }
        if(mlp_p->left != NULL)
        {
            RepairSizeUp(mlp_p->left);
        }
        else
        {
            RepairSizeUp(mlp_p);
        }
    }
    free(cur_node);
}

void show_tree(Node* node, int depth)
{
    if(node->right != NULL)
    {
        show_tree(node->right, depth+1);
    }
    for(int i = 0; i < depth; i++)
    {
        printf("\t");
    }

    printf("%d\n", node->val);
    if(node->left != NULL)
    {
        show_tree(node->left, depth+1);
    }
}

int isAVL(Node * node)
{
    if(abs(SizeOf(node->left) - SizeOf(node->right))>1)
    {
        return 1;
    }
    int result = 0;
    if(node->left != NULL)
    {
        result += isAVL(node->left);
    }
    if(node->right != NULL)
    {
        result += isAVL(node->right);
    }
    return result;
}

int abs(int a)
{
    if(a >= 0)
    {
        return a;
    }
    return (-1)*a;
}
int main()
{
    Node * tree = NULL;
    int n;
    while(1)
    {
        printf("Choose option:\n1. Create tree\n2. Add node to tree\n3. Delete node from tree\n4. Show tree\n5. Find element in tree\n6. Chek AVL\n7. Exit\nYour option: ");
        scanf("%d", &n);
        printf("\n");
        if(n == 1)
        {
            int v;
            printf("Input value for tree's root ");
            scanf("%d", &v);
            tree = create_node(v);
        }
        else if(n == 2)
        {
            if(tree == NULL)
            {
                printf("E: Create tree before\n");
            }
            else
            {
                int v;
                printf("Input value for adding ");
                scanf("%d", &v);
                add_node(tree, v);
            }
        }
        else if(n == 3)
        {
            if(tree == NULL)
            {
                printf("E: Create tree before\n");
            }
            else
            {
                int v;
                printf("Input value for deleting ");
                scanf("%d", &v);
                delete_node(&tree, v);
            }
        }
        else if(n == 4)
        {
            if(tree == NULL)
            {
                printf("E: Create tree before\n");
            }
            else
            {
                show_tree(tree, 0);          
            }
        }
        else if(n == 5)
        {
            if(tree == NULL)
            {
                printf("E: Create tree before\n");
            }
            else
            {
                int v;
                printf("Input value for find ");
                scanf("%d", &v);
                if(search(tree, v) == NULL)
                {
                    printf("%d doesn't in tree\n", v);
                }
                else
                {
                    printf("%d in tree\n", v);
                }
            }
        }
        else if(n == 6)
        {
            if(tree == NULL || isAVL(tree) == 0)
            {
                printf("This tree is AVL-tree now\n");
            }
            else
            {
                printf("This tree isn't AVL-tree now\n");
            }
        }
        else if(n == 7)
        {
            return 0;
        }
        else
        {
            printf("Fuck u, input normal option\n");
        }
        printf("\n");
    } 
}
