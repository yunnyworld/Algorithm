#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll>
#define pii pair<int, int>
#define X first
#define Y second
using namespace std;
int dx[]={-1, 1, 0, 0};
int dy[]={0, 0, -1, 1};
void Eratosthenes()
{
    vector<int> p;//소수 저장
    bool check[101]={false}; //check[i]=i가 소수이면 false
    int n=100;

    for(int i=2;i<=n;i++) //1은 소수가 아님, 2부터 n까지 돌아야 모든 소수가 배열에 추가된다.
    {
      if(check[i]==false) p.push_back(i);
      for(int j=i*i;j<=n;j+=i) check[j]=true; 
      //j의 배수는 소수가 아님, i가 너무 크면 i*i대신 2*i로 써야된다. i가 백만인 경우 i*i는 1조로 범위를 넘어가기 때문이다. 
    }
}
