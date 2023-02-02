#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll>
#define X first
#define Y second
using namespace std;

ll ccw(pll a, pll b, pll c)
{
	return a.X * b.Y + b.X * c.Y + c.X * a.Y - b.X * a.Y - c.X * b.Y - a.X * c.Y;
}

/*
선분 교차 판정
O(1)
Reference: https://jason9319.tistory.com/358
*/

bool isSegmentIntersect(pll a1, pll a2, pll b1, pll b2)
{
	ll a12 = ccw(a1, a2, b1) * ccw(a1, a2, b2);
	ll b12 = ccw(b1, b2, a1) * ccw(b1, b2, a2);
	if (a12 == 0 && b12 == 0)
	{
		if (a1 > a2) swap(a1, a2);
		if (b1 > b2) swap(b1, b2);
		return a2 >= b1 && b2 >= a1;
	}
	return a12 <= 0 && b12 <= 0;
}
