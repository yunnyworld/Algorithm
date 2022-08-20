#include <bits/stdc++.h>
using namespace std;
/*
큐(Queue)를 이용한 위상 정렬(Topology Sort) 구현
Reference : https://m.blog.naver.com/ndb796/221236874984

1. 진입 차수가 0인 정점을 큐에 삽입한다.
2. 큐에서 원소를 꺼내 연결된 모든 간선을 제거한다.
3. 간선 제거 이후, 진입 차수가 0이 된 정점을 큐에 삽입한다.
4. 큐가 빌 때까지 2번~3번 과정을 반복한다.
   모든 원소를 방문하기 전에 큐가 빈다면 사이클이 존재한는 것이고,
   모든 원소를 방문했다면 큐에서 꺼낸 순서가 위상 정렬의 결과이다.

시간복잡도: O(V+E)
*/
int V;
int inDegree[10];
vector<int> adj[10];
vector<int> TopologySort() //위상 정렬의 결과를 리턴
{
    vector<int> ret; 
    queue<int> q;
    
    for(int i=1;i<=V;i++) 
        if(inDegree[i]==0) q.push(i);
    
    while(V--)
    {
        if(q.empty()) 
        {
            cout<<"Cycle exist";
            return ret;
        }

        int x=q.front(); q.pop();
        ret.push_back(x);
        for(auto y : adj[x])
            if(--inDegree[y]==0) q.push(y);
    }
    return ret;
}