#include <bits/stdc++.h>
using namespace std;
/*
Sparse Table (희소 배열)
Reference: ICPC Shinchon 2022 Summer 중급 10회차

- 거듭 제곱을 O(logn)에 계산하는 방법에서 착안
- 2^k의 결과를 두개 합쳐서 2^(k+1)의 결과를 만들 수 있으면 다 된다.
    - 함수
    - 구간의 최대/최소/합 등
- 2^(i-1) + 2^(i-1) = 2^i 임을 이용하여, 
  p[i][j] = p[i - 1][p[i - 1][j]]
  로 점화식을 쓸 수 있다.
  단 i, j를 돌리는 순서는 아래와 같이 해야만 한다.
  왜냐하면, p[i-1][k]가 모두 채워져야 p[i][k]를 채울 수 있기 때문이다.
*/
ll p[20][50005]; // p[logN][N]

void MakeSparse()
{
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= N; j++)
            p[i][j] = p[i - 1][p[i - 1][j]];
}
