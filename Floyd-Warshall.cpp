/*
플로이드 알고리즘
Reference: 프로그래밍 대회에서 배우는 알고리즘 문제해결전략2 p952
*/
#include <bits/stdc++.h>
#define ll long long int
using namespace std;
const int MAX_V=1000;
/*
플로이드 알고리즘의 프로토타입
O(|v|^3)
*/
int v; //정점의 개수
int adj[MAX_V][MAX_V]; //그래프의 인접 행렬 표현, adj[u][v]=u에서 v로 가는 간선의 가중치, 간선이 없으면 아주 큰 값을 넣는다.
int c[MAX_V][MAX_V][MAX_V];
void allPairShortestPath1()
{
    for(int i=0;i<v;i++) for(int j=0;j<v;j++) //c[0]를 초기화
    if(i!=j) c[0][i][j]=min(adj[i][j], adj[i][0]+adj[0][j]);
    else c[0][i][j]=0;
    //c[k-1]이 있으면 c[k]를 계산할 수 있다.
    for(int k=1;k<v;k++) for(int i=0;i<v;i++) for(int j=0;j<v;j++)
        c[k][i][j]=min(c[k-1][i][k]+c[k-1][k][j], c[k-1][i][j]);
}

/*
슬라이딩 윈도우 기법을 사용해 메모리 사용량 줄이기 
1. c[k]의 답은 c[k-1]만 있으면 계산 할 수 있기 때문이다. 공간복잡도가 O(|v|^3) --> O(2*|v|^2) 와 같이 줄어든다.
2. c[k-1][u][k]=시작점부터 k-1번 정점까지를 경유점으로 이용해 u에서 k로 가는 최단경로의 길이
   c[k][u][k]=시작점부터 k번 정점까지를 경유점으로 이용해 u에서 k로 가는 최단경로의 길이
   이므로, c[k-1][u][k]에서 사용 가능한 경우점의 목록에 k가 추가되는 것은 아무 의미가 없다.
   따라서 c[(k-1)%2]과 c[k%2]를 구분하지 않고 섞어서 써도 된다.

최적화: 두 번째 for문 바로 다음에 i에서 k로 가는 경로가 실제 있는지 확인해보고, 없다면 j에 대한 for문은 생략한다.
*/
int v; //정점의 개수
int adj[MAX_V][MAX_V]; //그래프의 인접 행렬 표현, adj[u][v]=u에서 v로 가는 간선의 가중치, 간선이 없으면 아주 큰 값을 넣는다.
/*
플로이드의 모든 쌍 최단거리 알고리즘
O(2*|v|^2)
*/
void floyd()
{
    for(int i=0;i<v;i++) adj[i][i]=0;
    for(int k=0;k<v;k++) for(int i=0;i<v;i++) for(int j=0;j<v;j++)
        adj[i][j]=min(adj[i][j], adj[i][k]+adj[k][j]);
}

/*
플로이드 알고리즘에서 실제 최단 경로 계산하기
플로이드 알고리즘을 수행 한 뒤 두 정점 사이의 최단 경로를 계산하기 위해서는 각 정점의 쌍 u, v에 대해 마지막으로 adj[u][v]를 갱신했을 때 사용했던 k의 값을 저장해두면 된다.
이 정점의 번호를 w라 할 때, 재귀 호출을 이용해 u에서 w로 가는 최단 경로를 찾고, w에서 v로 가는 최단 경로를 찾은 뒤 이 둘을 합치면 u에서 v로 가는 최단 경로를 얻을 수 있다.
*/
int v; //정점의 개수
int adj[MAX_V][MAX_V]; //그래프의 인접 행렬 표현, adj[u][v]=u에서 v로 가는 간선의 가중치, 간선이 없으면 아주 큰 값을 넣는다.
int via[MAX_V][MAX_V]; //via[u][v]=u에서 v까지 가는 최단 경로가 경유하는 점 중 가장 번호가 큰 정점, -1로 초기화 해 둔다.
//플로이드의 모든 쌍 최단 거리 알고리즘
void floyd2()
{
    for(int i=0;i<v;i++) adj[i][i]=0;
    memset(via, -1, sizeof(via));
    for(int k=0;k<v;k++) for(int i=0;i<v;i++) for(int j=0;j<v;j++)
        if(adj[i][j]>adj[i][k]+adj[k][j])
        {
            via[i][j]=k;
            adj[i][j]=min(adj[i][j], adj[i][k]+adj[k][j]);
        }
}
//u에서 v로 가는 최단 경로를 계산해 path에 저장한다.
void reconstruct(int u, int v, vector<int> &path)
{
    //기저사례
    if(via[u][v]==-1)
    {
        path.push_back(u);
        if(u!=v) path.push_back(v); //u!=v인데, via[u][v]==-1 이라는 뜻은 u에서 다른 정점을 경유하지 않고 바로 v로 갔다는 의미이다.
    }
    else
    {
        int w=via[u][v];
        reconstruct(u, w, path);
        path.pop_back(); //w가 중복으로 들어가므로 지운다.
        reconstruct(w, v, path);
    }
}

/*
플로이드 알고리즘을 이용해서 도달 가능성 확인하기
c[k][u][v]를 0번부터 k번 정점까지를 경유점으로 썼을 때, u에서 v로 가는 경로가 존재 유무라 하자.
c[k][u][v]=c[k-1][u][v] || (c[k-1][u][k] && c[k-1][k][v]) 의 점화식이 성립한다.
시간 복잡도 면에서 모든 정점에서 시작해 bfs하는 방법보다 나을 것이 없지만, 간결한 구현 덕분에 유용하게 쓰인다.
*/
