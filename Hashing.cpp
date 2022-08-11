#include<bits/stdc++.h>
#define ll long long
using namespace std;
/*
Hashing(해싱)
- 해시 함수: 임의의 길이를 갖는 임의의 데이터를 고정된 길이의 데이터로 매핑하는 단방향 함수
- 해시 함수의 조건
    - 여러 번 실행해도 같은 결과가 나온다.
    - 데이터가 다르면 결과값이 다를 확률이 높다.

- 라빈카프 알고리즘 
    - 적당한 정수 P, M을 선택
    - f("s0 s1 ... s(L-1)") = (s0*P^(L-1) + s1*P^(L-2) + ... + s(L-2)*P^1 + s(L-1)*P^0) mod M
    - mod M을 제외하면 1:1 대응이므로 충돌이 발생하지 않음
        - 단, P >= 사용하는 문자의 종류
    - 해시 충돌은 M으로 나눈 나머지를 계산하는 것에 의해 발생
    - P, M을 잘 선택했다면 충돌이 발생할 확률은 1/M
    - M을 크게 잡아야 함
        - 보통 10억 정도의 소수로 잡음 (1e9+7, 998244353)
        - P와 M은 서로소, M은 소수일 때 해시 충돌이 적게 발생함
    - 부분 문자열의 해시값
        - H[i] = S[0...i]의 해시값
        - H[i] = (H[i-1]*P + S[i]) % M
        - S[s...e]의 해시값 = (H[r] - H[l-1]*P^(r-l+1)) % M
        - H배열과 P의 거듭제곱은 모두 O(|S|)에 전처리 가능
        - 부분 문자열의 해시값을 O(1)에 구할 수 있음

    - 문자열 A, B의 사전순 비교
        - 문자열 A가 B보다 사전순으로 앞선다.
            - A[i]!=B[i]인 가장 작은 i에서 A[i]<B[i]이다.
        - A와 B의 접두어가 처음으로 다른 지점을 이분 탐색으로 찾을 수 있음
        - O(log min(|A|, |B|)) 

Reference: ICPC Sinchon 22 Summer 7회차 문자열 

https://modoocode.com/219 : template 이해하기
*/
template<ll P, ll M> struct Hasing
{
    vector<ll> H, B;
    void build(const string &S)
    {
        H.resize(S.size()+1); 
        B.resize(S.size()+1);
        B[0]=1;
        for(int i=1;i<=S.size();i++) H[i]=(H[i-1]*P+S[i-1])%M;
        for(int i=1;i<=S.size();i++) B[i]=B[i-1]*P%M;
        //주의) H[i], B[i]는 S[0]...S[i-1]까지의 해시값을 나타냄
    }
    ll get(int s, int e)
    {
        ll res=(H[e]-H[s-1]*B[e-s+1])%M;
        return res>=0?res:res+M;
    }
}