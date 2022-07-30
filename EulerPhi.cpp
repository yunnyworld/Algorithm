#include <bits/stdc++.h>
#define ll long long int
#define pii pair<int, int>
#define X first
#define Y second
using namespace std;
int phi(int n)
{
    int res=n;
    for(int p=2;p*p<=n;p++)
    {
        if(n%p==0)
        {
            while(n%p==0) n/=p;
            res-=res/p;
        }
    }
    if(n>1) res-=res/n;
    return res;
}