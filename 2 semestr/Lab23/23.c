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
    while(node->left != NULL)
    {
        node = node->left;
    }
    return node;
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
            if(parent->val <= cur_node->val)
            {
                parent->right = NULL;
            }
            else
            {
                parent->left = NULL;
            }
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
            if(parent->val <= cur_node->val)
            {
                parent->right = left;
            }
            else
            {
                parent->left = left;
            }
        }
        else
        {
            (*where) = left;
        }
        left->parent = parent;
    }
    else if(left == NULL)
    {
        if(parent != NULL)
        {
            if(parent->val <= cur_node->val)
            {
                parent->right = right;
            }
            else
            {
                parent->left = right;
            }
        }
        else
        {
            (*where) = right;
        }
        right->parent = parent;
    }
    else
    {
        Node * mln = find_most_left(cur_node->right);// mln - most left node
        
        if(cur_node->right->left != NULL)
        {
            mln->parent->left = mln->right;
            if(mln->right != NULL)
            {
                mln->right->parent = mln->parent;// set right son and mln conection if he exist
            }
            mln->right = cur_node->right;
            cur_node->right->parent = mln;// set right son
        }

        mln->left = cur_node->left;
        cur_node->left->parent = mln; // set left son and mln conection

        mln->parent = cur_node->parent;
        if(cur_node->parent != NULL)
        {
            if(cur_node->parent->val <= cur_node->val)
            {
                cur_node->parent->right = mln;
            }
            else
            {
                cur_node->parent->left = mln;
            }
        }// set mln's parent conection
        else
        {
            (*where) = mln;
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
