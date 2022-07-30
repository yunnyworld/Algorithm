#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll>
#define pii pair<int, int>
#define X first
#define Y second
using namespace std;
const int MOD=987654321;
/*
https://suhak.tistory.com/77
https://www.youtube.com/watch?v=PjdWboLqhc4
https://ko.wikipedia.org/wiki/카탈랑_수
https://miho273.tistory.com/55 : 이진 순서 트리 설명이 잘 되어있음

n번째 카탈란 수 Cn
점화식: Cn+1=sigma(Ci*Cj) (i+j=n, n>=0) 
일반항: Cn = 2nCn - 2nCn+1 = 2nCn/(n+1)
나열: 1, 2, 5, 14, 42, 132, 429,  . . .

Cn의 다른 표현
- -1과 1값으로 만들어진 수열(a1, a2, . . ., a2n)에서 a1+a2+ . . . +a2n=0 일 때, 
  각각의 부분합 a1, a1+a2,  . . . , a1+a2+ . . .+a2n 이 모두 0이상이 되도록 하는 방법의 수
- 길이가 2n인 모든 뒤크 단어의 개수
  뒤크 단어는 n개의 X와 n개의 Y로 이루어진 문자열 중 처음부터 X와 Y의 개수를 세었을 때, 
  항상 X가 Y보다 많거나 같은 것이다. 
- 뒤크 단어에서 X를 (, Y를 )에 대응시키면
  Cn은 n쌍의 괄호로 만들 수 있는 올바른 괄호 구조의 개수
- n+1개의 항에 n쌍의 괄호를 씌우는 모든 경우의 수
- n+1개의 간선을 갖는 이진 순서 트리의 개수(괄호처럼 생각)
- n-1개의 단말 노드를 갖는 이진 순서 트리의 개수(괄호처럼 생각)
- 동형이 아닌 모든 정 이진 트리 가운데 자식을 가진 노드가 n개인 트리의 개수(괄호처럼 생각)
  (정 이진 트리는 한 개의 자식만 가진 노드가 없고, 모든 노드가 두 개의 자식을 가졌거나 혹은 단말노드인 트리)
- 정사각형들로 이루어진 n*n개 커다란 정사각형들의 변을 따라 이동할 때, 대각선과 만나지 않고 이동하는 방법의 수
- n+2각형을 n개의 삼각형으로 나누는 방법의 수

카탈란 수의 점화식은 dp를 이용해서 구현 가능하다.
*/
ll c[100];
ll Catalan(ll n)
{
    c[0]=1;
    for(ll i=1;i<=n;i++)
        for(ll j=0;j<i;j++) 
            c[i]+=c[j]*c[i-1-j];
    return c[n];
}