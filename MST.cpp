#include <bits/stdc++.h>
#define ll long long
using namespace std;

int p[100];
int find(int x)
{
    if(p[x]<0) return x;
    return p[x]=find(p[x]);
}
void merge(int a, int b)
{
    a=find(a); b=find(b);
    if(a==b) return ;
    p[b]=a;
}

const int MAX_V=100;
const int INF=987654321;
int V; //정점의 개수
vector<pair<int, int>> adj[MAX_V]; //(연결된 정점 번호, 간선 가중치)

/*
MST(Minimum Spanning Tree)

Kruskal
O(|E|log|E|)
Reference: 프로그래밍 대회에서 배우는 알고리즘 문제해결전략 p973
*/
int kruskal(vector<pair<int, int>>& selected) //MST에 포함된 간선의 목록을 selected에 저장하고, 가중치의 합을 반환한다.
{
    int ret=0;
    selected.clear(); 
    vector<pair<int, pair<int, int>>> edges; //(가중치, (정점1, 정점2))
    for(int u=0;i<V;u++)
        for(int i=0;i<adj[u].size();i++)
        {
            int v=adj[u][i].first; 
            int cost=adj[u][i].second;
            edges.push_back({cost, {u, v}});
        }
    sort(edges.begin(), edges.end());
    for(int i=0;i<edges.size();i++)
    {
        int cost=edges[i].first;
        int u=edges[i].second.fisrt;
        int v=edges[i].second.second;
        if(find[u]==find[v]) continue; //이미 u와 v가 연결되어 있을 경우 무시한다.
        merge(u, v);
        selected.push_back({u, v});
        ret+=cost;
    }
    return ret;
}

/*
Prim 
O(|V|^2|E|)
거의 모든 정점들 사이에 간선이 있는 밀집 그래프의 경우 |E|는 |V|^2이므로, 프림 알고리즘은 이 경우 크루스칼보다 빠르게 동작한다.
Reference: 프로그래밍 대회에서 배우는 알고리즘 문제해결전략 p977
*/
int prim(vector<pair<int, int>>& selected) //MST에 포함된 간선의 목록을 selected에 저장하고, 가중치의 합을 반환한다.
{
    int ret=0; //가중치의 합을 저장할 변수
    selected.clear();
    vector<bool> added(V, false); //해당 정점이 트리에 포함되어 있나?
    vector<int> minWeight(V, INF), parent(V, -1); //트리에 인접한 간선 중 해당 정점에 닿는 최소 간선의 정보를 저장한다.
    minWeight[0]=parend[0]=0;
    for(int iter=0;iter<V;iter++)
    {
        //다음에 트리에 추가할 정점 u를 찾는다.
        int u=-1; 
        for(int v=0;v<V;v++)
            if(!added[v] && (u==-1 || minWeight[v]<minWeight[u])) u=v;
        
        //(parent[u], u)를 트리에 추가한다.
        if(parent[u]!=u) 
            selected.push_back({parent[u], u});
        ret+=minWeight[u];
        added[u]=true;

        //u에 인접한 간선 (u, v)들을 검사한다.
        for(int i=0;i<adj[u].size();i++) 
        {
            int v=adj[u][i].first;
            int weight=adj[u][i].second;
            if(!added[v] && minWeight[v]>weight)
            {
                parent[v]=u;
                minWeight[v]=weight;
            }
        }
    }
    return ret;
}