#include <bits/stdc++.h>
#define ll long long int
#define pii pair<int, int>
#define X first
#define Y second
using namespace std;
/*
우선순위 큐의 구현
- 연결 리스트, 배열
    원소 추가: O(1)
    원소 꺼내기: O(N)
- 힙 트리

힙은 가장 큰(작은) 원소를 찾는데 최적화된 형태의 이진 트리로, 힙을 사용하면 
새 원소를 추가하는 연산과 가장 큰 원소를 꺼내는 연산을 모두 O(lgN) 시간에 수행할 수 있다.

립은 STL에 포함되어 있으므로 직접 구현할 일은 거의 없다.

힙의 대소관계 규칙: 부모 노드가 가진 원소는 항상 자식 노드가 가진 원소 이상이다.(최대 힙 기준)
힙의 모양 규칙: 1. 마지막 레벨을 제외한 모든 레벨에 노드가 꽉 차 있어야 한다.
             2. 마지막 레벨에 노드가 있을 때는 항상 가장 왼쪽부터 순서대로 채워져 있어야 한다.

배열을 이용한 힙의 구현
엄격한 힙의 모양 규칙은 트리에 포함된 노드의 개수만으로 트리의 전체 구조를 알 수 있기 때문에 
이 점을 최대한 이용해 배열 하나로 전체 트리를 표현 할 수 있다.
- 배열의 1번 인덱스 부터 사용한다.
- a[i]에 대응되는 왼쪽 자손은 a[2*i]에 대응된다.
- a[i]에 대응되는 오른쪽 자손은 a[2*i+1]에 대응된다.
- a[i]에 대응되는 노드의 부모는 a[i/2]에 대응된다.
*/
vector<int> heap;
/*
새 원소의 삽입
힙의 모양 규칙을 먼저 충족시키고, 힙의 대소관계 규칙을 충족시키자.
while문의 내부가 한 번 수행될 때마다 트리에서 한 레벨 위로 올라가게 되므로 push_heap()의 시간 복잡도는 트리의 높이인 O(lgN)이다.
*/
//정수를 담는 최대 힙 heap에 새 원소 newValue를 삽입한다.
void push_heap(vector<int> &heap, int newValue)
{  
    heap.push_back(newValue); //힙의 모양규칙 충족
    int idx=heap.size()-1; //현재 newValue의 위치 
    //루트에 도달하거나 newValue 이상의 원소를 가진 조상을 만날 때 까지
    while(idx>0 || heap[idx/2]<heap[idx])
    {
        swap(heap[idx], heap[idx/2]);
        idx/=2;
    }
}
/*
최대 원소 꺼내기
힙의 모양 규칙을 먼저 충족시키고, 힙의 대소관계 규칙을 총족시키자.
while문의 내부가 한 번 수행될 때마다 트리의 아래 레벨로 내려가기 때문에, 시간 복잡도는 트리의 높이인 O(lgN)이다.
*/
//정수는 담는 최대 힙 heap에서 heap[0]을 제거한다.
void pop_heap(vector<int> &heap)
{
    heap[0]=heap.back(); //힙의 맨 끝에서 값을 가져와 루트에 덮어씌운다.
    heap.pop_back();
    int here=0;
    while(true)
    {
        int left=here*2, right=here*2+1;
        if(left>=heap.size()) break; //리프노드에 도달한 경우
        int next=here;
        if(heap[next]<heap[left]) next=left;
        if(right<heap.size() && heap[next]<heap[right]) next=right;
        if(next==here) break; //두 자손이 모두 자기 자신 이하의 원소를 가진 경우
        swap(heap[here], heap[next]);
        here=next;
    }
}
/*
힙을 이용한 다른 연산들
- 힙 정렬:
  힙에서 원소를 꺼낼 때 항상 정렬된 순서대로 반환한다는 점을 이용한다.
  힙에서 원소를 하나 꺼내면 힙을 담은 배열의 맨 뒤쪽에 한 칸이 비게 되므로, 최대 원소를 여기에 옮기면 추가 메모리를 사용하지 않을 수 있다.
  병합 정렬과 달리 추가적인 메모리를 요구하지 않으면서, 최악의 경우에도 O(NlgN)의 시간복잡도를 가지므로 유명하다.
*/
/*
C++ STL을 이용한 우선순위 큐
Reference: https://koosaga.com/9
*/
#include <queue>
priority_queue<int> pq1;
priority_queue<int, vector<int>, less<int> > pq2; //less<int>>으로 쓰면 일부 컴파일러가 비트 연산으로 오해하니 띄어쓰기를 하자.
/*
위 두 우선순위 큐는 완전히 동일하다. priority_queue<자료형, 구현체, 비교 연산자>로 정의한다.
구현체는 기본적으로 vector<자료형>으로 정의된다. 
비교 연산자는 기본적으로 less<자료형>으로 정의된다. 이건 STL에서 기본으로 제공하는 비교 연산자 클래스이고, 큰 것 부터 나온다.
greater<자료형>을 넣으면 작은 것 부터 나온다.
*/
/*
pq1.push(3);
pq1.empty();
pq1.size();
pq1.top();
pq1.pop();
*/