/*
다익스트라 알고리즘
Reference: 프로그래밍 대회에서 배우는 알고리즘 문제해결전략2 p921
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_V=1000;
const int INF=987654321;
/*
다익스트라의 최단 거리 알고리즘의 구현
구조는 아래와 같이 bfs와 크게 다르지 않다. 다만, 큐 대신에 우선순위 큐를 사용한다는 점이 다르다.
O(|E|lg|V|)
*/
int V; //정점의 개수
vector<pair<int, int>> adj[MAX_V]; //그래프의 인접 리스트, (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<int> dijkstra(int src)
{
    vector<int> dist(V, INF);
    priority_queue<pair<int, int>> pq; //(-거리, 정점 번호) 쌍을 담는다.
    dist[src]=0;
    pq.push({0, src});
    while(!pq.empty())
    {
        int cost=-pq.top().first; 
        int here=pq.top().second;
        pq.pop();
        if(cost>dist[here]) continue; //만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다.
        for(int i=0;i<adj[here].size();i++) //인접한 정점들을 모두 검사한다. 
        {
            int there=adj[here][i].first;
            int nextDist=cost+adj[here][i].second;
            if(nextDist<dist[there]) //더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣는다.
            {
                dist[there]=nextDist;
                pq.push({-nextDist, there}); //거리가 작은 정점부터 꺼내지도록 부호를 바꾸기, C++ STL의 우선순위 큐는 최대힙으로 구현되어 있다.
            }
        }
    }
    return dist;
}

/*
우선순위 큐를 사용하지 않는 다익스트라 알고리즘의 구현
정점의 수가 적거나 간선의 수가 매우 많은 경우에는 아예 우선순위 큐를 사용하지 않고 구현하는 것이 더 빠른 경우가 있다.
다음에 방문할 정점을 별도의 큐에 보관하는 대신 매번 반복문을 이용해 방문하지 않은 정점 중 dist[]가 가장 작은 값을 찾는다.
O(|V|^2+|E|)
*/
vector<int> dijkstra2(int src)
{
    vector<int> dist(V, INF);
    vector<bool> visited(V, false); //각 정점을 방문했는지 여부를 저장한다.
    dist[src]=0; visited[src]=false;
    while(true)
    {
        int closest=INF, here;
        for(int i=0;i<V;i++) //아직 방문하지 않은 
        {
            if(dist[i]<closest && !visited[i])
            {
                here=i;
                closest=dist[i];
            }
        }
        if(closest==INF) break;
        visited[here]=true; //가장 가까운 정점을 방문한다.
        for(int i=0;i<adj[here].size();i++)
        {
            int there=adj[here][i].first;
            if(visited[there]) continue;
            int nextDist=dist[here]+adj[here][i].second;
            dist[there]=min(dist[there], nextDist);
        }
    }
    return dist;
}
 