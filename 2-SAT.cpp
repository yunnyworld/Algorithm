#include <bits/stdc++.h>
using namespace std;
/*
2-SAT(2-SATisfiability)

- 충족 가능성 문제는 여러 개의 boolean변수들로 이루어진 식이 있을 때 
  각 변수에 값을 할당하여 식을 참으로 만드는 조합을 찾거나, 그러한 조합이 없음을 핮는 문제이다.

¬ k-SAT
    - 한 절에 최대 k개의 변수가 들어간 충족 가능성 문제
    - 임의의 SAT 문제는 3-SAT으로 바꿀 수 있다. 3-SAT은 NP-Complete
    - 하지만 2-SAT은 선형 시간에 해결할 수 있다.

- 2-SAT
    - (A v B) 꼴의 여러 개가 and 연산으로 연결되어 있다.
    - 각각의 절을 모두 참으로 만들어야 한다.

    - (A v B) <=> (~A => B) ^ (~B => A)
        - 둘 중 하나는 참이 되어야 한다.
        - A가 거짓이면 B는 참, B가 거짓이면 A는 참
        - A v B 꼴의 식보다는 A => B 꼴의 식으로 생각하는 것이 편하다. 
    
    - (A v B) ^ (~B v A)
        - ~A => B => A
        - 변수 A만 놓고 보면 ~A => A
        - ~A가 거짓이면 B는 아무거나 될 수 있으므로 A = true로 하면 충족 가능
    
    - (A v B) ^ (~B v A) ^ (~A V B) ^ (~B v ~A)
        - ~A => B => A => B => ~A
        - 변수 A만 놓고 보면 ~A => A => ~A
        - A가 어떤 값이 되더라도 충족 불가능
    
    - ~A => A 이고(and) A => ~A 이면 충족 불가능
    
    - SCC를 쓰면 된다.  

    - 그래프 구성
        - 각 변수 X_i마다 X_i를 나타내는 정점과 ~X_i를 만족하는 정점을 만들고
        - (A v B) 주어지면 ~A => B, ~B => A 간선 생성
        - X_i와 ~ X_i가 같은 SCC에 속하면 불가능, 아니면 가능하다.

    - 변수 값 추적
        - X_i와 ~X_i는 서로 다른 SCC에 속한다.
        - 만약 X_i가 속한 SCC가 위상 정렬 상에서 뒤에 있으면 ~X_i => X_i 이므로 X_i = true
        - 만약 X_i가 속한 SCC가 위상 정렬 상에서 앞에 있으면 X_i => ~X_i 이므로 X_I = false

reference: 
https://justicehui.github.io/hard-algorithm/2019/05/17/2SAT/
ICPC Shinchon 2022 Summer 중급
https://www.acmicpc.net/problem/11280 : 이 문제를 해결하면서 이해하자
*/

int notX(int x){return x^1;}
int trueX(int x){return x<<1;}
int falseX(int x){return (x<<1)|1;}

int n, m;
int num[200005];
int low[200005];
int cnt;
bool visit[200005];
vector<int> g[200005];
stack<int> s;
int SCC[200005];
int SCCcnt;

void dfs(int now) //Tarjan's Algorithm
{
    num[now]=++cnt;
    low[now]=cnt;
    visit[now]=1;
    s.push(now);

    for(auto nxt : g[now])
    {
        if(!num[nxt])
        {
            dfs(nxt);
            low[now]=min(low[now], low[nxt]);
        }
        else if(visit[nxt]) low[now]=min(low[now], num[nxt]);
    }

    if(num[now]==low[now])
    {
        SCCcnt++;
        while(!s.empty())
        {
            int poped=s.top(); s.pop();
            visit[poped]=0;
            SCC[poped]=SCCcnt;
            if(now==poped) break;
        }
    }
}

int main()
{
    cin>>n>>m;
    while(m--)
    {
        int a, b; cin>>a>>b;
        if(a>0) a=trueX(a);
        else a=falseX(-a);
        if(b>0) b=trueX(b);
        else b=falseX(-b);

        g[notX(a)].push_back(b); //~A => B
        g[notX(b)].push_back(a); //~B => A
    }

    for(int i=1*2;i<=n*2+1;i++) if(!num[i]) dfs(i);

    for(int i=1;i<=n;i++)
        if(SCC[trueX(i)] && SCC[trueX(i)]==SCC[falseX(i)])
        {
            cout<<0;
            return 0;
        }
    cout<<1;
    return 0;
}
