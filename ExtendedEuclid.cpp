#include <bits/stdc++.h>
#define ll long long int
using namespace std;
/*
확장 유클리드 알고리즘: ax + by = gcd(a, b)의 정수해 (x, y) 중 하나를 구하는 알고리즘

b = 0 이면 ax + 0 = a, (x, y)=(1, 0)
유클리드 호제법의 종료 조건과 동일하다.

proof) ax + by = gcd(a, b) -> bx' + ry' = gcd(b, r) (r = a%b)
1. gcd(a, b) = gcd(b, r) (Euclidean Algorithm)
2. ax + by = bx' + ry'
           = bx' + (a-qb)y' (a=b*q+r, q=[a/b])
           = ay' + b(x'-qy')
   -> (x, y) = (y', x'-qy') = (y', x'-[a/b]y')

위와 같이 
bx' + ry' = gcd(b, r)의 답을 이용해 
ax + by = gcd(a, b)의 답을 구할 수 있으므로
유클리드 호제법과 동일한 방법으로 해결할 수 있다.


선형 디오판토스 방정식
- ax + by = c 의 정수해를 구하는 방정식
- gcd(a, b) | c 일 때만 정수해 존재 (베주 항등식)
- ax + by = gcd(a, b)를 해결할 수 있으면 양변에 c/gcd(a, b) 를 곱함으로써 전체 문제를 해결할 수 있다.

Reference: ICPC Sinchon 22 Summer 5회차 정수론 
*/
//return [g, x, y] s.t. ax+by = gcd(a, b) = g
tuple<ll, ll, ll> ext_gcd(ll a, ll b)
{
    if(b==0) return {a, 1LL, 0LL};
    auto [g, x, y]=ext_gcd(b, a%b);
    return {g, y, x-a/b*y};
}
