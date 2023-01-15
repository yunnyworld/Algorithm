#include <bits/stdc++.h>
#define ll long long int
using namespace std;
/*
Fermat's little Theorem (FlT, 페르마 소정리)

페르마 소정리: p가 소수이고 a, p가 서로소일 때 a^(p-1) = 1 (mod p)
- a^(p-1) = 1 (mod p) 
- a * a^(p-2) = 1 (mod p) 
- a^(-1) = a^(p-2) (mod p) : a^(p-2)는 a의 곱셈 역원이다 

주의사항: 조건을 정확히 충족하는지 확인하고 사용하자.
1. p가 소수
2. a, p가 서로소
*/

/*
보통 분할 정복을 이용한 거듭제곱을 이용해 구현한다.
시간복잡도: O(logp)
*/
ll pow(ll a, ll n)
{
    if(n==0) return 1ll;
    ll ret=pow(a, n/2);
    ret*=ret;
    if(n%2) ret*=a;
    return ret;
}
