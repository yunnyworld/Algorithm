#include <bits/stdc++.h>
#define ll long long int
using namespace std;
/*
less memory using Trie code
*/
struct Trie
{
    vector<Trie*> nxt;
    vector<int> idx;
    ~Trie()
    {
        for (int i = 0; i < nxt.size(); i++) delete nxt[i];
    }
    int find_idx(int x)
    {
        for (int i = 0; i < idx.size(); i++) if (idx[i] == x) return i;
        return -1;
    }
    void insert(const char* s)
    {
        if (*s == 0) { return; } //null character
        int i = find_idx(*s - 'a');
        if (i < 0)
        {
            Trie* new_child = new Trie();
            nxt.push_back(new_child);
            idx.push_back(*s - 'a');
            i = nxt.size() - 1;
        }
	// do something
        nxt[i]->insert(s + 1);
    }
    void find(const char* s)
    {
        if (*s == 0) return;
        int i = find_idx(*s - 'a');
        if (i > -1)
        {
            // do something
            nxt[i]->find(s + 1);
        }
        return;
    }
};

/*
트라이(Trie): 문자열의 집합을 표현하는 트리 자료구조 
Reference: 프로그래밍 대회에서 배우는 알고리즘 문제해결전략 p783
*/
//트라이의 노드를 표현하는 객체의 선언
const int ALPHABETS=26; //알파벳 대문자를 저장하는 경우 각 노드는 26개의 자손을 가질 수 있다.
int toNumber(char ch){return ch-'A';}
//트라이의 한 노드를 나타내는 객체
struct TrieNode
{
    TrieNode* children[ALPHABETS];
    bool terminal; //이 노드가 종료 노드인가?
    TrieNode() : terminal(false)
    {
        memset(children, 0, sizeof(children));
    }
    ~TrieNode()
    {
        for(int i=0;i<ALPHABETS;i++)
            if(children[i]) delete(children[i]);
    }
    //O(M) (M은 문자열의 길이)
    void insert(const char* key) //이 노드를 루트로 하는 트라이에 문자열 key를 추가한다.
    {
        if(*key==0) terminal=true; //문자열이 끝나면 terminal만 참으로 바꾸고 종료
        else
        {
            int next=toNumber(*key); 
            if(children[next]==NULL) children[next]=new TrieNode(); //해당 자식 노드가 없다면 생성한다.
            children[next]->insert(key+1);
        }
    }
    //O(M) (M은 문자열의 길이)
    TrieNode* find(const char* key) //이 노드를 루트로 하는 트라이에 문자열 key와 대응되는 노드를 찾는다. 없으면 NULL을 반환한다.
    {
        if(*key==0) return this;
        int next=toNumber(*key);
        if(children[next]==NULL) return NULL;
        return children[next]->find(key+1);
    }
    /*
    find()가 종료 노드가 아닌 노드도 상관없이 반환한다는 점
    -> 트라이가 표현하는 집합에 해당 문자열이 진짜로 존재하는지 확인하기 위해서는 반환된 노드의 terminal 멤버가 참인지 확인해야 한다.
    -> 트라이는 포함하는 문자열들의 모든 접두사에 대응되는 노드들을 가지고 있기 때문에, 
       전체 문자열이 아닌 문자열의 첫 일부만을 가지고도 이 문자열로 시작하는 키가 있는지 쉽게 확인할 수 있다.
    */
};

/*
알파벳을 소문자만 받는다고 가정
Reference: ICPC Sinchon 22 Summer 7회차 문자열 
https://boycoding.tistory.com/204 : 동적 메모리 할당 이해하기
https://codemasterkimc.tistory.com/14 : -> 연산자 이해하기
https://codingdog.tistory.com/entry/c-string-cstr-%ED%95%A8%EC%88%98-string%EC%9D%84-char-%EB%A1%9C-%EB%B0%94%EA%BF%94%EB%B4%85%EC%8B%9C%EB%8B%A4
: c_str() 이해하기
*/
struct Trie
{
    Trie *ch[26]; //자식들의 주소를 가르키는 포인터 배열
    int key; //이 정점에서 끝나는 문자열이 있으면, 그 문자가 몇 번째 문자인지 표시, 끝나지 않으면 -1
    Trie() //생성자
    {
        fill(ch, ch+26, nullptr);
        key=-1;
    }
    ~Trie() //소멸자
    {
        for(int i=0;i<26;i++) delete ch[i];
    }
    void insert(const char *s, int id)
    {
        if(*s==0){key=id; return ;} //null character
        if(!ch[*s-'a']) ch[*s-'a']=new Trie();
        ch[*s-'a']->insert(s+1, id);
    }
    int find(const char *s)
    {
        if(*s==0) return key;
        if(!ch[*s-'a']) return -1;
        else return ch[*s-'a']->find(s+1);
    }
};
int main()
{
    string s; cin>>s;

    Trie* T=new Trie(); 
    T->insert(s.c_str(), 1); 
    /*
    Trie T;
    T.insert(s.c_str(), 1);
    이렇게 표현도 가능하다. 다만, 메모리 상의 차이가 있긴하다. 정확히는 아직 잘 모르겠다.
    */

    //이 부분으로 Trie 더 잘 이해할 수 있다.
    string s="abcdefg";
    const char *c=s.c_str();
    cout<<*c; //a
    c+=1;
    cout<<*c; //b
}

/*
간결한 구현
멤버 함수를 구현할 때,
- 문자열의 끝 처리
- 없는 노드 생성 처리
- 다음 노드 방문 처리
이 세 가지 까먹지 말고 포함하기
*/
struct Trie
{
	Trie* ch[26];
	
	Trie()
	{
		fill(ch, ch + 26, nullptr);
	}
	~Trie()
	{
		for (int i = 0; i < 26; i++) delete ch[i];
	}
    void insert(const char* s);
    void find(const char* s);
};
