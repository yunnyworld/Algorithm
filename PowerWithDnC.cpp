#include <bits/stdc++.h>
#define ll long long int
using namespace std;
ll fpow1(ll a, ll x)
{
    if(x==0) return 1;
    ll ret=fpow1(a, x/2);
    ret*=ret;
    if(x%2) ret*=a;
    return ret;
}
ll fpow2(ll a, ll x)
{
    ll ret=1;
    while(x)
    {
        if(x%2) ret*=a;
        a*=a;
        x/=2;
    }
    return ret;
}