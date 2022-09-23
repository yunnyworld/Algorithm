#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll a[100005];
ll tree[400005];
ll lazy[400005];
/*
Lazy Propagation: 구간 [i, j]의 모든 값을 v로 바꾸는 쿼리를 O(logn)에 처리하기
Reference: https://justicehui.github.io/medium-algorithm/2018/08/24/Seg2/
기본적인 아이디어는 "업데이트를 미룬다(lazy)"는 점이다.
*/
void init(ll node, ll s, ll e) //기존 세그먼트 트리 코드와 동일하다. O(nlogn)
{
    if(s==e) tree[node]=a[s];
    else
    {
        init(node*2, s, (s+e)/2);
        init(node*2+1, (s+e)/2+1, e);
        tree[node]=tree[node*2]+tree[node*2+1];
    }
}

void update_lazy(ll node, ll s, ll e) //lazy값을 노드에 적절하게 업데이트하고, 자식들에게 물려준다. O(1)
{
    if(lazy[node]) //업데이트를 해야 할 경우
    {
        tree[node]+=(e-s+1)*lazy[node]; //관할 구역의 개수만큼 더한다.
        if(s!=e) //리프 노드가 아니면, 자식들에게 lazy값을 물려준다.
        {
            lazy[node*2]+=lazy[node];
            lazy[node*2+1]+=lazy[node];
        }
        lazy[node]=0; //업데이트 완료
    }
}

void update_range(ll node, ll s, ll e, ll l, ll r, ll diff) //원하는 범위의 값을 업데이트 한다. O(logn)
{
    update_lazy(node, s, e); //lazy값이 남아있으면 갱신
    if(l>e || s>r) return ;
    if(l<=s && e<=r)
    {
        tree[node]+=(e-s+1)*diff; //그림에서 초록색 노드
        if(s!=e) //자식 노드들은 lazy하게 나중에 필요할 때 하자.
        {
            lazy[node*2]+=diff;
            lazy[node*2+1]+=diff;
        }
    }
    else
    {
        update_range(node*2, s, (s+e)/2, l, r, diff);
        update_range(node*2+1, (s+e)/2+1, e, l, r, diff);
        tree[node]=tree[node*2]+tree[node*2+1];
    }
}

ll query(ll node, ll s, ll e, ll l, ll r) //기존 세그먼트 트리 코드와 동일하다. O(logn)
{
    update_lazy(node, s, e);
    if(l>e || r<s) return 0;
    if(l<=s && e<=r) return tree[node];
    ll lsum=query(node*2, s, (s+e)/2, l, r);
    ll rsum=query(node*2+1, (s+e)/2+1, l, r);
    return lsum+rsum;
}