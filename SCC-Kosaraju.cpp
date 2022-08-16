#include <bits/stdc++.h>
using namespace std;
/*
SCC를 구하는 알고리즘 중 Kosaraju's Algorithm
Reference: https://justicehui.github.io/hard-algorithm/2019/01/04/SCC_1/
https://www.acmicpc.net/problem/2150 : 이 문제를 해결하면서 이해하자
*/
int V, E;
vector<int> g[10005]; //그래프
vector<int> gp[10005]; //역방향 그래프
bool visit[10005];
vector<int> order; //finish time 순
int SCC[10005];

void dfs(int now)
{
    if(visit[now]) return ;
    visit[now]=1;
    for(auto nxt : g[now]) dfs(nxt);
    order.push_back(now);
}

void dfs_rev(int now, int num)
{
    if(visit[now]) return ;
    visit[now]=1;
    SCC[now]=num;
    for(auto nxt : gp[now]) dfs_rev(nxt, num);
}

int main()
{
    cin>>V>>E;
    while(E--)
    {
        int a, b; cin>>a>>b;
        g[a].push_back(b);
        gp[b].push_back(a);
    }

    for(int i=1;i<=V;i++) dfs(i);
    memset(visit, 0, sizeof(visit));
    reverse(order.begin(), order.end());
    int num=0;
    for(auto i : order) dfs_rev(i, ++num);
    
    cout<<num<<'\n';
    vector<vector<int>> ans(num);
    for(int i=1;i<=V;i++) ans[SCC[i]-1].push_back(i);
    for(int i=0;i<num;i++) sort(ans[i].begin(), ans[i].end());
    sort(ans.begin(), ans.end());
    for(auto v : ans)
    {
        for(auto i : v) cout<<i<<' ';
        cout<<"-1\n";
    }
    return 0;
}