#include <bits/stdc++.h>
#define ll long long int
using namespace std;
/*
Manacher's Algorithm
Reference:
https://nicotina04.tistory.com/250
Time Complexity Analysis:
https://www.youtube.com/watch?v=OLpy_Mh6NZY
O(n)
*/
struct manacher
{
    string s; // input string
    string ss = ""; // preprocessed string
    vector<ll> ma; // ma[i] := length of palindrome which center is i
    ll r = -1, c = -1; // center of previous palindrome, radius of previous palindrome
    manacher(string& s) : s(s), ma(s.size() * 2 + 2, 0) {}
    void go()
    {
        for (char cc : s)
        {
            ss.push_back('#'); // dummy character for even length palindrome
            ss.push_back(cc);
        }
        ss.push_back('#');
        for (ll i = 0; i < ss.size(); i++)
        {
            if (i <= r) ma[i] = min(r - i, ma[2 * c - i]); // get ma[i]
            while (i + ma[i] + 1 < ss.size() && i - ma[i] - 1 >= 0 && ss[i + ma[i] + 1] == ss[i - ma[i] - 1])
                ma[i]++; // update ma[i]
            if (i + ma[i] > r) // update c and r
            {
                c = i;
                r = i + ma[i];
            }
        }
    }
    // real index of palindrome(0-base): [(i-ma[i]+1)/2, (i+ma[i]-1)/2] if ma[i]>0
};
