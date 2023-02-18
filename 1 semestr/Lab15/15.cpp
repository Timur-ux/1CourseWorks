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

vector<vector <int>> mult(vector<vector <int>> m1, vector<vector <int>>m2)
{
  int n = m1[0].size();
  vector<vector <int>> result = m1;
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      int s = 0;
      for(int p = 0; p < n; p++)
      {
        s += m1[i][p]*m2[p][j];
      }
      result[i][j] = s;
    }
  }
  return result;
}
void printM(vector<vector <int>> m)
{
  int n = m[0].size();
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      cout << m[i][j] << ' ';
    }
    cout << endl;
  }
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
  vector<vector<int>> matrix, tMatrix, multedMatrix;
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      mLine.push_back(line[i*n+j]);
    }
    matrix.push_back(mLine);
    mLine.erase(mLine.begin(), mLine.end());
  }
  tMatrix = matrix;
  int temp;
  for(int i = 0; i < n; i++)
  {
    for(int j = i; j < n; j++)
    {
      temp = tMatrix[i][j];
      tMatrix[i][j] = tMatrix[j][i];
      tMatrix[j][i] = temp;
    }
  }
  multedMatrix = mult(matrix, tMatrix);
  cout << "-------------------------" << endl;
  printM(matrix);
  cout << "-------------------------" << endl;
  printM(tMatrix);
  cout << "-------------------------" << endl;
  printM(multedMatrix);
  cout << "-------------------------" << endl;

  return 0;
}