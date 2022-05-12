#include<iostream>
#include<vector>
#include<algorithm>

#define endl "\n"
#define MAX 10000 + 1
using namespace std;

int Vertex, Edge, Answer;
int Parent[MAX];
vector<pair<int, pair<int, int>>> graph;

void Input()
{
    cin >> Vertex >> Edge;
    
    for (int i = 0; i < Edge; i++)
    {
        int From, To, Cost;
        cin >> From >> To >> Cost;
        graph.push_back(make_pair(Cost, make_pair(From, To)));
    }
}

int Find(int x)
{
    if (Parent[x] == x) return x;
    return Find(Parent[x]);
}

bool SameParent(int a, int b)
{
    a = Find(a);
    b = Find(b);
    
    if (a == b) return true;
    
    return false;
}

void Union(int a, int b)
{
    a = Find(a);
    b = Find(b);
    
    if (a != b) Parent[b] = a;
}

void Solution()
{
    sort(graph.begin(), graph.end());
    
    for (int i = 1; i <= Vertex; i++)
    {
        Parent[i] = i;
    }
    
    for (int i = 0; i < Edge; i++)
    {
        if (SameParent(graph[i].second.first, graph[i].second.second) == false)
        {
            Union(graph[i].second.first, graph[i].second.second);
            Answer += graph[i].first;
        }
    }
    
    cout << Answer << endl;
    
}

void Solve()
{
    Input();
    Solution();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    Solve();
    return 0;
}