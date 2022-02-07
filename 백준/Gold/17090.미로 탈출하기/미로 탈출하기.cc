#include<iostream>
#include<cstring>
 
#define endl "\n"
#define MAX 500
using namespace std;
 
int N, M, Answer;
int DP[MAX][MAX];
bool Visit[MAX][MAX];
char MAP[MAX][MAX];
 
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
 
int Dir_To_Idx(char A)
{
    if (A == 'U') return 3;
    else if (A == 'R') return 0;
    else if (A == 'D') return 2;
    else if (A == 'L') return 1;
}
 
void Input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
            DP[i][j] = -1;
        }
    }
}
 
int DFS(int x, int y)
{
    if (x < 0 || y < 0 || x >= N || y >= M) return 1;
    if (DP[x][y] != -1) return DP[x][y];
    
    DP[x][y] = 0;
    int Dir = Dir_To_Idx(MAP[x][y]);
 
    DP[x][y] = DFS(x + dx[Dir], y + dy[Dir]);
 
    return DP[x][y];
}
 
void Solution()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            Answer = Answer + DFS(i, j);
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