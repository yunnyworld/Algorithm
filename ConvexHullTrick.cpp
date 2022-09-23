#include <bits/stdc++.h>
#define ll long long
using namespace std;
/*
Convex Hull Trick
O(n)을 O(logn)으로 최적화
Reference: https://m.blog.naver.com/kks227/221418495037
*/
ll n;
ll A[100005];
ll B[100005];
ll dp[100005];

struct LinearFunc //f(x)=ax+b, x>=s
{
    ll a, b;
    double s; //시작점
    LinearFunc(): LinearFunc(1, 0){}
    LinearFunc(ll a1, ll b1): a(a1), b(b1), s(0){}
};

double cross(LinearFunc &f, LinearFunc &g)
{ //두 직선 f, g의 교점의 x좌표를 구함
    return (g.b-f.b)/(f.a-g.a);
}

void solve()
{
    cin>>n;
    for(ll i=0;i<n;i++) cin>>A[i];
    for(ll i=0;i<n;i++) cin>>B[i];
    
    //dp[0]=0, dp테이블을 채우면서 "f(.) = B[i]*x + dp[i]"를 스택에 쌓음
    ll dp[100005]={0};
    LinearFunc f[100005];
    int top=0;
    for(ll i=1;i<n;i++)
    {
        //i-1번에 해당하는 새로운 직선을 스택의 위에 쌓음
        LinearFunc g(B[i-1], dp[i-1]);
        while(top>0) //쌓기 전에, top과 교점을 구해서 top의 시작점보다 교점이 앞이면 pop
        {
            g.s=cross(f[top-1], g);
            if(f[top-1].s<g.s) break;
            top--;
        }
        f[top++]=g;

        ll x=A[i];
        //주어진 x좌표를 포함하는 선분(fpos)을 이분 탐색으로 찾음
        int fpos=top-1;
        if(x<f[top-1].s)
        {
            int l=0, r=top-1;
            while(l+1<r)
            {
                int mid=(l+r)/2;
                if(x>=f[mid].s) l=mid; 
                else r=mid;
            }
            fpos=l;
        }
        /*
        x좌표값 A[i]가 단조증가하기 때문에, 새로 생긴 선분만 훑어보면 된다.
        while(fpos+1<top && f[fpos+1].s<x) fpos++;
        */
        //i번째 dp값 계산
        dp[i]=f[fpos].a*x+f[fpos].b;
    }
    cout<<dp[n-1];
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int tc=1; //cin>>tc;
    while(tc--) solve();
    return 0;
}