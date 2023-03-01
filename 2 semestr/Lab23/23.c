#include <stdio.h>
#include <malloc.h>
typedef struct tree
{
    int val;
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
    return res_node;
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
            node->left = new_node;
            return;
        }
        else
        {
            add_node(node->left, v);
        }
    }
    else
    {
        if(node->right == NULL)
        {
            Node * new_node = (Node *)malloc(sizeof(Node));
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->parent = node;
            new_node->val = v;
            node->right = new_node;
            return;
        }
        else
        {
            add_node(node->right, v);
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
    Node * cur_node = node->right;
    while(cur_node->left != NULL)
    {
        cur_node = cur_node->left;
    }
    return cur_node;
}

void delete_node(Node** where, int what)
{
    Node * cur_node = search((*where), what);
    if(cur_node == NULL)
    {
        printf("E: %d doesn't in tree\n", what);
        return;
    }
    if(cur_node->parent == NULL)
    {
        if(cur_node->left == NULL && cur_node->right == NULL)
        {
            (*where) = NULL;
        }
        else if(cur_node->left == NULL)
        {
            (*where) = cur_node->right;
            (*where)->parent = NULL;
        }
        else if(cur_node->right == NULL)
        {
            (*where) = cur_node->left;
            (*where)->parent = NULL;
        }
        else
        {
            Node * most_left_node = find_most_left(cur_node);
            (*where) = most_left_node;
            if(cur_node->right->left != NULL)
            {
                if(most_left_node->right != NULL)
                {
                    
                    most_left_node->parent->left = most_left_node->right;
                    most_left_node->right->parent = most_left_node->parent;
                }
                else
                {
                    cur_node->right->left = NULL;
                }
                cur_node->right->parent = most_left_node;
                most_left_node->right = cur_node->right;
            }
            most_left_node->parent = NULL;
            cur_node->left->parent = most_left_node;
            most_left_node->left = cur_node->left;
        }
        return;
    }
    if(cur_node->left == NULL && cur_node->right == NULL)
    {
        if(cur_node->val >= cur_node->parent->val)
        {
            cur_node->parent->right = NULL;
        }
        else
        {
            cur_node->parent->left = NULL;
        }
    }
    else if(cur_node->left == NULL)
    {
        if(cur_node->val >= cur_node->parent->val)
            {
                cur_node->parent->right = cur_node->right;
            }
        else
            {
               cur_node->parent->left = cur_node->right;
            }
    }
    else if(cur_node->right == NULL)
    {
        if(cur_node->val >= cur_node->parent->val)
        {
            cur_node->parent->right = cur_node->left;
        }
        else
        {
            cur_node->parent->left = cur_node->left;
        }
    }
    else
    {
        Node * most_left_node = find_most_left(cur_node);
        
        if(cur_node->right->left != NULL)
        {
            if(most_left_node->right != NULL)
            {
                most_left_node->parent->left = most_left_node->right;
                most_left_node->right->parent = most_left_node->parent;
            }
            else
            {
                most_left_node->parent->left = NULL;
            }
            most_left_node->right = cur_node->right;
            cur_node->right->parent = most_left_node;
        }
        cur_node->left->parent = most_left_node;
        most_left_node->left = cur_node->left;

        most_left_node->parent = cur_node->parent;

        if(cur_node->val >= cur_node->parent->val)
        {
            cur_node->parent->right = most_left_node;
        }
        else
        {
            cur_node->parent->left = most_left_node;
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

int main()
{
    Node * tree = NULL;
    int n;
    while(1)
    {
        printf("Choose option:\n1. Create tree\n2. Add node to tree\n3. Delete node from tree\n4. Show tree\n5. Find element in tree\n6. Exit\nYour option: ");
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
            return 0;
        }
        else
        {
            printf("Fuck u, input normal option\n");
        }
        printf("\n");
    } 
}
