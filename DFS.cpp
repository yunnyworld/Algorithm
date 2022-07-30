//재귀함수, 인접 리스트(벡터 배열)를 이용한 dfs
#include <iostream>
#include <vector>
using namespace std;
bool check[100];
vector<int> g[100];
void dfs(int x)
{
  check[x]=true;
  for(int i=0;i<g[x].size();i++)
  {
    int y=g[x][i];
    if(check[y]==false) dfs(y);
  }
}
