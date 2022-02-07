#include<iostream>
#include<cstring>
#include<queue>
 
#define endl "\n"
#define MAX 100
using namespace std;
 
int N, Max_Value, Min_Value;
int MAP[MAX][MAX];
bool Visit[MAX][MAX];
 
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
 
void Input()
{
    Max_Value = -1;
    Min_Value = 500;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] > Max_Value) Max_Value = MAP[i][j];
            if (MAP[i][j] < Min_Value) Min_Value = MAP[i][j];
        }
    }
}
 
bool BFS(int Diff)
{
    queue<pair<int, int>> Q;
    
    for (int i = Min_Value; i <= Max_Value; i++)
    {
        memset(Visit, true, sizeof(Visit));
 
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                if (i <= MAP[j][k] && MAP[j][k] <= i + Diff) Visit[j][k] = false;
            }
        }
 
        Q.push(make_pair(0, 0));
 
        while (Q.empty() == 0)
        {
            int x = Q.front().first;
            int y = Q.front().second;
            Q.pop();
 
            if (Visit[x][y] == true) continue;
            Visit[x][y] = true;
 
            if (x == N - 1 && y == N - 1) return true;
 
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
 
                if (nx >= 0 && ny >= 0 && nx < N && ny < N)
                {
                    Q.push(make_pair(nx, ny));
                }
            }
        }
    }
    return false;
}
 
void Solution()
{
    int Start = 0;
    int End = Max_Value - Min_Value;
    int Mid;
 
    while (Start <= End)
    {
        Mid = (Start + End) / 2;
        if (BFS(Mid) == true) End = Mid - 1;
        else Start = Mid + 1;
    }
    cout << End + 1 << endl;
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