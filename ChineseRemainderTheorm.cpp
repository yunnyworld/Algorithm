#include <bits/stdc++.h>
#define ll long long int
using namespace std;
/*
중국인의 나머지 정리

{a1, a2, ... , an}, {m1, m2, ... , mn} 이 주어지면 a=ai (mod mi)를 만족하는 a를 구하는 방법
- a=a1 (mod m1), a=a2 (mod m2)를 만족하는 a를 구할 수 있으면
- 그 방법을 n-1번 적용해서 전체 문제를 해결할 수 있다
- n=2인 문제만 생각하자

a=a1 (mod m1) <-> a=a1+m1x 를 만족하는 정수 x 존재
a=a2 (mod m2) <-> a=a2-m2y 를 만족하는 정수 y 존재
연립하면 m1x+m2y=a2-a1
- a2-a1=0 (mod gcd(m1, m2)) 이면 해 존재, 아니면 해 없음
- 확장 유클리드로 x 구한 다음, a=a1+m1x 계산하면 된다
- a는 0이상 lcm(m1, m2)미만에서 유일하다 -> 증명은 나중에 해보자
m1x+m2y=gcd(m1, m2) * ((a2-a1)/gcd(m1, m2))

Reference: 
ICPC Sinchon 22 Summer 5회차 정수론
https://seastar105.tistory.com/66 -> 나중에 읽어보기
*/
ll mod(ll x, ll m)
{
    return x%m>=0?x%m:x%m+m;
}

tuple<ll, ll, ll> ext_gcd(ll a, ll b)
{
    if(b==0) return {a, 1, 0};
    auto [g, x, y]=ext_gcd(b, a%b);
    return {g, y, x-(a/b)*y};
}

pair<ll, ll> crt(ll a1, ll m1, ll a2, ll m2)
{
    ll g=gcd(m1, m2), m=m1/g*m2;
    if((a2-a1)%g) return {-1, -1};
    ll mul=mod((a2-a1)/g, m2);
    ll x=mod(get<1>(ext_gcd(m1, m2)), m2)*mul%m2;
    return {(a1+m1*x)%m, m};
}

pair<ll, ll> crt(const vector<ll> &a, const vector<ll> &m)
{
    ll ra=a[0], rm=m[0];
    for(int i=1;i<m.size();i++)
    {
        auto [aa, mm]=crt(ra, rm, a[i], m[i]);
        if(mm==-1) return {-1, -1};
        else tie(ra, rm)=tie(aa, mm);
    }
    return {ra, rm};
}
