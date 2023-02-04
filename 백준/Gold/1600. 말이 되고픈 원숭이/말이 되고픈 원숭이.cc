#include<iostream>
#include<queue>
 
#define endl "\n"
#define MAX 200
using namespace std;
 
int W, H, K;
int MAP[MAX][MAX];
bool Visited[MAX][MAX][31]; // K <= 30, third demension means count of using ability so far
 
int dx[] = { 0, 1, 0, -1 }; // n, e, s, w
int dy[] = { -1, 0, 1, 0 };
int horseDx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
int horseDy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
 
void Input()
{
    cin >> K;
    cin >> W >> H;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> MAP[i][j];
        }
    }
}
 
void Solution()
{
    queue<pair<pair<int, int>, pair<int, int>>> Q; // Insert coordination, count of move, count of using horse ability
    Q.push(make_pair(make_pair(0, 0), make_pair(0, 0))); // Init for start
    Visited[0][0][0] = true;
 
    while (Q.empty() == 0)
    {
        int x = Q.front().first.first;
        int y = Q.front().first.second;
        int moveCount = Q.front().second.first;
        int restTime = Q.front().second.second;
        Q.pop();
 
        if (x == W - 1 && y == H - 1) // if arrive at destination
        {
            cout << moveCount << endl;
            return;
        }
        if (restTime < K)
        {
            for (int i = 0; i < 8; i++)
            {
                int nextX = x + horseDx[i];
                int nextY = y + horseDy[i];
                if (nextX >= 0 && nextY >= 0 && nextX < W && nextY < H) // check if can move to
                {
                    if (MAP[nextY][nextX] == 0 && Visited[nextY][nextX][restTime + 1] == false) // if first time
                    {
                        Visited[nextY][nextX][restTime + 1] = true;
                        Q.push(make_pair(make_pair(nextX, nextY), make_pair(moveCount + 1, restTime + 1)));
                    }
                }
            }
        }
 
        for (int i = 0; i < 4; i++)
        {
            int nextX = x + dx[i];
            int nextY = y + dy[i];
 
            if (nextX >= 0 && nextY >= 0 && nextX < W && nextY < H) // check if can move to
            {
                if (MAP[nextY][nextX] == 0 && Visited[nextY][nextX][restTime] == false)
                {
                    Visited[nextY][nextX][restTime] = true;
                    Q.push(make_pair(make_pair(nextX, nextY), make_pair(moveCount + 1, restTime)));
                }
            }
        }
    }
    cout << -1 << endl;
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