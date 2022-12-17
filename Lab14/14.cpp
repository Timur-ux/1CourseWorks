#include <iostream>
#include <vector>
#include <string>

using namespace std;

int sqrt(int n)
{
  for(int res = 0; res <= n; res++)
  {
    if(res*res == n)
    {
      return res;
    }
  }
  throw n;
}

int main()
{
  vector<int> line;
  int val;
  while(cin >> val)
  {
    line.push_back(val);
  }
  
  int n = sqrt(line.size());
  vector<int> mLine;
  vector<vector<int>> matrix;
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      mLine.push_back(line[i*n+j]);
    }
    matrix.push_back(mLine);
    mLine.erase(mLine.begin(), mLine.end());
  }
  int is = n, js = 0;
  while(is > 0)
  {
    is--;
    for(int k = is*n+js; k < n*n; k += n+1)
    {
      cout << line[k] << ' ';
    }
  }
  int p = n-1;
  js++;
  while(p > 0)
  {
    int k = is*n+js;
    for(int _ = 0; _ < p; _++)
    {
      cout << line[k] << ' ';
      k += n+1;
    }
    p--;
    js++;
  }

  return 0;
}