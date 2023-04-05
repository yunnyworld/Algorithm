#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll>
#define X first
#define Y second
using namespace std;
/*
CCW(Counter ClockWise) 알고리즘
O(1)
a x b = |a||b|sin(c)
a x b = (a2*b3 - a3*b2, a3*b1 - a1*b3, a1*b2 - a2*b1)
이때, a와 b가 xy평면에 있다고 하면, a3 = b3 = 0 이므로,
a x b = (0, 0, a1*b2 - a2*b1)이다.

점 A(x1,y1), B(x2, y2), C(x3, y3)라 하면,
AB = (x2 - x1, y2 - y1, 0)
AC = (x3 - x1, y3 - y1, 0)
AB x AC = (0, 0, (x2 - x1)*(y3 - y1) - (y2 - y1) * (x3 - x1))
= (0, 0, x1y2 + x2y3 + x3y1 - x1y3 - x2y1 - x3y2)이다.

외적의 방향은 오른손 법칙을 따르므로, 
z값이 양수이면, A, B, C 순서대로 반시계 방향
z값이 음수이면, A, B, C 순서대로 시계 방향
z값이 0이면, A, B, C 순서대로 일직선에 놓여있다.

Reference: 
https://wogud6792.tistory.com/11
https://wogud6792.tistory.com/10?category=315912
https://wogud6792.tistory.com/12?category=315912
*/
ll ccw(pll A, pll B, pll C)
{
	return A.X * B.Y + B.X * C.Y + C.X * A.Y - A.X * C.Y - B.X * A.Y - C.X * B.Y;
}

/*
CCW를 이용한 두 '직선'의 교차 여부 판단
O(1)
ccw(A, B, C) * ccw(A, B, D) < 0 이면, 직선 AB와 직선 CD는 교차하고 있다.
Reference: https://wogud6792.tistory.com/12?category=315912

CCW를 이용한 두 '선분'의 교차 여부 판단
O(1)
ccw(A, B, C) * ccw(A, B, D) < 0 && ccw(C, D, A) * ccw(C, D, B) < 0 이면, 선분 AB와 선분 CD는 교차하고 있다.
Reference: https://jason9319.tistory.com/358
*/

/*
CCW를 이용한 다각형의 넓이 구하기
O(1)
일단 삼각형 넓이를 신발끈 공식으로 구한 값의 절반이 CCW값이다.
1. 고정점을 설정한다.
2. 고정점을 기준으로 시계방향 or 반시계방향으로 꼭짓점을 돌면서 CCW 알고리즘을 적용한다.
3. 절댓값으로 만든 후 1/2을 곱해준다.
   이때 절댓값으로 만드는 이유는, 반시계 방향으로 돌렸을 때에는 양수 넓이가 나오지만,
   시계 방향으로 돌렸을 때에는 음수 넓이가 나오기 때문이다.
Reference: https://wogud6792.tistory.com/12?category=315912
*/

