#include <iostream>
#include <vector>
#include <set>

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
  set<char> good{'a', 'o', 'i', 'e', 'u', 'y'};
  char val;
  set<char> Sval;
  bool flag = true;
  vector<bool> result;
  for(char val; (val = getchar()); )
  {
    val = tolower(val);
    if(val == ' ' || val == '\n' || val == EOF)
    {
      if(flag)
      {
        result.push_back(true);
      }
      flag = true;
      Sval.erase(Sval.begin(), Sval.end());
      if(val == EOF)
      {
        break;
      }
    }
    if(Sval.find(val) != Sval.end() && good.find(val) != good.end())
    {
      flag = false;
      result.push_back(false);
    }
    else
    {
      Sval.insert(val);
    }
  }
  for(int i = 0; i < result.size()-1; i++)
  {
    if(result[i])
    {
      cout << "YES" << ' ';
    }
    else
    {
      cout << "NO" << ' ';
    }
  }

  return 0;
}