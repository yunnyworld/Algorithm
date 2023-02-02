#include <bits/stdc++>
using namespace std;
/*
Manacher's Algorithm
Reference: 
https://www.crocus.co.kr/1075
https://nicotina04.tistory.com/250

O(n)
*/
string s; //주어진 문자열
string ss; //전처리 된 문자열
ll ma[4000005]; //ma[i] = i가 중심인 펠린드롬의 길이
ll r=-1, c=-1;

void manacher()
{
    for(char cc : s)
    {
        ss.push_back('#');
        ss.push_back(cc);
    }
    ss.push_back('#');

    for(ll i=0;i<ss.size();i++)
    {
        if(i<=r) ma[i]=min(r-i, ma[2*c-i]);

        while(i+ma[i]+1<ss.size() && i-ma[i]-1>=0 && ss[i+ma[i]+1]==ss[i-ma[i]-1])
            ma[i]++;
        
        if(i+ma[i]>r) {c=i; r=i+ma[i];}
    }
}
