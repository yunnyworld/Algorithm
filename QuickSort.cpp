#include <bits/stdc++.h>
#define ll long long int
#define pii pair<int, int>
#define X first
#define Y second
using namespace std;
/*
퀵 소트
- 평균적인 상황에서 최고의 성능 O(nlgn)을 보여준다.
- 피벗(pivot)을 하나 고른 다음, 그것보다 작은 것을 앞으로 큰 것을 뒤로 보낸다.
- 그 다음, 피벗의 앞과 뒤에서 다시 퀵 정렬을 수행한다.
- 최악의 경우에는 O(n^2)이 걸린다.
*/
int a[100];
int choosePivot(int low, int high)
{
    return (low+high)/2;
}
int partition(int low, int high)
{
    int pivotIndex=choosePivot(low, high);
    int pivotValue=a[pivotIndex];
    swap(a[pivotIndex], a[high]);
    int storeIndex=low;
    for(int i=low;i<high;i++)
    {
        if(a[i]<pivotValue)
        {
            swap(a[i], a[storeIndex]);
            storeIndex++;
        }
    }
    swap(a[storeIndex], a[high]);
    return storeIndex;
}
void quicksort(int low, int high)
{
    if(low<high)
    {
        int pivot=partition(low, high);
        quicksort(low, pivot-1);
        quicksort(pivot+1, high);
    }
}
/*
퀵 셀렉트
- 정렬되지 않은 리스트에서 k번재 작은 수를 찾는 알고리즘
- 퀵 소트와 같지만, 한 쪽만 호출한다.
- 따라서, 시간 복잡도가 O(n)으로 줄어들지만, 최악의 경우에는 O(n^2)이다.
*/
int quickselect(int low, int high, int k)
{
    int pivot=partition(low, high);
    if(pivot==k) return a[k];
    else if(k<pivot) return quickselect(low, pivot-1, k);
    else quickselect(pivot+1, high, k);
}