#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll>
#define pii pair<int, int>
#define X first
#define Y second
using namespace std;
int d[1001][1001];
/*
O(n^2)
Longest Common Substring 의 점화식
d[i][j]=a[i], b[j]까지의 Longest Common Substring
a[i]==b[j] : d[i][j]=d[i-1][j-1]+1
a[i]!=b[j] : d[i][j]=0
*/
void LCS1()
{
    string a, b; cin>>a>>b;
    a="0"+a;
    b="0"+b;
    for(int i=1;i<a.length();i++)
    {
        for(int j=1;j<b.length();j++)
        {
            if(a[i]==b[j]) d[i][j]=d[i-1][j-1]+1;
            else d[i][j]=0;
        }
    }
    int ans=0;
    for(int i=0;i<a.length();i++) for(int j=0;j<b.length();j++)
        if(d[i][j]>ans) ans=d[i][j];
    cout<<ans<<'\n';
}
/*
O(n^2)
Longest Common Subsequence 의 점화식
d[i][j]=a[i], b[j]까지의 Longest Common Subsequence
a[i]==b[j] : d[i][j]=d[i-1][j-1]+1
a[i]!=b[j] : d[i][j]=max(d[i-1][j], d[i][j-1])
*/
void LCS2()
{
    string a, b; cin>>a>>b;
    a="0"+a; 
    b="0"+b;
    for(int i=1;i<a.length();i++)
    {
        for(int j=1;j<b.length();j++)
        {
            if(a[i]==b[j]) d[i][j]=d[i-1][j-1]+1;
            else d[i][j]=max(d[i-1][j], d[i][j-1]);
        }
    }
    int ans=0;
    for(int i=0;i<a.length();i++) for(int j=0;j<b.length();j++)
        if(d[i][j]>ans) ans=d[i][j];
    cout<<ans<<'\n';
}