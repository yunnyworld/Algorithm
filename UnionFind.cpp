#include <bits/stdc++.h>
using namespace std;
/*
Union-Find
Reference: 프로그래밍 대회에서 배우는 알고리즘 문제해결전략2 p769
*/
//랭크에 의한 합치기(union-by-rank) 최적화된 상호 배타적 집합의 구현
//트리를 이용해 상호 배제적 집합을 구현한다.
struct OptimizedDisjointSet
{
    vector<int> parent, rank;
    OptimizedDisjointSet(int n): parent(n), rank(n, 1)
    {
        for(int i=0;i<n;i++) parent[i]=i;
        //u가 속한 트리의 루트의 번호를 반환한다.
        int find(int u) //O(logn)
        {
            if(u==parent[u]) return u;
            return parent[u]=find(parent[u]);
        }
        //u가 속한 트리와 v가 속한 트리를 합친다.
        void merge(int u, int v) //O(logn)
        {
            u=find(u); v=find(v);
            //u와 v가 이미 같은 집합에 속하는 경우를 걸러낸다.
            if(u==v) return ;
            if(rank[u]>rank[v]) swap(u, v); //항상 rank[u]가 작으므로 u를 v의 자식으로 넣는다.
            parent[u]=v;
            if(rank[u]==rank[v]) rank[v]++;
        }
    }
};

/*
구현이 더 간단하다
Reference: 라이 블로그
https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=kks227&logNo=220791837179
*/
int p[50]; //-1로 초기화

int find(int n) //O(1)
{
    if(p[n]<0) return n;
    p[n]=find(p[n]); //경로 압축(path compression)
    return p[n];
}

void merge(int a, int b) //O(1)
{
    a=find(a);
    b=find(b);
    if(a==b) return ;
    p[a]+=p[b]; //루트가 -(집합 크기) 값을 갖고 있도록 해서, 집합 크기를 저장할 수 있다.
    p[b]=a;
}