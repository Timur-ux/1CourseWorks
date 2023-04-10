#include "lib/26.c"

int main()
{
    udt * dek = NULL;
    printf("udt is empty %d\n", udt_is_empty(dek));
    printf("Generating dek...\n");
    for(int i = 0; i < 10; i++)
    {
        udt_push_front(&dek, (data_type){rand(), ((double)rand())/17});
    }
    udt_print(dek);
    printf("^^^^^^^^^^^^^^^^^^^^\n");
    printf("udt is empty %d\n", udt_is_empty(dek), udt_size(dek));
    data_type item = dek->top->back->back->item;
    printf("deleting item with key = %d...\n", item.key);
    udt_erase(&dek, item.key);
    udt_print(dek);
    printf("dek size %d\n", udt_size(dek));
    printf("^^^^^^^^^^^^^^^^^^^^\n");
    printf("do hoar's qsort...\n");
    dek = hoar_qsort(dek);
    udt_print(dek);
}