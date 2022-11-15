//program for CP3

#include <stdio.h>
#include <math.h>

double f(double x)
{
    return x/(9+x*x);
}

double taylor(double x, double a, double b, int &n, double eps)
{
    double di = (b-a)/n;
    int endN = n;
    double sum = x/9;
    double prev_sum;
    for(int i = 1; i <= n; i++)
    {
        prev_sum = sum;
        sum += (pow(-1, i)*pow(x, 2*i+1)/pow(9, i+1));
        if(abs(sum - prev_sum) <= eps)
        {
            endN = i-1;
            sum = prev_sum;
            break;
        }
    }
    n = endN;
    return sum;
}

int main()
{
    double prev_eps = 1;
    double eps;
    double k;
    double a = -1, b = 1;
    int n = 30;
    printf("Input k (1e14 is good) ");
    scanf("%lf", &k);
    printf("\n");
    while ((1+prev_eps) != 1)
    {
        eps = prev_eps;
        prev_eps /= 2;
    }

    eps *= k;
    printf("eps*k is %f\n", eps);
    printf("                  Table of values function f(x) = x/(9+x^2)\n");
    printf("| x            | Taylor's row sum for f(x)| f(x)        | iteration's quantity|\n");
    double dx = (b-a)/n;
    for(double x = a; x <= b; x += dx)
    {
        int n_iter = 50;
        double taylorX = taylor(x, a, b, n_iter, eps);
        double fX = f(x);
        if(x<0)
        {
            printf("|%f     |%f                 |%f    |%d                    |\n", x, taylorX, fX, n_iter);
        }
        else
        {
            printf("|%f      |%f                  |%f     |%d                    |\n", x, taylorX, fX, n_iter);
        }
    }


    return 0;
}