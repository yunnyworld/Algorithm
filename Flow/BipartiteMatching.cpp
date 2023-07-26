/*
https://www.acmicpc.net/problem/2188
*/
#include <bits/stdc++.h>
#define ll long long int
using namespace std;

ll n, m, ans;
ll A[205], B[205];
vector<ll> g[205];
bool v[205];

bool dfs(ll a)
{
	v[a] = 1;
	for (auto b : g[a])
		if (B[b] == -1 || (!v[B[b]] && dfs(B[b])))
		{
			A[a] = b;
			B[b] = a;
			return 1;
		}
	return 0;
}

void solve()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		ll s; cin >> s;
		for (int j = 0; j < s; j++)
		{
			ll x; cin >> x;
			g[i].push_back(x);
		}
	}
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));
	for (int i = 1; i <= n; i++)
	{
		if (A[i] == -1)
		{
			memset(v, 0, sizeof(v));
			if (dfs(i)) ans++;
		}
	}
	cout << ans;
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
