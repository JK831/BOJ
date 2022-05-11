#include<iostream>
#include<vector>
#include<algorithm>
 
#define endl "\n"
#define MAX 100000 + 1
using namespace std;
 
int N, M, Answer;
int Parent[MAX]; // 각 노드들의 부모 노드
vector<pair<int, pair<int, int>>> Edge; // 컴퓨터와 컴퓨터를 연결하는 데 필요한 비용(간선의 가중치)
 
void Input()
{
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int a, b, Cost;
        cin >> a >> b >> Cost;
        Edge.push_back(make_pair(Cost, make_pair(a, b)));
    }
}
 
int Find(int x)
{
    if (Parent[x] == x) return x;
    return Parent[x] = Find(Parent[x]);
}
 
void Union(int x, int y)
{
    x = Find(x);
    y = Find(y);
    
    if (x != y) Parent[y] = x;
}
 
bool SameParent(int x, int y)
{
    x = Find(x);
    y = Find(y);
 
    if (x == y) return true;
    
    return false;
}
 
void Solution()
{
    sort(Edge.begin(), Edge.end());
    
    for (int i = 1; i <= N; i++)
    {
        Parent[i] = i;
    }
    
    for (int i = 0; i < M; i++)
    {
        if (SameParent(Edge[i].second.first, Edge[i].second.second) == false)
        {
            Union(Edge[i].second.first, Edge[i].second.second);
            Answer += Edge[i].first;
        }
    }
    
    cout << Answer << endl;
}
 
void Solve()
{
    Input();
    Solution();
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solve();
 
    return 0;
}