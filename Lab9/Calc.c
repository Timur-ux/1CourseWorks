#include <stdio.h>
//Данный модуль содержит всю логику и математику программы.
//Определяем основные функции(математические). Макс, мин, проверить на попадание, знак, модуль
int max(int a, int b){
    return (a>b) ? a : b;
}
int min(int a, int b){
    return (a>b) ? b : a;
}
int chek(int i, int j, int Ci, int Cj, int A, int B){
    if (abs(Cj - j)>A){
        return 0;
    }
    //Xo2mCi - максимальный разлёт значений х от Ci, если у считать параметром.(i ~ x, j ~ y в дальнейшем).
    int Xo2mCi = A*A*(1-(j-Cj)*(j-Cj)/B/B);
    if(Xo2mCi >= (i-Ci)*(i-Ci)){
        return 1;
    }
    return 0;
}

int sign(int n){
    if (n > 0) return 1;
    if (n == 0) return 0;
    return -1;
}
int abs(int x){
    if (x >= 0) return x;
    return -x;
}
//Главная вычислительная функция, для данного теста вычисляет попадание.
int Calc(const int i0, const int j0, const int l0){
    //Объявление начальных констант
    const int Ci = 10;
    const int Cj = 10;
    const int A = 10;
    const int B = 5;
    //Объявление начальных переменных
    int ik = i0;
    int jk = j0;
    int lk = l0;
    //Проверка на попадание при k = 0, затем при k = 1,2,...,50
    if(chek(i0, j0, Ci, Cj, A, B)){
        printf("Yes. k = 0, i = %d, j = %d, l = %d\n", i0, j0, l0);
        return 0;
    }
    for(int k = 1; k <= 50; k++){
        int copyik = ik, copyjk = jk, copylk = lk;//Создание копий ik, jk, lk
        //Обновляем ik, jk, lk
        ik = max(max(copyik*copyjk, copyik*copylk), copyjk*copylk)%30 + k;
        jk = abs(copyjk-copylk)*sign(copyik) - abs(copyik-copylk)*sign(copyjk);
        lk = min(copyik, max(copyjk, min(copylk, max(copyik-copylk, copyjk-copylk))));
        //Проверка на попадание
        if(chek(ik, jk, Ci, Cj, A, B)){
            printf("Yes. k = %d, i = %d, j = %d, l = %d\n", k, ik, jk, lk);
            return 0;
        }
    }
    //Если вышли из цикла, значит промах.
    printf("No. k = 50, i = %d, j = %d, l = %d\n", ik, jk, lk);
    return 0;
}