struct centroid
{
	int N;
	vector<int> v, sz;
	vector<vector<pair<int, int>>> g;
	centroid(int N) : N(N), v(N + 1), sz(N + 1), g(N + 1) {}
	int get_sz(int x, int p = -1)
	{
		sz[x] = 1;
		for (auto [y, w] : g[x])
			if (y != p && !v[y]) sz[x] += get_sz(y, x);
		return sz[x];
	}
	int get_cent(int x, int p, int SZ)
	{
		for (auto [y, w] : g[x])
			if (y != p && !v[y] && sz[y] * 2 > SZ) return get_cent(y, x, SZ);
		return x;
	}
	void dnc(int x)
	{
		int cent = get_cent(x, -1, get_sz(x));
		// do something
		v[cent] = 1;
		for (auto [y, w] : g[cent])
			if (!v[y]) dnc(y);
		return;
	}
};
