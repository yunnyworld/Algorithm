/*
Merge Sort
n개를 n/2개, n/2개로 나눈 뒤 왼쪽 n/2와 오른쪽 n/2를 정렬한 후 그 결과를 합친다.
O(nlgn)
예시: Inversion Counting
*/
int a[100], b[100]; //a는 정렬해야 할 원래 배열, b는 임시 배열
void merge(int start, int end)
{
    int mid=(start+end)/2;
    int i=start, j=mid+1, k=0;
    while(i<=mid && j<=end)
    {
        if(a[i]<=a[j]) b[k++]=a[i++];
        else b[k++]=a[j++];
    }
    while(i<=mid) b[k++]=a[i++];
    while(j<=end) b[k++]=a[j++];
    for(int i=start;i<=end;i++) a[i]=b[i-start];
}
void sort(int start, int end)
{
    if(start==end) return ;
    int mid=(start+end)/2;
    sort(start, mid);
    sort(mid+1, end);
    merge(start, end);
}