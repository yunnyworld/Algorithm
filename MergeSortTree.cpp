/*
머지 소트 트리
- 각 노드가 한 값이 아닌 리스트를 들고 있는 세그먼트 트리
- 자신이 의미하는 구간에 들어있는 모든 값들을 정렬된 형태로 들고 있다.
값의 개수가 N일때, 
- 시간복잡도: O(NlgN)
- 공간복잡도: O(NlgN), 트리의 깊이 O(lgN) * 각 깊이의 노드에 있는 값의 개수 N개
Reference: 
https://m.blog.naver.com/kks227/221400656663 (설명)
https://nicotina04.tistory.com/126 (구현)
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX=987654321;
/*
머지 소트 트리를 만드는 함수 init
시간복잡도: O(NlgN)
*/
vector<int> a(100000);
vector<int> tree[400000];
void init(int node, int start, int end)
{
    if(start==end) tree[node].push_back(a[start]);
    else 
    {
        init(node*2, start, (start+end)/2);
        init(node*2+1, (start+end)/2+1, end);
        auto &l=tree[node*2], &r=tree[node*2+1];
        tree[node].resize(l.size()+r.size());
        merge(l.begin(), l.end(), r.begin(), r.end(), tree[node].begin());
    }
}
/*
특정 구간에 있는 원소 val의 인덱스를 찾는 함수 query
시간복잡도: O((lgN)^2), 원하는 구간을 찾는데 O(lgN) * 이진 탐색시 O(lgN)
*/
int query(int node, int start, int end, int left, int right, int val)
{
    if(right<start || end<left) return 0;
    if(left<=start && end<=right)
        return lower_bound(tree[node].begin(), tree[node].end(), val)-tree[node].begin();
    int l=query(node*2, start, (start+end)/2, left, right, val);
    int r=query(node*2+1, (start+end)/2+1, end, left, right, val);
    return l+r;
}