#include <bits/stdc++.h>
#define ll long long int
using namespace std;
/*
practical
*/
ll a[100005];
ll tree[400005];

void init(ll x, ll s, ll e)
{
    if (s == e) tree[x] = a[s];
    else
    {
        init(x * 2, s, (s + e) / 2);
        init(x * 2 + 1, (s + e) / 2 + 1, e);
        tree[x] = tree[x * 2] + tree[x * 2 + 1];
    }
}

ll query(ll x, ll s, ll e, ll l, ll r)
{
    if (l > e || r < s) return 0ll;
    if (l <= s && e <= r) return tree[x];
    else
    {
        ll lsum = query(x * 2, s, (s + e) / 2, l, r);
        ll rsum = query(x * 2 + 1, (s + e) / 2 + 1, e, l, r);
        return lsum + rsum;
    }
}

void update(ll x, ll s, ll e, ll idx, ll val)
{
    if (idx<s || idx>e) return;
    if (s == e)
    {
        a[idx] = val;
        tree[idx] = val;
    }
    else
    {
        update(x * 2, s, (s + e) / 2, idx, val);
        update(x * 2 + 1, (s + e) / 2 + 1, e, idx, val);
        tree[x] = tree[x * 2] + tree[x * 2 + 1];
    }
}

/*
구간 합을 저장하는 세그먼트 트리 구현
재귀 이용
Reference: https://book.acmicpc.net/ds/segment-tree
LIS(Longest Increasing Subsequence) 구현은 12015.cpp 참고
*/

/*
a: 배열 A, 0번 인덱스부터 시작
tree: 세그먼트 트리, 1번 인덱스부터 시작
node: 노드 번호
node에 저장되어 있는 합의 범위가 [start, end]
*/
/*
세그먼트 트리 만드는 함수 init
시간복잡도: O(n)
*/
void init(vector<long long> &a, vector<long long> &tree, int node, int start, int end)
{
    if(start==end) tree[node]=a[start];
    else
    {
        init(a, tree, node*2, start, (start+end)/2);
        init(a, tree, node*2+1, (start+end)/2+1, end);
        tree[node]=tree[node*2]+tree[node*2+1];
    }
}
/*
세그먼트 트리에서 [left, right]의 합을 구하는 함수 query
시간복잡도: O(lgn)
*/
long long query(vector<long long> &tree, int node, int start, int end, int left, int right)
{
    if(left>end || right<start) return 0;
    if(left<=start && end<=right) return tree[node];
    long long lsum=query(tree, node*2, start, (start+end)/2, left, right);
    long long rsum=query(tree, node*2+1, (start+end)/2+1, end, left, right);
    return lsum+rsum;
}
/*
세그먼트 트리에서 index번째 수를 val로 변경하는 함수 update  - 1번째 방법(위에서부터 업데이트)
시간복잡도: O(lgn)
*/
void update_tree1(vector<long long> &tree, int node, int start, int end, int index, long long diff)
{
    if(index<start || index>end) return ;
    tree[node]=tree[node]+diff;
    if(start!=end)
    {
        update_tree1(tree, node*2, start, (start+end)/2, index, diff);
        update_tree1(tree, node*2+1, (start+end)/2+1, end, index, diff);
    }
}
void update(vector<long long> &a, vector<long long> &tree, int n, int index, long long val)
{
    long long diff=val-a[index];
    a[index]=val;
    update_tree1(tree, 1, 0, n-1, index, diff);
}
/*
세그먼트 트리에서 index번째 수를 val로 변경하는 함수 update  - 2번째 방법(아래서부터 업데이트)
시간복잡도: O(lgn)
*/
void update_tree2(vector<long long> &a, vector<long long> &tree, int node, int start, int end, int index, long long val)
{
    if(index<start || index>end) return ;
    if(start==end)
    {
        a[index]=val;
        tree[node]=val;
        return ;
    }
    update_tree2(a, tree, node*2, start, (start+end)/2, index, val);
    update_tree2(a, tree, node*2+1, (start+end)/2+1, end, index, val);
    tree[node]=tree[node*2]+tree[node*2+1];
}
int main()
{
    int n; cin>>n; //리프 노드의 개수
    vector<long long> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    //tree_size를 미리 정해주지 않으면, segmentation fault가 발생한다.
    int h=(int)ceil(log2(n));
    int tree_size=(1<<(h+1)); //2^(h+1)은 대략 2*n, 걍 편의를 위해 4*n으로 해도 된다.
    vector<long long> tree(tree_size); //이렇게 tree_size를 정해주지 않고 2*n으로 쓰면 포화 이진 트리가 아닌 경우에 공간이 부족하게 된다.
    
    return 0;   
}
