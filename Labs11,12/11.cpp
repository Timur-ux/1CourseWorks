//Лабораторная работа №11. Вариант 1. Бучкин Тимур Артемович. М8О-101Б-22.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int findInd(string s, string sub, int start, int end)
{
    for(int i = start; i < end; i++)
    {
        for(int j = 0; j < sub.size(); j++)
        {
            if(s[i]!=sub[j])
            {
                break;
            }
            if(j == sub.size()-1)
            {
                return i;
            }
        }
    }
    return -1;
}

string slice(string s, int start, int end)
{
    string result = "";
    for(int i = start; i < end; i++)
    {
        result += s[i];
    }
    return result;
}

vector<string> split(string s, char sep=' ')
{
    vector<string> result;
    string val = "";
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == sep)
        {
            result.push_back(val);
            val = "";
            continue;
        }
        val += s[i];
    }
    if(val != "")
    {
        result.push_back(val);
    }
    return result;
}

int main()
{
    string filepath;
    cout << "Input path to file ";
    cin >> filepath;
    ifstream file(filepath);
    string val;
    int count = 0;
    
    while (getline(file, val, '\n'))
    {
        int s1 = findInd(val, "//", 0, val.size());
        if(s1 < 0)
        {
            continue;
        }
        val = slice(val, s1+2, val.size());
        
        vector<string> result = split(val, ' ');
        
        for(string el : result)
        {
            if(el.size()!=0)
            {
                count += 1;
            }
        }
    }
    cout << count << '\n';
    return 0;
}
