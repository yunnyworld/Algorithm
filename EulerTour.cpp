#include <bits/stdc++.h>
using namespace std;
const int MAX_V=10000;
/*
Euler Tour Technique
Reference: ICPC Shinchon 2022 Summer 중급 10회차

루트부터 dfs로 트리를 순회한다.
각 정점에 들어가고(in(v)) 나가는(out(v)) 시간을 기록한다.
v의 자손들은 in(v)와 out(v) 사이에 존재한다.
in(v)와 out(v) 사이에는 v의 자손들만 존재한다.
v의 서브트리를 수열의 구간으로 생각할 수 있다.
*/

vector<int> childs[MAX_V];
int cnt;
int in[MAX_V], out[MAX_V];

void dfs(int now)
{
    cnt++;
    in[now]=cnt;
    for(int i : childs[now]) dfs(i);
    out[now]=cnt;
}
