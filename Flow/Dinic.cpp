#include <bits/stdc++.h>
using namespace std;
/*
Dinic Algorithm
Time Complexity: O(V^2E)
Reference: https://github.com/justiceHui/SSU-SCCC-Study/blob/master/2022-winter-adv/slide/04.pdf
*/
struct Dinic
{
	struct edge_t { int v, c, r; };
	int n;
	vector<vector<edge_t>> g;
	vector<int> lv, idx;
	Dinic(int n):n(n), g(n + 1), lv(n + 1), idx(n + 1) {}
	void add_edge(int s, int e, int c1, int c2 = 0)
	{
		g[s].push_back({ e, c1, (int)g[e].size() });
		g[e].push_back({ s, c2, (int)g[s].size() - 1 });
	}
	bool bfs(int s, int t)
	{
		fill(lv.begin(), lv.end(), 0);
		queue<int> que; 
		que.push(s); lv[s] = 1;
		while (!que.empty())
		{
			int v = que.front(); que.pop();
			for (const auto& e : g[v])
				if (!lv[e.v] && e.c != 0) que.push(e.v), lv[e.v] = lv[v] + 1;
		}
		return lv[t];
	}
	int dfs(int v, int t, int f = 1e9)
	{
		if (v == t || f == 0) return f;
		for (int& i = idx[v]; i < g[v].size(); i++)
		{
			auto& e = g[v][i];
			if (lv[e.v] != lv[v] + 1 || e.c == 0) continue;
			int now = dfs(e.v, t, min(f, e.c));
			if (now == 0) continue;
			e.c -= now;
			g[e.v][e.r].c += now;
			return now;
		}
		return 0;
	}
	int run(int s, int t)
	{
		int flow = 0, path = 0;
		while (bfs(s, t))
		{
			fill(idx.begin(), idx.end(), 0);
			while (path = dfs(s, t)) flow += path;
		}
		return flow;
	}
};
