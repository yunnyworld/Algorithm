#include <bits/stdc++.h>
#define ll long long int
using namespace std;
/*
Reference: 
https://www.youtube.com/watch?v=qJ_ft3Spcxc
https://plzrun.tistory.com/entry/Counting-Sort-Radix-Sort
*/
struct SuffixArray
{
	ll n;
	string s;
	vector<ll> sfx, g, ng, cnt, idx;
	SuffixArray(string& str)
	{
		s = str;
		n = str.length();
		sfx.resize(n + 1);
		g.resize(2 * n + 1);
		ng.resize(2 * n + 1);
		cnt.resize(n + 1);
		idx.resize(n + 1);
	}
	vector<ll> getsfx()
	{
		s = ' ' + s;
		vector<ll> tmp;
		for (int i = 1; i <= n; i++)
		{
			sfx[i] = i;
			tmp.push_back(s[i]);
		}
		sort(tmp.begin(), tmp.end());
		tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
		for (int i = 1; i <= n; i++)
			g[i] = lower_bound(tmp.begin(), tmp.end(), s[i]) - tmp.begin() + 1;
		for (int i = n + 1; i <= 2 * n; i++) g[i] = 0;
		for (int t = 1; t < n; t *= 2)
		{
			// counting sort by g[i+t] for stable sorting
			for (int i = 0; i <= n; i++) cnt[i] = 0;
			for (int i = 1; i <= n; i++) cnt[g[i + t]]++;
			for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
			for (int i = n; i >= 1; i--) idx[cnt[g[i + t]]--] = i;
			// counting sort by g[i] for stable sorting
			for (int i = 0; i <= n; i++) cnt[i] = 0;
			for (int i = 1; i <= n; i++) cnt[g[i]]++;
			for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
			for (int i = n; i >= 1; i--) sfx[cnt[g[idx[i]]]--] = idx[i];
			// prepare for next update
			ng[sfx[1]] = 1;
			for (int i = 2; i <= n; i++) 
				ng[sfx[i]] = ng[sfx[i - 1]] + (g[sfx[i - 1]] < g[sfx[i]] || (g[sfx[i - 1]] == g[sfx[i]] && g[sfx[i - 1] + t] < g[sfx[i] + t]));
			for (int i = 1; i <= n; i++) g[i] = ng[i];
		}
		return sfx;
	}
};
