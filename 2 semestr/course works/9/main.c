#include "Table.c"

int main()
{
    FILE *file = fopen("input.txt", "r");
    Table T; Create(&T);
    for(int i = 0; i < 25; i++)
    {
        char *key;
        int data;
        fscanf(file, "%s %d", key, &data);
        add(&T, key, data);
    }
    print(T);
    printf("Sorting...\n");
    LinChangeSort(&T);
    print(T);
    printf("Searching for Item406...\nItem406 = %d", search(T, "Item406"));
}

