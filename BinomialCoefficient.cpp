#include <bits/stdc++.h>
#define ll long long
using namespace std;
/*
이항 계수(Binomial Coefficient)
nCr = n!/r!(n-r)! 를 어떤 수로 나눈 나머지를 빠르게 계산해 보자

1. 소수 p로 나눈 나머지
    - 전처리 O(n + logp), 쿼리 O(1)
    - 전처리 O(p + logp), 쿼리 O(logp)

2. 소수의 거듭제곱 p^e으로 나눈 나머지 
    - 전처리 O(p^e), 쿼리 O(logn + logp)

3. 합성수 m = p1^e1 * p2^e2 * ... pk^ek 로 나눈 나머지
    - 전처리 O(sum(pi^ei)), 쿼리 O(logn + logm)

Reference: ICPC Sinchon 22 Summer 5회차 정수론
*/

/*
1. 소수 p로 나눈 나머지
    1-1. O(n + logp + q)

    - fac[n] = n! mod p 
        > O(n)에 전처리 가능

    - inv[n] =  (n!)^(-1) mod p 
        > 매번 곱셈 역원을 구하면 O(nlogp)
        > 1/n! = 1/(n+1)! * (n+1) 임을 이용하면 O(n + logp)에 전처리 가능
    
    - 전처리
        > fac[0] = 1; 
        > for(int i=1; i<=sz; i++) fac[i] = fac[i-1]*i %p;

        > inv[sz] = pow_mod(fac[sz], p-2, p); //곱셈 역원 구하기, 페르마의 소정리 이용 가능 
        > for(int i=sz-1; i>=0; i--) inv[i] = inv[i+1]*(i+1) %p;

        >
            ll pow_mod(ll a, ll n, ll mod)
            {
                if(n==0) return 1;
                ll ret=pow_mod(a, n/2, mod);
                ret=ret*ret%mod;
                if(n&1) ret=ret*a%mod;
                return ret;
            }

    - fac[n] * inv[r] % p * inv[n-r] % p 를 이용해 O(1)에 쿼리 가능

    - n<p 일 때만 사용 가능
*/

/*
1. 소수 p로 나눈 나머지
    1-2. O(p + logp + qlogp)

    - p가 작고 n이 클 때 사용 (n>p)
    - n, r을 p진법으로 전개하자
    - Lucas's Theoreom

    - ni < p 이므로 1-1에서 사용한 풀이를 적용할 수 있음
        > inv를 p까지만 전처리해도 되므로 O(p + logp)에 전처리 가능

    - 앞에서 사용한 풀이를 log(p)n 번 적용해야 하므로 O(logp)에 쿼리 가능
*/
/*
아래 루카스 정리 코드 이해하기 위해서, constructor 관련 문법 이해하기
https://saikamesh.medium.com/what-is-the-weird-colon-member-syntax-in-constructor-2fd065278d6f
*/
struct Lucas
{
    //init: O(P + logP), query: O(logP)
    const size_t P;
    vector<ll> fac, inv;
    ll Pow(ll a, ll b)
    {
        ll ret=1;
        for(; b; b>>=1, a=a*a%P) if(b&1) ret=ret*a%P;
        return ret;
    }
    Lucas(size_t P) : P(P), fac(P), inv(P)
    {
        fac[0]=1;
        for(int i=1;i<P;i++) fac[i]=fac[i-1]*i%P;
        inv[P-1]=Pow(fac[P-1], P-2);
        for(int i=P-2; ~i; i--) inv[i]=inv[i+1]*(i+1)%P;
    }
    ll small(ll n, ll r) const
    {
        if(n<r) return 0;
        return fac[n]*inv[r] %P *inv[n-r] %P;
    }
    ll calc(ll n, ll r) const
    {
        if(n<r || n<0 || r<0) return 0;
        if(!n || !r || n==r) return 1;
        return small(n%P, r%P)*calc(n/P, r/P) %P;
    }  
};