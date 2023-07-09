#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll>
using namespace std;

/*
reference: https://lem0nad3.tistory.com/130?category=1076804
*/
bool cmp(pll a, pll b)
{
	if ((a.X < 0) != (b.X < 0)) return a.X > b.X;
	if (a.X == 0 && b.X == 0) return a.Y < b.Y;
	return a.Y * b.X < b.Y * a.X;
}
