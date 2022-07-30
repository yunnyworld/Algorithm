//Reference: https://nukestorm.tistory.com/149
#include <bits/stdc++.h>
#define ll long long int
using namespace std;
struct matrix22
{
    ll f[2][2];
};
matrix22 multiply(matrix22 a, matrix22 b)
{
    matrix22 c;
    c.f[0][0]=a.f[0][0]*b.f[0][0]+a.f[0][1]*b.f[1][0];
    c.f[0][1]=a.f[0][0]*b.f[0][1]+a.f[0][1]*b.f[1][1];
    c.f[1][0]=a.f[1][0]*b.f[0][0]+a.f[1][1]*b.f[1][0];
    c.f[1][1]=a.f[1][0]*b.f[0][1]+a.f[1][1]*b.f[1][1];
    return c;
}
matrix22 matrix_power(matrix22 a, int n) //분할정복 이용, O(n)을 O(log2n)으로 줄여준다.
{
    if(n>1)
    {
        a=matrix_power(a, n/2);
        a=multiply(a, a);
        if(n%2==1) //n이 홀수인 경우
        {   
            matrix22 f1={1, 1, 1, 0};
            a=multiply(a, f1); //나누기 연산으로 버려진 1 보완
        }
    }
    return a;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin>>n;
    matrix22 f1={1, 1, 1, 0};
    f1=matrix_power(f1, n);
    if(n==0) cout<<0<<'\n';
    else cout<<f1.f[0][1]<<'\n'; //n번째 피보나치 추
    return 0;
}