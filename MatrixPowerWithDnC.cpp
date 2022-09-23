#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD = 1000;

vector<vector<ll>> A(6, vector<ll>(6));

vector<vector<ll>> mul(vector<vector<ll>> &a, vector<vector<ll>> &b)
{
	vector<vector<ll>> ans(6, vector<ll>(6));
	for (ll i = 1; i <= n; i++)
		for (ll j = 1; j <= n; j++)
		{
			for (ll k = 1; k <= n; k++) ans[i][j] += a[i][k] * b[k][j] % MOD;
			ans[i][j] %= MOD;
		}
	return ans;
}

vector<vector<ll>> pow(vector<vector<ll>> &a, ll x)
{
	if (x == 1) return a;
	auto u = pow(a, x / 2);
	u = mul(u, u);
	if (x % 2) u = mul(u, a);
	return u;
}