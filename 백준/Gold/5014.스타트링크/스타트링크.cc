#include<iostream>
#include<queue>
#define MAX 1000000 + 1
using namespace std;
 
int F, S, G, U, D;
bool Visit[MAX];
 
void Input()
{
    cin >> F >> S >> G >> U >> D;
}
 
int BFS()
{
    queue<pair<int, int>> Q;
    Q.push(make_pair(S, 0));
    Visit[S] = true;
    
    while (Q.empty() == 0)
    {
        int Pos = Q.front().first;
        int Cnt = Q.front().second;
        Q.pop();
 
        if (Pos == G) return Cnt;
 
        if (Pos + U <= F && Visit[Pos+U] == false)
        {
            Q.push(make_pair(Pos + U, Cnt + 1));
            Visit[Pos + U] = true;
        }
        if (Pos - D > 0 && Visit[Pos - D] == false)
        {
            Q.push(make_pair(Pos - D, Cnt + 1));
            Visit[Pos - D] = true;
        }
    }
    return -1;
}
 
void Solution()
{
    int Answer = BFS();
    if (Answer == -1) cout << "use the stairs" << endl;
    else cout << Answer << endl;
}
 
void Solve()
{
    Input();
    Solution();
}
 
int main(void)
{
    Solve();
    return 0;
}