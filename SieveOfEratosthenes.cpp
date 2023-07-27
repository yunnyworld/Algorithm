#include <bits/stdc++.h>
#define ll long long int
using namespace std;

/*
에라토스테네스의 체로 소수 판별
O(nlog(logn))
*/
vector<int> p;//소수 저장
bool check[1000005]; //check[i]=i가 소수이면 false
void Eratosthenes()
{
    for(int i=2;i<=1000000;i++) //1은 소수가 아님, 2부터 n까지 돌아야 모든 소수가 배열에 추가된다.
      if(!check[i]) 
      {
	p.push_back(i);
      	for(int j=i*i;j<=n;j+=i) check[j]=1; 
      	//j의 배수는 소수가 아님, i가 너무 크면 i*i대신 2*i로 써야된다. i가 백만인 경우 i*i는 1조로 범위를 넘어가기 때문이다. 
      }
}

//간단한 구현
ll N;
bool notP[4000005];
void Eratosthenes2()
{
	for (ll i = 2; i <= N; i++)
		for (ll j = i * i; j <= N; j += i) notP[j] = 1;
}

/*
각 2부터 n까지의 자연수 k에 대해, "k가 갖는 가장 작은 소인수"를 계산하기
O(nlogn)
Reference: https://rebro.kr/96?category=449699
*/
int p[1000005]; // p[i] = i의 가장 작은 소인수
void MinPrimeFactor()
{
	int n = 1000000;
	for (int i = 1; i <= n; i++) p[i] = i;
	for (int i = 2; i <= n; i++)
	{
		if (p[i] == i)
			for (ll j = 2; i * j <= n; j++)
				if (p[i * j] == i * j) p[i * j] = i;
	}
}

/*
각 2부터 n까지의 자연수 k에 대해, "빠르게 k를 소인수분해" 하기
O(nlogn)
전처리 해둔 가장 작은 소인수로 계속 나누어 구한다.
Reference: https://rebro.kr/96?category=449699
*/
int p[1000005]; // p[i] = i의 가장 작은 소인수
vector<int> facs[1000005]; // fac[i] = i의 소인수들
void PrimeFactorization()
{
	int n = 1000000;
	MinPrimeFactor();
	for (int i = 2; i <= n; i++)
	{
		int k = i;
		while (k > 1)
		{
			facs[i].push_back(p[k]);
			k /= p[k];
		}
	}
}

/*
각 2부터 n까지의 자연수 k에 대해 "k의 약수의 개수" 빠르게 구하기
O(nlogn)
k의 약수의 수를 구하기 위해서 k−1 이하의 모든 자연수에 대해서 약수의 수를 알고 있다고 가정한다.
n의 약수의 개수를 fac[n]이라고 하면,
k의 가장 작은 소인수가 p이고, 이 소인수가 k에서 a번 출현한다면 fac[k / p] * (a + 1) / a = fac[k]이다.
Reference: https://rebro.kr/96?category=449699
*/
int p[1000005]; // p[i] = i의 가장 작은 소인수
int fac[1000005]; // fac[i] = i의 약수의 개수
int minfac[1000005]; // minfac[i] = i의 가장 작은 소인수의 출현 횟수
void NumberOfDivisor()
{
	int n = 1000000;
	MinPrimeFactor();
	fac[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (p[i] == i)
		{
			fac[i] = 2;
			minfac[i] = 1;
		}
		else
		{
			int m = i / p[i];
			if (p[i] != p[m]) minfac[i] = 1;
			else minfac[i] = minfac[m] + 1;
			int a = minfac[i];
			fac[i] = fac[m] * (a + 1) / a;
		}
	}
}

/*
각 수의 약수를 직접 구하기(약수의 개수도 저절로 구해진다)
O(nlogn)
약수를 구하는 것보다 배수를 구하는 것이 쉽다는 것을 이용한다.
Reference: https://rebro.kr/96?category=449699
*/
int fac[1000005];
void GetDivisor()
{
	int n = 1000000;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j+=i) fac[j]++;
}

