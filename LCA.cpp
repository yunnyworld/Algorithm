#include <bits/stdc++.h>
using namespace std;
/*
Lowest Common Ancestor (LCA)

Reference: 
ICPC Shinchon 2022 Summer 10회차
https://justicehui.github.io/medium-algorithm/2019/03/28/LCA/

- 가장 낮은 공통 조상
- 트리의 두 정점 u, v의 공통 조상 중 가장 낮은 정점
- LCA를 구하는 방법
    - u와 v의 깊이가 다른 경우, 깊이를 동일하게 맞춘다.
    - u와 v가 동시에 한 칸씩 올라가면서 처음으로 u = v가 되는 지점이 LCA
    - 시간 복잡도: O(n) + O(n) = O(n)
*/
//int depth[100005];
//int p[100005];

int LCA(int u, int v)
{
    if(depth[u]<depth[v]) swap(u, v); //무조건 정점 u가 더 깊다
    while(depth[u]>depth[v]) u=p[u];
    while(u!=v) u=p[u], v=p[v];
    return u;
}
/*
Sparse Table을 이용한 LCA 최적화: O(logn)

- p[j][i] = i의 2^j번째 조상

1. u, v의 깊이가 다르다면, 깊은 정점을 부모 쪽으로 옮겨 높이를 맞춘다.
    - 깊이의 차이를 k라고 하면 깊은 정점을 k번째 조상으로 옮기면 된다. O(logn)
2. u, v를 동시에 부모 쪽으로 옮기며 처음으로 u = v가 되는 정점을 찾는다.
    - 이분탐색을 이용한다. O(logn)
    - k = logn, logn - 1, ... , 0 차례로 보면서 p[k][u]!=p[k][v] 이면 옮김
    - p[0][u] = p[0][v] = LCA
*/
int n, q;
int d[100005];
int p[22][100005]; //log(2*1e6) = 21
vector<int> g[100005];

void dfs(int v, int b=-1)
{
    for(auto i : g[v]) if(i!=b) d[i]=d[v]+1, p[0][i]=v, dfs(i, v);
}

int LCA(int u, int v)
{
    if(d[u]<d[v]) swap(u, v);
    int diff=d[u]-d[v];
    for(int i=0;i<22;i++) if(diff&(1<<i)) u=p[i][u];
    if(u==v) return u;
    for(int i=21;i>=0;i--) if(p[i][u]!=p[i][v]) u=p[i][u], v=p[i][v];
    return p[0][u];
}

int main()
{
    cin>>n;
    for(int i=1, s, e;i<n;i++) cin>>s>>e, g[s].push_back(e), g[e].push_back(s);
    dfs(1); //루트의 정점번호가 1
    for(int i=1;i<22;i++) for(int j=1;j<=n;j++) p[i][j]=p[i-1][p[i-1][j]]; //전처리
    
    cin>>q;
    while(q--)
    {
        int u, v; cin>>u>>v;
        cout<<LCA(u, v)<<'\n';
    }

    return 0;
}
