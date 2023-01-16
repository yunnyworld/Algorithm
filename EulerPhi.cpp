#include <bits/stdc++.h>
#define ll long long int
using namespace std;
/*
Euler Phi function (오일러 피 함수)
- E(x) = x이하의 수 중 x와 서로소인 수의 개수
- E(p) = p-1 (p는 소수)
- E(p^n) = p^n - p^(n-1) (by definition)
         = (p-1)*p^(n-1) - ㄱ
- E(p*q) = E(p)*E(q) (p와 q가 서로소일때)
- m = p1^n1 * p2^n2 * ... * pk^nk 일때, ㄱ에 의해
  E(m) = m*((p1-1)/p1)*((p2-1)/p2)*...*((pk-1)/pk) 이다.
- 에라토스테네스 체에서 소인수분해를 따라가다가 처음보는 소인수 p가 나오면 m에다가 (p-1)/p를 곱해주면 된다.

*/
ll phi(ll n)
{
    ll res = n;
    for (ll p = 2; p * p <= n; p++)
        if (n % p == 0)
        {
            while (n % p == 0) n /= p;
            res /= p;
            res *= p - 1;
        }
    if (n > 1)
    {
        res /= n;
        res *= n - 1;
    }
    return res;
}
