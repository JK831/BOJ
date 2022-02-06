#include<iostream>
#include<cstring>
 
#define endl "\n"
#define MAX 500
using namespace std;
 
int N, M, Answer;
int MAP[MAX][MAX];
bool Visit[MAX][MAX];
 
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
 
int Bigger(int A, int B) { if (A > B) return A; return B; }
 
void Input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
        }
    }
}
 
void DFS(int x, int y, int Sum, int Cnt)
{
    Visit[x][y] = true;
 
    if (Cnt == 3)
    {
        Answer = Bigger(Answer, Sum);
        return;
    }
 
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
        if (Visit[nx][ny] == true) continue;
 
        DFS(nx, ny, Sum + MAP[nx][ny], Cnt + 1);
        Visit[nx][ny] = false;
    }
}
 
void Shape1(int x, int y)
{
    int Tmp_Sum = 0;
    Tmp_Sum = MAP[x][y] + MAP[x][y + 1] + MAP[x][y + 2] + MAP[x - 1][y + 1];
    if (Tmp_Sum > Answer) Answer = Tmp_Sum;
}
 
void Shape2(int x, int y)
{
    int Tmp_Sum = 0;
    Tmp_Sum = MAP[x][y] + MAP[x][y + 1] + MAP[x][y + 2] + MAP[x + 1][y + 1];
    if (Tmp_Sum > Answer) Answer = Tmp_Sum;
}
 
void Shape3(int x, int y)
{
    int Tmp_Sum = 0;
    Tmp_Sum = MAP[x][y] + MAP[x + 1][y] + MAP[x + 2][y] + MAP[x + 1][y + 1];
    if (Tmp_Sum > Answer) Answer = Tmp_Sum;
}
 
void Shape4(int x, int y)
{
    int Tmp_Sum = 0;
    Tmp_Sum = MAP[x][y] + MAP[x - 1][y + 1] + MAP[x][y + 1] + MAP[x + 1][y + 1];
    if (Tmp_Sum > Answer) Answer = Tmp_Sum;
}
 
void Solution()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            memset(Visit, false, sizeof(Visit));
            DFS(i, j, MAP[i][j], 0);
            if (i - 1 >= 0 && j + 2 < M) Shape1(i, j);
            if (j + 2 < M && i + 1 < N) Shape2(i, j);
            if (i + 2 < N && j + 1 < M) Shape3(i, j);
            if (i + 1 < N && i - 1 >= 0 && j + 1 < M) Shape4(i, j);
        }
    }
}
 
void Solve()
{
    Input();
    Solution();
 
    cout << Answer << endl;
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    Solve();
 
    return 0;
}
