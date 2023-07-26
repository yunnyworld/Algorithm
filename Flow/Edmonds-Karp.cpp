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
                if(par[nxt]==-1 && c[now][nxt]-f[now][nxt]>0)
                {
                    q.push(nxt); par[nxt]=now;
                    if(nxt==e) break;
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

/*
struct of Edmonds-karp Algorithm
reference: https://github.com/justiceHui/SSU-SCCC-Study/tree/master/2022-winter-adv    
*/
struct maximum_flow
{
	struct edge_t { int v, c, r; }; // next destination, capacity, index of reverse node
	vector<vector<edge_t>> gph;
	vector<int> dst, prv, idx;
	maximum_flow(int n) : gph(n), dst(n), prv(n), idx(n) {}
	void add_edge(int s, int e, int c1, int c2 = 0)
	{
		gph[s].push_back({ e, c1, (int)gph[e].size() });
		gph[e].push_back({ s, c2, (int)gph[s].size() - 1 }); // reverse edge
	}
	int augment(int s, int t)
	{
		fill(dst.begin(), dst.end(), -1);
		queue<int> que; 
		que.push(s); dst[s] = 0;
		while (!que.empty())
		{
			int v = que.front(); que.pop();
			for (int i = 0; i < gph[v].size(); i++)
			{
				const auto& e = gph[v][i];
				if (e.c > 0 && dst[e.v] == -1)
				{
					que.push(e.v); dst[e.v] = dst[v] + 1;
					prv[e.v] = v; idx[e.v] = i;
				}
			}
		}
		if (dst[t] == -1) return 0;
		int flow = 1e9;
		for (int i = t; i != s; i = prv[i])
		{
			const auto& e = gph[prv[i]][idx[i]];
			flow = min(flow, e.c);
		}
		for (int i = t; i != s; i = prv[i])
		{
			auto& e = gph[prv[i]][idx[i]];
			e.c -= flow;
			gph[e.v][e.r].c += flow;
		}
		return flow;
	}
	int run(int s, int t)
	{
		int flow = 0, path = 0;
		while (path = augment(s, t)) flow += path;
		return flow;
	}
};
