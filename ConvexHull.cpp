#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll>
#define pdd pair<double, double>
#define X first
#define Y second
using namespace std;
/*
볼록 껍질(Convex Hull) 구하기
볼록 껍질은 '2차원 평면 상에서 주어진 점들을 포함하는 가장 작은 다각형'이다.
Reference:
https://wogud6792.tistory.com/14?category=315912
https://lem0nad3.tistory.com/131
*/

/*
그라함 스캔 알고리즘(Graham's Scan Algorithm)

1. 주어진 점들 중 가장 왼쪽 아래에 있는 점을 기준점으로 선택한다. (왼쪽이 우선)
2. 기준점을 기준으로 나머지 점들을 반시계 방향으로 정렬한다. (기울기를 이용)
3. 그라함 스캔 알고리즘을 적용한다. (스택, CCW 이용)

cf1) 1번에서 왼쪽을 우선시 하는 이유는, 가장 왼쪽에 있어야 2번에서 기울기를 찾을 때에
기울기의 범위가 (-90도, 90도]가 되어서 훨씬 편하기 때문이다.
게다가, 정렬 구현 할 때에도 따로 기준을 정해주지 않고 그냥 정렬해도 되어서 더 편하다.

cf2) 2번에서 반시계 방향으로 정렬 하는 것을 180도 정렬이라고도 한다.
dy/dx를 기준으로 오름차순으로 정렬하는데, dx=0일 수 있으니, 분모를 넘겨서 비교하자.

실제 그라함 스캔 알고리즘은 O(n)므로, 볼록 껍질을 구하는 데에는 점들을 정렬하는데 걸리는 O(nlogn)이다.

Reference: 
https://wogud6792.tistory.com/14?category=315912
https://lem0nad3.tistory.com/130
https://m.blog.naver.com/kks227/220857597424
*/

ll n;
pll d[100005];

ll ccw(pll a, pll b, pll c)
{
    return a.X * b.Y + b.X * c.Y + c.X * a.Y - a.X * c.Y - b.X * a.Y - c.X * b.Y;
}

bool comp(pll a, pll b) //180도 정렬, 기울기가 같은 경우에 거리가 가까운 것이 우선인 점 조심하기
{
    if (a.Y * b.X == a.X * b.Y) return a.X * a.X + a.Y * a.Y < b.X* b.X + b.Y * b.Y;
    else return a.Y * b.X < a.X * b.Y; //기준점이 가장 왼쪽 아래이므로, 항상 dx > 0이다.
}

void GrahamScan()
{
    sort(d, d + n);
    pll refer = d[0];
    for (int i = 1; i < n; i++)
    {
        d[i].X -= refer.X;
        d[i].Y -= refer.Y;
    }
    sort(d + 1, d + n, comp);
    for (int i = 1; i < n; i++)
    {
        d[i].X += refer.X;
        d[i].Y += refer.Y;
    }
    stack<ll> st;
    st.push(0);
    st.push(1);
    ll nxt = 2;
    while (nxt < n)
    {
        while (st.size() >= 2)
        {
            ll p, pp;
            p = st.top(); 
            st.pop();
            pp = st.top();
            if (ccw(d[pp], d[p], d[nxt]) > 0)
            {
                st.push(p);
                break;
            }
        }
        st.push(nxt++);
    }
}

/*
반껍질 두 개를 구해서 합쳐주어 볼록 껍질 구하기

이 방법도 그라함 스캔 알고리즘을 일부분 차용한다.
하지만, 이 방법은 각도 정렬을 하지 않아도 되어서 편하다. 
주의해야 할 점으로는, 각 반껍질의 양 끝 점이 겹치기 때문에 이를 빼주어야 한다.

O(nlogn)

Reference: https://lem0nad3.tistory.com/131
*/

vector<pll> v(n);

void TwoHalf()
{
	sort(v.begin(), v.end());
	vector<pll> L, R;
	for (auto i : d)
	{

	}
	v.clear();
	for (ll i = 0; i < R.size() - 1; i++) v.push_back(R[i]);
	for (ll i = L.size() - 1; i > 0; i--) v.push_back(L[i]);
}
