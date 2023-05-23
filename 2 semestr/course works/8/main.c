#include "List.c"

int main()
{
    List l;
    Create(&l);
    for(int i = 0; i < 5; i++)
    {
        double data = rand()%1000;
        Insert(&l, First(l), data/17);
    }
    Print(l);
    printf("List size is %d\n", SizeOf(l));
    Delete(&l, First(l));
    Print(l);
    DestroyIfEqual(&l, 24.5);
    Print(l);
    DestroyIfEqual(&l, Fetch(Next(First(l))));
    Print(l);
    return 0;
}