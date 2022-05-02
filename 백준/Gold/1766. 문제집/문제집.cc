#include<iostream>
#include<vector>
#include<queue>
 
#define endl "\n"
#define MAX 32010
using namespace std;
 
int N, M;
int Entry[MAX];
vector<int> Problem[MAX];
 
void Input()
{
    cin >> N >> M;
    
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        Problem[a].push_back(b);
        Entry[b]++;
    }
}
 
void Solution()
{
    priority_queue<int> Q; // 낮은 숫자부터 꺼내오기 위한 우선순위 큐
 
    for (int i = 1; i <= N; i++)
    {
        if (Entry[i] == 0) Q.push(-i);
    }
 
    while (Q.empty() == 0)
    {
        int Cur = -Q.top();
        Q.pop();
 
        cout << Cur << " ";
 
        for (int i = 0; i < Problem[Cur].size(); i++)
        {
            int Next = Problem[Cur][i];
            Entry[Next]--;
            
            if (Entry[Next] == 0) Q.push(-Next);
        }
    }
    cout << endl;
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
