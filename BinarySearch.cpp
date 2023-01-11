#include <bits/stdc++.h>
#define ll long long int
#define pii pair<int, int>
#define X first
#define Y second
using namespace std;
//이분 탐색 간단한 구현
void BinarySearch()
{
    int l, r, x, position, a[10000];
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(a[mid]==x)
        {
            position=mid;
            break;
        }
        else if(a[mid]>x) r=mid-1;
        else l=mid+1;
    }
}
/*
C++ STL 
binary_search(first, last, value)
*/
/*
어떤 수열 a가 있을 때, 
상한: x보다 큰 수 중 첫 번째 수
하한: x보다 크거나 같은 수 중 첫 번째 수
어떤 수열 a에서 x의 개수는 "상한 인덱스-하한 인덱스"와 같다.

어떤 수열 a가 오름차순 정렬되어 있을 때,
어떤 수열 a에서 x보다 큰 수의 개수 = a.end()-upper_bound(a.begin(), a.end(), x)
어떤 수열 a에서 x보다 작은 수의 개수 = lower_bound(a.begin(), a.end(), x)-a.begin()
*/
void LowerBound()
{
    int l, r, x, position, a[10000];
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(a[mid]==x)
        {
            position=mid;
            r=mid-1;
        }
        else if(a[mid]>x) r=mid-1;
        else l=mid+1;
    }
}
void UpperBound()
{
    int l, r, x, position, a[10000];
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(a[mid]==x)
        {
            position=mid+1;
            l=mid+1;
        }
        else if(a[mid]>x) r=mid-1;
        else l=mid+1;
    }
}
/*
C++ STL
lower_bound(first, last, value)
upper_bound(first, last, value)

Reference: https://rebro.kr/36

lower_bound는 [first, last)의 범위에서 val보다 '크거나 같은' 원소 들 중 첫 번째 원소의 Iterator, 배열인 경우에는 원소의 주솟값이 반환 된다.
upper_bound는 [first, last)의 범위에서 val보다 '큰' 원소 들 중 첫 번째 원소의 Iterator, 배열인 경우에는 원소의 주소값이 반환 된다. 
쉽게 말해서, 처음으로 val보다 큰 값이 나오는 위치를 반환한다. 
*/
