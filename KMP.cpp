#include <bits/.stdc++.h>
#define ll long long
using namespace std;
/*
KMP
    - 문자열 S, P가 주어지면, S에서 P가 부분 문자열로 등장하는 위치를 모두 찾는 문제
    - 브루트 포스하면 O(|S||P|), KMP를 이용하면 O(|S|+|P|)에 할 수 있음

    - 실패 함수 F[i] := P[0 ... k-1] = P[i-k+1 ... i]를 만족하는 가장 큰 k
        - P[0 ... i]의 Prefix와 Suffix가 일치하는 가장 긴 길이

    - S[x+i]와 P[i]가 일치하지 않음
        - S[x+i-F[i]]부터 다시 시작
        - P[F[i]]부터 비교하면 됨

    - 실패 함수를 구하는 방법(알고리즘)
        - F[i]를 구했고, F[i+1]을 구해야 하는 상황
        - 만약 P[F[i]]=P[i+1]이라면, F[i+1]=F[i]+1
        - 그렇지 않다면
            - P[0 ... i]의 Suffix와 일치하는 P의 Prefix를 찾아야 함
            - P[0 ... F[i]-1]과 P[i-F[i]+1 ... i]는 일치하므로, P[0 ... F[i]-1]의 Suffix를 찾아도 됨
            - P[F[i]]=P[i+1]를 만족할 때까지 F[i], F[F[i]], F[F[F[i]]], ... 를 따라가면 됨 
    
    - 실패 함수를 구하는 방법(코드, 시간 복잡도)
        - i, j의 증감 횟수를 구해야 함
        
        - i-j는 항상 증가하고, j는 항상 감소함
        - 반복문의 각 단계마다 아래 두 가지 중 하나 시행
            - i, j 1씩 증가
            - j 감소
        - 0 <= i, j < |P|이므로 O(|P|)

    - 문자열을 매칭하는 방법(알고리즘)
        - S[i-1]=P[j-1]이 대응됐고, S[i]와 대응시킬 P[k]를 찾아야 하는 상황

        - 만약 S[i]=P[j]이라면 k=j
            - 문자열의 끝까지 대응시켰다면(k+1=|P|) 정답배열에 i-|P|+1을 추가하고
            - j=F[|P|-1]로 바꾸고 탐색 계속 진행

        - 그렇지 않다면
            - S[i-j ... i-1]의 Suffix와 일치하는 P의 Prefix를 찾아야 함
            - P[0 ... j-1]의 Suffix와 일치하는 P의 Prefix를 찾아야 함
            - S[i]=P[j]를 만족할 때까지 F[j-1], F[F[j-1]], ... 를 따라가면 됨


Reference: ICPC Sinchon 22 Summer 7회차 문자열 
https://justicehui.github.io/hard-algorithm/2019/01/16/KMP/ : 나정휘 강사 블로그 KMP 설명 참고하기
*/
//실패함수
//i=0이면 자기 자신을 찾아버리니까 안 됨
vector<int> GetFail(const string &p)
{
    int m=p.size();
    vector<int> fail(m);
    fail[0]=0;
    for(int i=1,j=0; i<m; i++) //i = 0~i 범위의 부분 문자열의 맨 뒤 인덱스, j = prefix와 suffix가 같을 때의 prefix의 맨 뒤 인덱스
    {
        while(j>0 && p[i]!=p[j]) j=fail[j-1];
        if(p[i]==p[j]) fail[i]=++j;
    }
    return fail;
}
//KMP
vector<int> KMP(const string &s, const string &p)
{
    int n=s.size(), m=p.size();
    vector<int> fail=GetFail(p), res;
    for(int i=0, j=0; i<n; i++) //i = s에서 비교할 인덱스, j = p에서 비교할 인덱스
    {
        while(j>0 && s[i]!=p[j]) j=fail[j-1];
        if(s[i]==p[j])
        {
            if(j+1==m) res.push_back(i-m+1), j=fail[j];
            else j++;
        }
    }
    return res;
}

/*
KMP
Reference: 프로그래밍 대회에서 배우는 알고리즘 문제해결전략 p649
O(|H|)
*/
vector<int> kmpSearch(const string &H, const string &N)
{
    int n=H.size(), m=N.size();
    vector<int> ret; 
    vector<int> pi=getPartialMatch(N); //pi[i] = N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
    int begin=0, matched=0; //begin=matched=0에서부터 시작하자.
    while(begin<=n-m)
    {
        if(matched<m && H[begin+matched]==N[matched]) //H와 N의 해당 글자가 같다면
        {
            ++matched;
            if(matched==m) ret.push_back(begin); //결과적으로 m글자가 모두 일치했다면 답에 추가한다.
        }
        else 
        {
            if(matched==0) ++begin;//예외: matched가 0인 경우에은 다음 칸에서부터 계속
            else 
            {
                begin+=matched-pi[matched-1]; 
                //begin을 옮겼다고 처음부터 다시 비교할 필요가 없다. 옮긴 후에도 pi[matched-1]만큼은 항상 일치하기 때문이다.
                matched=pi[matched-1];
            }
        }
    }
    return ret;
}
/*
getPartialMatch(실패 함수)
Reference: 프로그래밍 대회에서 배우는 알고리즘 문제해결전략 p653
O(|N|)
*/
//N에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해 pi[]를 계산한다.
vector<int> getPartialMatch(const string &N)
{
    int m=N.size();
    vector<int> pi(m, 0); //pi[i] = N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
    //KMP로 자기 자신을 찾는다. N을 N에서 찾는다. begin=0이면 자기 자신을 찾아버리니까 안 됨!
    int begin=1, matched=0;
    while(begin+matched<m) //비교할 문자가 N의 끝에 도달할 때까지 찾으면서 부분 일치를 모두 기록한다.
    {
        if(N[begin+matched]==N[matched])
        {
            ++matched;
            pi[begin+matched-1]=matched;
        }
        else
        {
            if(matched==0) ++begin;
            else 
            {
                begin+=matched-pi[matched-1];
                //begin을 옮겼다고 처음부터 다시 비교할 필요가 없다. 옮긴 후에도 pi[matched-1]만큼은 항상 일치하기 때문이다.
                macted=pi[matched-1];
            }
        }
    }
    return pi;
}