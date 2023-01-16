#include <bits/stdc++.h>
#define ll long long int
using namespace std;
/*
Lucas's Theorem (루카스 정리, 뤼카 정리)
: nCr (mod p)를 O(p + logp + qlogn)으로 구할 수 있다.
- p가 작고 n이 클 때 이용
- n, r을 p진법으로 전개한 이후 n_iCr_i들의 곱은 nCr과 mod p에서 합동임
- 증명은 어려우니 생략
- 

*/
struct Lucas
{
    // init: O(P + logP), query: O(logP)
    const size_t P;
    vector<ll> fac, inv;
    ll Pow(ll a, ll b)
    { // O(logP)
        ll ret=1;
        for(; b; b>>=1, a=a*a%P) if(b&1) ret=ret*a%P;
        return ret;
    }
    Lucas(size_t P) : P(P), fac(P), inv(P)
    { // O(P)
        fac[0]=1;
        for(int i=1;i<P;i++) fac[i]=fac[i-1]*i%P;
        inv[P-1]=Pow(fac[P-1], P-2); // 페르마 소정리
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
        return small(n%P, r%P)*calc(n/P, r/P) %P; // n, r을 P진법으로 전개한 이후 n_iCr_i들의 곱, O(logn)
    }  
};
