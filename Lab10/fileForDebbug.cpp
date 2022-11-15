#include <iostream>
#include <string>
#include <vector>
using namespace std;

void calc(int c)
{
    return;
}

int main()
{
    cout << " Input a and b " << endl;
    int a, b;
    cin >> a >> b;
    string c;
    while(b==0)
    {
        cout << "b is zero, please reinput b" << endl;
        cin >> b;
    }
    int c1 = a/b;
    calc(c1);
    vector<int> v = {1, 2, 3};
    while ((b<0)||(b>=v.size()))
    {
        cout << "b is incorrect, please reinput b from 0 to " << v.size()-1 << endl;
        cin >> b;
    }
    cout << v[b] << endl;
    return 0; 
}