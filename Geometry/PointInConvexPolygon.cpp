#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll>
#define X first
#define Y second
using namespace std;
/*
Reference: https://blog.naver.com/vermeil_/222998313068
*/
bool isInCh(vector<pii> &v, pii pt) //v에는 반시계 방향으로 정렬된 점들이 들어있다.
{
    if (v.empty()) return false;
    if (v.size() == 1) return v[0] == pt;
    if (v.size() == 2) return ccw(v[0], v[1], pt) == 0 && v[0] <= pt && pt <= v[1];

    int vs = v.size();
    if (ccw(v[vs - 1], v[0], pt) < 0 || ccw(v[0], v[1], pt) < 0) return false;
    int lo = 1, hi = vs - 1;
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        if (ccw(v[0], v[mid], pt) >= 0) lo = mid + 1;
        else hi = mid;
    }
    return ccw(v[lo - 1], v[lo], pt) >= 0;
}
