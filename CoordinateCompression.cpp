#include <bits/stdc++.h>
using namespace std;
/*
좌표 압축
- 원소들의 대소관계만 중요할 때
- 원소의 개수가 n개일 때, 각 원소들을 0, 1, ... , n-1에 대응시킬 수 있다.
Reference: ICPC Shinchon 2022 Summer 중급 8회차
*/
vector<int> a(n);
void CoordinateCompression()
{
    vector<int> comp;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        comp.push_back(a[i]);
    }
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for(int i=0;i<n;i++) a[i]=lower_bound(comp.begin(), comp.end(), a[i])-comp.begin();
}