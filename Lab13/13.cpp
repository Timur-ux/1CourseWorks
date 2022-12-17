#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

int count(string s, char el)
{
  int res = 0;
  for(char e : s)
  {
    if(e == el)
    {
      res++;
    }
  }
  return res;
}

int main()
{
  vector<string> result;
  set<char> good{'a', 'o', 'i', 'e', 'u', 'y'};
  string val;
  while(cin >> val)
  {
    bool flag = true;
    set<char> Sval;
    for(char el : val)
    {
      Sval.insert(el);
    }
    for(set<char>::iterator it = Sval.begin(); it != Sval.end(); it++)
    {
      if(good.find(*it) != good.end() && count(val, *it) > 1)
      {
        flag = false;
        break;
      }
    }
    if(flag)
    {
      cout << "YES - " << val << endl;
      result.push_back(val);
    }
    else
    {
      cout << "NO - " << val << endl;
    }
  }
  cout << endl;

  return 0;
}