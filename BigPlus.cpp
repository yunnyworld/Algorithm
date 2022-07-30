#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll>
#define pii pair<int, int>
#define X first
#define Y second
using namespace std;
/*
Reference:
http://wookje.dance/2018/03/13/boj-1793-타일링/
*/
string BigPlus(string a, string b) 
{
	int sum=0;
	string res;
	while (!a.empty() || !b.empty() || sum) 
    {
		if(!a.empty()) sum+=a.back()-'0', a.pop_back();
		if(!b.empty()) sum+=b.back()-'0', b.pop_back();
		res.push_back((sum%10)+'0');
		sum/=10;
	}
	reverse(res.begin(), res.end());
	return res;
}