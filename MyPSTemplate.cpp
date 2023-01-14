#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll>
#define X first
#define Y second
using namespace std;
const ll INF = 987654321;
const ll MOD = 1e9 + 7;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

void solve()
{
	
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
