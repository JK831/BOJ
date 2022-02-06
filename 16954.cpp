#include<iostream>
#include<queue>
#include<vector>
 
#define endl "\n"
#define MAX 8
using namespace std;
 
char MAP[MAX][MAX];
char Wall_MAP[MAX][MAX][MAX];
vector<pair<int, int>> Wall_V;
 
int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1, 0 };
int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1, 0 };
 
void Input()
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == '#')
            {
                Wall_MAP[0][i][j] = '#';
                Wall_V.push_back(make_pair(i, j));
            }
        }
    }
    for (int t = 0; t < MAX; t++)
    {
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                if (Wall_MAP[t][i][j] == '#') continue;
                Wall_MAP[t][i][j] = '.';
            }
        }
    }
}
 
void Make_Wall_MAP()
{
    for (long unsigned int i = 0; i < Wall_V.size(); i++)
    {
        int x = Wall_V[i].first;
        int y = Wall_V[i].second;
        int Time = 1;
 
        while (1)
        {
            int nx = x + 1;
            int ny = y;
            if (nx >= MAX) break;
            
            Wall_MAP[Time][nx][ny] = '#';
            Time++;
            x = nx;
            y = ny;
        }
    }
}
 
void Print()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                cout << Wall_MAP[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << "#######################################" << endl;
    }
}
 
bool Can_Finish(int x, int T)
{
    for (int i = x - 1; i >= 0; i--)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (Wall_MAP[T][i][j] == '#') return false;
        }
    }
    return true;
}
 
int BFS(int a, int b)
{
    queue<pair<pair<int, int>, int>> Q;
    Q.push(make_pair(make_pair(a, b), 0));
 
    while (Q.empty() == 0)
    {
        int x = Q.front().first.first;
        int y = Q.front().first.second;
        int t = Q.front().second;
        Q.pop();
 
        if (x == 0) return 1;
        else
        {
            if (Can_Finish(x, t) == true) return 1;
        }
        
        for (int i = 0; i < 9; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nt = t + 1;
 
            if (nx >= 0 && ny >= 0 && nx < MAX && ny < MAX)
            {
                if (Wall_MAP[nt][nx][ny] == '.' && Wall_MAP[t][nx][ny] == '.')
                {
                    Q.push(make_pair(make_pair(nx, ny), nt));
                }
            }
        }
    }
    return 0;
}
 
bool Wall_State()
{
    for (int i = 0; i < 7; i++)
    {
        int Cnt = 0;
        for (int j = 0; j < MAX; j++)
        {
            if (MAP[i][j] == '#') Cnt++;
        }
        if (Cnt == 8) return false;
    }
    return true;
}
 
//(x,y) 말고 
void Solution()
{
    if (Wall_V.size() == 0)
    {
        cout << 1 << endl;
        return;
    }
    if (Wall_State() == false)
    {
        cout << 0 << endl;
        return;
    }
    Make_Wall_MAP();
    cout << BFS(7, 0) << endl;
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
