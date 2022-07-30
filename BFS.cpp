//큐, 재귀함수, 인접 리스트(벡터 배열)을 이용한 bfs
#include <bits/stdc++.h>
#define ll long long int
#define pii pair<int, int>
#define X first
#define Y second
using namespace std;
//1차원 bfs
bool check[100];
vector<int> g[100];
void bfs(int x)
{
  queue<int> q;
  q.push(x);
  check[x]=true;
  while(!q.empty())
  {
    int y=q.front();
    q.pop();
    for(int i=0;i<g[y].size();i++)
    {
      int z=g[y][i];
      if(check[z]==false)
      {
        q.push(z);
        check[z]=true;
      }
    }
  }
}
//2차원 bfs
int dx[]={0, 0, -1, 1};
int dy[]={-1, 1, 0, 0};
int n, m, a[10][10], b[10][10];
void bfs()
{
    queue<pii> q;
    for(int i=0;i<n;i++) for(int j=0;j<m;j++)
    {
        b[i][j]=a[i][j];
        if(b[i][j]==2) q.push(make_pair(i, j));
    }
    while(!q.empty())
    {
        int x=q.front().X;
        int y=q.front().Y;
        q.pop();
        for(int i=0;i<4;i++)
        {
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(0<=nx && nx<n && 0<=ny && ny<m)
            {
                if(b[nx][ny]==0) 
                {
                    b[nx][ny]=2;
                    q.push(make_pair(nx, ny));
                }
            }
        }
    }
} 