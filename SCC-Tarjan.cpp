#include <bits/stdc++.h>
using namespace std;
/*
SCC를 구하는 알고리즘 중 Tarjan's Algorithm

사전 정보 2가지
- num[i] = i번 정점이 몇 번째로 방문한 정점인지 저장 (discover time)
- low[i] = i번 정점을 루트로 하는 서브트리에서 간선 하나만 거쳐서 갈 수 있는 정점 중, 가장 작은 num값을 저장

low값 구하기
- edge(u, v)가 tree edge라면, low[u] = min(low[u], low[v])
- edge(u, v)가 back edge라면, low[u] = min(low[u], num[v])

dfs의 방문순서의 역순으로 한 정점씩 보면서 num값과 low값이 같은 정점이 나온다면, 그 정점까지가 한 SCC이다.

타잔 알고리즘으로 SCC를 구하면 위상 정렬의 역순으로 생성된다.

- O(V+E)

Reference: https://justicehui.github.io/hard-algorithm/2019/01/04/SCC_2/
https://www.acmicpc.net/problem/2150 : 이 문제를 해결하면서 이해하자

SCC를 구하면 좋은 점
- SCC를 정점 하나로 압축하면 임의의 방향 그래프를 DAG로 만들 수 있음 -> DP
- 서로 이동 가능하다는 것 자체가 중요한 경우도 있음
*/
int num[100001];
int low[100001];
bool visit[100001];
int cnt=0;
vector<int> g[100001];
stack<int> s;
vector<vector<int>> ans;

void dfs(int now)
{
    num[now]=++cnt;
    low[now]=cnt;
    visit[now]=1;
    s.push(now);

    for(auto nxt : g[now])
    {
        if(!num[nxt]) //!num[nxt]가 참이라는 뜻은 방문하지 않았다는 뜻이므로 now->nxt가 tree edge라는 뜻이다.
        {
            dfs(nxt);
            low[now]=min(low[now], low[nxt]);
        }
        else if(visit[nxt]) low[now]=min(low[now], num[nxt]);
        /*
        visit[nxt]가 참이라는 뜻은 이미 방문했다는 뜻이므로 now->nxt가 back edge라는 뜻이다.
        num[nxt]가 참인데도 visit[nxt]가 거짓이라는 뜻은 now->nxt가 cross edge라는 뜻이다.
        */
    }

    if(low[now]==num[now]) //한 SCC 완성
    {
        vector<int> SCC;
        while(!s.empty())
        {
            int poped=s.top(); s.pop();
            SCC.push_back(poped);
            visit[poped]=0; //cross edge를 처리하기 위해 필요하다. 반례로는 4013번 문제의 예제1 그래프가 있다.
            if(now==poped) break;
        }
        sort(SCC.begin(), SCC.end());
        ans.push_back(SCC);
    }
}

int main()
{
    int V, E; cin>>V>>E;
    while(E--)
    {
        int a, b; cin>>a>>b;
        g[a].push_back(b);
    }
    
    for(int i=1;i<=V;i++) if(!num[i]) dfs(i);

    cout<<ans.size()<<'\n';
    sort(ans.begin(), ans.end());
    for(auto v : ans)
    {
        for(auto i : v) cout<<i<<' ';
        cout<<"-1\n";
    }
    return 0;
}