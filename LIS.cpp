#include <bits/stdc++.h>
#define ll long long
using namespace std;
/*
LIS(Longest Increasing Subsequence, 최장 증가 부분 수열)
Reference: https://rebro.kr/33
*/
ll n;
ll a[1005];
ll dp[1005];

//O(n^2)
ll LIS()
{
    for (ll i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (ll j = 0; j < i; j++)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
    }
    ll ret = 0;
    for (ll i = 0; i < n; i++) ret = max(ret, dp[i]);
    return ret;
}


//O(nlogn)
ll idx[1005]; //a[i]의 ans 벡터 안에서의 인덱스
ll LIS()
{
    vector<ll> ans;
    for(ll i=0;i<n;i++)
    {
        ll j=lower_bound(ans.begin(), ans.end(), a[i])-ans.begin();
        if(j<ans.size()) ans[j]=a[i];
        else ans.push_back(a[i]);
        idx[i]=j;
    }

    ll s=ans.size()-1;
    for(ll i=n-1;i>=0;i--)
        if(idx[i]==s) ans[s--]=a[i]; //LIS 수열

    return ans.size(); //LIS 길이
}





