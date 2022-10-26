//Лабораторная работа №9. Вариант 29. Бучкин Тимур Артемович. М8О-101Б-22.
//Здесь содержатся тесты, реализация программы находится в модуле Calc.c
#include <stdio.h>
#include "Calc.c"

int main(){
    //Тест из варианта
    printf("First test from guide(Variant 29) i0 = %d, j0 = %d, l0 = %d\n Result =  ",-7, -19, 4); 
    Calc(-7, -19, 4);//
    //Далее идут 125 тестов для i0, j0, l0 = {1,...,5}
    int k = 1;
    for(int i0 = 1; i0 <= 5; i0++){
        for(int j0 = 1; j0 <= 5; j0++){
            for(int l0 = 1; l0 <= 5; l0++){
                printf("Test N %d: i0 = %d, j0 = %d, l0 = %d\n Result = ", k, i0, j0, l0);
                Calc(i0, j0, l0);
                k++;
            }
        }
    }
    
    return 0;
}