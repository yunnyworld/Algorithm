#include <bits/stdc++.h>
using namespace std;
/*
Reference: 프로그래밍 대회에서 배우는 알고리즘 문제해결전략 p946

벨만-포드 알고리즘은 음수 간선이 있는 그래프에 대해서도 최단 경로를 찾을 수 있으며, 그래프에 음수 사이클이 있어서 최단 거리가 제대로 정의되지 않을 경우 이것도 알려준다.
*/
const int MAX_V=1000;
const int INF=987654321;

int v; //정점의 개수
vector<pair<int, int>> adj[MAX_V]; //그래프의 인접 리스트 (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<int> bellmanFord(int src) //음수 사이클이 있을 경우 텅 빈 배열을 반환
{
    vector<int> upper(v, INF); //시작점을 제외한 모든 정점까지의 최단 거리 상한을 INF로 둔다.
    upper[src]=0;
    bool updated;
    for(int iter=0;iter<v;iter++)
    {
        updated=false;
        for(int here=0;here<v;here++)
            for(int i=0;i<adj[here].size();i++)
            {
                int there=adj[here][i].first;
                int cost=adj[here][i].second;
                if(upper[there]>upper[here]+cost) 
                {
                    upper[there]=upper[here]+cost;
                    updated=true;
                }
            }
        if(!updated) break; //모든 간선에 대해 완화가 실패했을 경우 v-1번도 돌 필요 없이 곧장 종료한다.
    }
    if(updated) upper.clear(); //v번째 순회에서도 완화가 성공했다면 음수 사이클이 있다.
    return upper;
}
 