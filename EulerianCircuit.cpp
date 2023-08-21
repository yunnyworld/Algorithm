/*
https://www.acmicpc.net/problem/1199
*/
#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int n, s = 1;
int deg[1005];
int mat[1005][1005];
vector<int> g[1005];
vector<int> ans;

void Eulerian(int now)
{
	while (g[now].size())
	{
		int nxt = g[now].back();
		if (mat[now][nxt] == 0) g[now].pop_back();
		else
		{
			mat[now][nxt]--;
			mat[nxt][now]--;
			dfs(nxt);
		}
	}
	ans.push_back(now);
}

void solve()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			int x; cin >> x;
			if (x)
			{
				deg[i] += x;
				g[i].push_back(j);
				mat[i][j] = x;
			}
		}
	for (int i = 1; i <= n; i++)
	{
		if (deg[i] % 2)
		{
			cout << -1;
			return;
		}
		else if (deg[i] > 0) s = i;
	}
	Eulerian(s);
	// 단방향에서는 reverse(all(ans)); 가 필요하다
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	int tc = 1; //cin >> tc;
	while (tc--) solve();
	return 0;
}
