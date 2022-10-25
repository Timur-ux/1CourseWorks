#include <stdio.h>
#include <stdbool.h>
int max(int a, int b){
    return (a>b) ? a : b;
}
int min(int a, int b){
    return (a>b) ? b : a;
}
bool chek(int Rk2, int Rl, int Rb, int k){
    if ((Rk2 >= sqr(Rl)) & (Rk2 <= sqr(Rb))){
        printf("Yes! k = %d", k);
        return true;
    }
    return false;
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
int sqr(int a){
    return a*a;
}
int main(){
    const int Rl = 5;
    const int Rb = 10;
    const int Ci = 10;
    const int Cj = 10;
    const int i0 = 18;
    const int j0 = -9;
    const int l0 = 5;
    int ik = i0;
    int jk = j0;
    int lk = l0;
    int R02 = sqr(ik - Ci) + sqr(jk - Cj);
    if (chek(R02, Rl, Rb, 0)){
        return 0;
    }
    
    for(int k = 1; k <= 50; k++){
        int copyik = ik, copyjk = jk, copylk = lk;
        ik = copyik*max(copyjk, copylk)%30 + copyjk*min(copyik, copylk)%20 + k;
        jk = min(copyjk, max(copyjk,min(copylk, max(copyjk-copylk, copyik-copylk))));
        lk = sign(k-10)*abs(copyik-copyjk+copylk-k);
        int Rk2 = sqr(ik - Ci) + sqr((jk - Cj));
        if(chek(Rk2, Rl, Rb, k)){
            return 0;
        }
    }
    printf("No. k = 50, i = %d, j = %d, l = %d", ik, jk, lk);
    return 0;
}