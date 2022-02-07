#include<iostream>
#include<cstring>
#include<vector>

#define MAX 31
using namespace std;

/* 백트래킹을 사용하여, 여러 방향에 대해 각 방향에서 탐색할 수 있는 모든 칸을 탐색하는 방식으로 진행,
    가장 방향을 적게 돌린 횟수 리턴*/

int N, M;
int M_Area;
int Answer;
char MAP[MAX][MAX];
bool Visit[MAX][MAX];
vector<pair<int, int>> Dot;
 
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
 
void Initialize()
{
    memset(Visit, false, sizeof(Visit));
    memset(MAP, 0, sizeof(MAP));
    M_Area = 0;
    Answer = 987654321;
    Dot.clear();
}
 
void Input()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == '.')
            {
                Dot.push_back(make_pair(i, j));
                M_Area++;
            }
        }
    }
}
 
bool Range_Over(int x, int y)
{
    if (x < 0 || y < 0 || x >= N || y >= M) return true;    // 범위 밖을 벗어나면 true
    return false;
}
 
void Move(int x, int y, int d, int Cnt, int Turn_Cnt)
{
    if (Cnt == M_Area)
    {
        if (Answer > Turn_Cnt) Answer = Turn_Cnt;
        return;
    }
 
    int nx = x + dx[d];
    int ny = y + dy[d];
 
    if (Range_Over(nx, ny) == false && Visit[nx][ny] == false && MAP[nx][ny] == '.')
    {
        Visit[nx][ny] = true;
        Move(nx, ny, d, Cnt + 1, Turn_Cnt);
        Visit[nx][ny] = false;
    }
    else
    {
        for (int nd = 0; nd < 4; nd++)
        {
            if (nd == d) continue;
            nx = x + dx[nd];
            ny = y + dy[nd];
            
            if (Range_Over(nx, ny) == false && Visit[nx][ny] == false && MAP[nx][ny] == '.')
            {
                Visit[nx][ny] = true;
                Move(nx, ny, nd, Cnt + 1, Turn_Cnt + 1);
                Visit[nx][ny] = false;
            }
        }
    }    
}
 
void Solution()
{
    if (M_Area == 1)
    {
        Answer = 0;
        return;
    }
    
    for(int i = 0 ; i < Dot.size(); i++)
    {
        int x = Dot[i].first;
        int y = Dot[i].second;
 
        for (int d = 0; d < 4; d++)
        {
            Visit[x][y] = true;
            Move(x, y, d, 1, 1);
            Visit[x][y] = false;
        }
    }    
}
 
void Solve()
{
    int Tc = 1;
    while (cin >> N >> M)
    {
        Initialize();
        Input();
        Solution();
 
        if (Answer == 987654321) Answer = -1;
        cout << "Case " << Tc << ": " << Answer << endl;
        Tc++;
    }
}
 
int main(void)
{
    Solve();
 
    return 0;
}