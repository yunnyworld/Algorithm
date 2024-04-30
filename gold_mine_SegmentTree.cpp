#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e18;

/*
왼쪽 끝점을 포함 할 때의 구간합 최대 ls
오른쪽 끝점을 포함 할 때의 구간합 최대 rs
어떤 구간에서의 구간합 최대 ms
구간의 합 s
*/
struct node
{
    ll ls=-INF, rs=-INF, ms=-INF, s=0;
};
ll a[100005];
node tree[400005];

void init(ll x, ll s, ll e)
{
    if(s==e) tree[x]={a[s], a[s], a[s], a[s]};
    else
    {
        init(x*2, s, (s+e)/2);
        init(x*2+1, (s+e)/2+1, e);
        tree[x].ls=max(tree[x*2].ls, tree[x*2].s+tree[x*2+1].ls);
        tree[x].rs=max(tree[x*2+1].rs, tree[x*2+1].s+tree[x*2].rs);
        tree[x].ms=max(max(tree[x*2].ms, tree[x*2+1].ms), tree[x*2].rs+tree[x*2+1].ls);
        tree[x].s=tree[x*2].s+tree[x*2+1].s;
    }
}

node query(ll x, ll s, ll e, ll l, ll r)
{
    if(s>r || e<l) return {-INF, -INF, -INF, 0};
    if(l<=s && e<=r) return tree[x];
    node L=query(x*2, s, (s+e)/2, l, r);
    node R=query(x*2+1, (s+e)/2+1, e, l, r);
    node ret;
    ret.ls=max(L.ls, L.s+R.ls);
    ret.rs=max(R.rs, R.s+L.rs);
    ret.ms=max(max(L.ms, R.ms), L.rs+R.ls);
    ret.s=L.s+R.s;
    return ret;
}
