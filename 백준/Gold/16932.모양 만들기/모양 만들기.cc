#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
 
#define endl "\n"
#define MAX 1000
using namespace std;
 
int N, M, Answer = -987654321;
int MAP[MAX][MAX];
bool Visit[MAX][MAX];
 
vector<pair<int, int>> V;
vector<int> Size;
 
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
            if (MAP[i][j] == 0) V.push_back(make_pair(i, j));
        }
    }
}
 
int BFS(int a, int b, int Idx)
{
    queue<pair<int, int>> Q, NQ;
    Q.push(make_pair(a, b));
    NQ.push(make_pair(a, b));
 
    Visit[a][b] = true;
    int R_Value = 1;
 
    while (Q.empty() == 0)
    {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
 
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && ny >= 0 && nx < N && ny < M)
            {
                if (MAP[nx][ny] == 1 && Visit[nx][ny] == false)
                {
                    R_Value++;
                    Visit[nx][ny] = true;
                    Q.push(make_pair(nx, ny));
                    NQ.push(make_pair(nx, ny));
                }
            }
        }
    }
 
    while (NQ.empty() == 0)
    {
        int x = NQ.front().first;
        int y = NQ.front().second;
        NQ.pop();
 
        MAP[x][y] = Idx;
    }
    Size.push_back(R_Value);
    return R_Value;
}
 
void Solution()
{
    int Idx = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (MAP[i][j] == 1 && Visit[i][j] == false)
            {
                int Temp = BFS(i, j, Idx);
                Answer = Bigger(Answer, Temp);
                Idx++;
            }
        }
    }
 
 
    for (int i = 0; i < V.size(); i++)
    {
        set<int> Group_Visit;
 
        int x = V[i].first;
        int y = V[i].second;
        int Temp_Size = 0;
        int Cnt = 0;
 
        for (int j = 0; j < 4; j++)
        {
            int nx = x + dx[j];
            int ny = y + dy[j];
 
            if (nx >= 0 && ny >= 0 && nx < N && ny < M)
            {
                if (MAP[nx][ny] != 0)
                {
                    if (Group_Visit.find(MAP[nx][ny]) == Group_Visit.end())
                    {
                        Group_Visit.insert(MAP[nx][ny]);
                        Temp_Size = Temp_Size + Size[MAP[nx][ny] - 1] + 1;
                        Cnt++;    // 몇 개의 그룹이랑 겹치는지 Check
                    }
                }
            }
        }
 
        Temp_Size = Temp_Size - (Cnt - 1);
        Answer = Bigger(Answer, Temp_Size);
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
    Solve();
 
    return 0;
}