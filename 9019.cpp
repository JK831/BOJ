#include<iostream>
#include<cstring>
#include<string>
#include<queue>
 
#define endl "\n"
#define MAX 10000
using namespace std;
 
int Start, End;
bool Visit[MAX];
 
void Initialize()
{
    memset(Visit, false, sizeof(Visit));
}
 
void Input()
{
    cin >> Start >> End;
}
 
string BFS(int a)
{
    queue<pair<int, string>> Q;
    Q.push(make_pair(a, ""));
    Visit[a] = true;
 
    while (Q.empty() == 0)
    {
        int x = Q.front().first;
        string s = Q.front().second;
        Q.pop();
 
        if (x == End) return s;
        
        int nx = x * 2;
        if (nx > 9999) nx = nx % 10000;
        if (Visit[nx] == false)
        {
            Visit[nx] = true;
            Q.push(make_pair(nx, s + "D"));
        }
 
        nx = x - 1;
        if (nx < 0) nx = 9999;
        if (Visit[nx] == false)
        {
            Visit[nx] = true;
            Q.push(make_pair(nx, s + "S"));
        }
 
        nx = (x % 1000) * 10 + (x / 1000);
        if (Visit[nx] == false)
        {
            Visit[nx] = true;
            Q.push(make_pair(nx, s + "L"));
        }
 
        nx = (x % 10) * 1000 + (x / 10);
        if (Visit[nx] == false)
        {
            Visit[nx] = true;
            Q.push(make_pair(nx, s + "R"));
        }
    }
}
 
 
void Solution()
{
    string R = BFS(Start);
    cout << R << endl;
}
 
void Solve()
{
    int Tc;
    cin >> Tc;
    for (int T = 1; T <= Tc; T++)
    {
        Initialize();
        Input();
        Solution();
    }
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solve();
 
    return 0;
}
