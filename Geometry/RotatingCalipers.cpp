#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll>
#define X first
#define Y second
using namespace std;
/*
회전하는 캘리퍼스(Rotating Calipers) 알고리즘
: 회전하는 캘리퍼스는 볼록 껍질의 최대 직경을 구하는 알고리즘이다.
O(n)
Reference: https://lem0nad3.tistory.com/131
*/
pll operator + (const pll a, const pll b)
{
    return {a.X + b.X, a.Y + b.Y};
}

pll operator - (const pll a, const pll b)
{
    return {a.X - b.X, a.Y - b.Y};
}

ll dist(const pll a, const pll b)
{
    return (a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y);
}

ll ccw(const pll a, const pll b)
{
    return a.X * b.Y + b.X * c.Y + c.X * a.Y - a.X * c.Y - b.X * a.Y - c.X * b.Y;
}

vector<pll> v; //볼록 껍질 위의 점만 있어야 한다. 
int n = v.size();
int r = 0;
ll ans = 0;

void RotatingCalipers()
{
    for (int i = 0; i < n; i++)
    {
        // A, B, D - C + B
        while (r < n * 2 && ccw(v[i], v[(i + 1) % n],  v[(i + 1) % n] + v[(r + 1) % n] - v[r % n]) >= 0)
        {
            ans = max(ans, dist(v[i], v[r % n])); // A, D
            r++;
        }
        ans = max(ans, dist(v[i], v[r % n]));
    }
}
