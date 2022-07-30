#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll>
#define pii pair<int, int>
#define X first
#define Y second
using namespace std;
int dx[]={-1, 1, 0, 0};
int dy[]={0, 0, -1, 1};
/*
삼분 탐색
- 최소값 또는 최대값이 하나인 함수에서 최소/최대값을 찾는 방법
- 이분 탐색과 비슷하지만, 삼등분을 한다.
*/
//최대값을 찾는 경우 아래와 같이 동작한다.
void TernarySearch()
{
    double left, right;
    while(true)
    {
        if(abs(right-left)<1e-9) return (left+right)/2;
        double m1=left+(right-left)/3;
        double m2=right-(right-left)/3;
        if(f(m1)<f(m2)) left=m1;
        else right=m2;
    }
}