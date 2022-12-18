//variant 1 F(x) = e^x + ln(x) - 10x

#include <stdio.h>
#include <math.h>

double F(double x)
{
    return exp(x) + log(x) - 10*x;
}

double F1(double x)
{
    // return exp(x) + 1/x - 10;
    double dx = 0.0001;
    return (F(x+dx) - F(x))/dx;
}

double F2(double x)
{
    // return exp(x) - 1/pow(x, 2);
    double dx = 0.0001;
    return (F1(x+dx) - F1(x))/dx;
}


int main()
{
    double a = 3, b = 4;
    double xmin = a, xmax = a;
    for(double x = a; x < b; x+=0.01)
    {
        if(fabs(F(x)*F2(x))< pow(F1(x), 2))
        {
            if(xmin == a)
            {
                xmin = x;
            }
            if(x > xmax)
            {
                xmax = x;
            }
            if(x < xmax && x > xmin)
            {
                printf("Interruption on %lf\n", x);
            }
        }
    }
    printf("All right, the method go in from %lf to %lf\n", xmin, xmax);
    double eps = 1, prev_eps;
    while(1+eps != 1)
    {
        prev_eps = eps;
        eps /= 2;
    }
    eps = prev_eps;
    double xk = (a+b)/2, xkp1 = xk - F(xk)/F1(xk);
    
    while(fabs(xk - xkp1) >= eps)
    {
        xk = xkp1;
        xkp1 = xk - F(xk)/F1(xk);
    }
    printf("\nx end = %lf, ", xkp1);
    printf("F(x end) = %lf", F(xkp1));
    return 0;
}