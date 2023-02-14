#inlcude <bits/stdc++.h>
#define ll long long
using namespace std;
/*
Edmonds-Karp Algorithm: Max Flow 구하기
Reference:
https://justicehui.github.io/tutorial/
https://m.blog.naver.com/kks227/220804885235?referrerCode=1

Ford-Fulkerson 알고리즘은 DFS를 이용해 탐색을 하면 O(V+E)가 들고, 최대 유량을 f라 하면,
시간 복잡도는 O(Ef)가 된다. 만약 f가 매우 큰 수라면 시간이 오래 걸릴 수 있다. 
BFS를 이용해 증가 경로를 탐색한 Edmonds-Karp 알고리즘을 이용하면 O(VE^2)만에 최대 유량을 구할 수 있다.
시간 복잡도의 증명은 지금은 잘 이해 안되니, 나중에 다시 이해해보자.
*/
const ll INF=1e9+7;

vector<ll> g[2005];
ll c[2005][2005]; //용량
ll f[2005][2005]; //유량
ll s=0, e=2001; //source 정점, sink 정점
ll par[2005];
ll ans;

void EdmondsKarp()
{
    for(ll iter=1; ;iter++)
    {
        memset(par, -1, sizeof(par));
        queue<ll> q;
        q.push(s);
        while(!q.empty())
        {
            ll now=q.front(); q.pop();
            for(auto nxt : g[now])
            {
                if(par[nxt]==-1 && c[now][nxt]-f[now][nxt]>0)
                {
                    q.push(nxt); par[nxt]=now;
                    if(nxt==e) break;
                }
            }
        }
        if(par[e]==-1) break; //더 이상 유량을 흘려보낼 수 없다.

        ll cost=INF;
        for(ll i=e;i!=s;i=par[i]) cost=min(cost, c[par[i]][i]-f[par[i]][i]);
        for(ll i=e;i!=s;i=par[i]) 
        {
            f[par[i]][i]+=cost;
            f[i][par[i]]-=cost;
        }
        ans+=cost;
    }
}
