//Лабораторная работа №12. Вариант 1. Бучкин Тимур Артемович. М8О-101Б-22.

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;
long long int mult(long long int n, int s)
{
    long long int result = 1;
    for (int i = 0; i < s; i++)
    {
        result *= n;
    }
    return result;
}
void solve(long long int n);

int main(){
    long long int val;
    ifstream file("12input.txt");
    while(file >> val)
    {
        solve(val);
    }
    
    return 0;
}

void solve(long long int n)
{
    cout << n << " --> ";
    long long int tempN = n;
    int counter = 0;
    while(tempN != 0)
    {
        counter += 1;
        tempN /= 10;
    }
    if(counter <= 1)
    {
        cout << "" << '\n';
        return;
    }
    if(counter%2 == 0)
    {
        cout << n << endl;
        return;
    }
    
    else
    {
        long long int result = 0;
        result += n/(mult(10, counter/2+1));
        result *= mult(10, counter/2);
        result += n%(mult(10, counter/2));
        cout << result << endl;
    }
    return;
}