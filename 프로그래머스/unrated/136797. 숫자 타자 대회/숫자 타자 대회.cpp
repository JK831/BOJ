#include <string>
#include <memory.h>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

struct Element
{
    int y;
    int x;
    int count;
};

queue<Element> q;
int visited[4][3];
int dp[100005][4][3][4][3];

int board[4][3] = {
    { 1, 2, 3 },
    { 4, 5, 6 },
    { 7, 8, 9 },
    { 10, 0, 11 }
};
int coord[12][2] = {
    { 3, 1 },
    { 0, 0 },
    { 0, 1 },
    { 0, 2 },
    { 1, 0 },
    { 1, 1 },
    { 1, 2 },
    { 2, 0 },
    { 2, 1 },
    { 2, 2 },
    { 3, 0 },
    { 3, 2 },
};
int dir1[4][2] = {
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 }
};
int dirDiagonal[4][2] = {
    { -1, -1 },
    { -1, 1 },
    { 1, 1 },
    { 1, -1 },
};

string ns;
int n;

int checkRange(int y, int x)
{
    return y >= 0 and y < 4 and x >= 0 and x < 3;
}

int BFS(int y, int x, int ty, int tx)
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            visited[i][j] = 0;

    while (!q.empty()) q.pop();

    visited[y][x] = 1;
    q.push({ y, x, 0 });

    while (!q.empty())
    {
        Element elem = q.front();
        q.pop();

        for (const auto &dir: dir1)
        {
            int ny = elem.y + dir[0];
            int nx = elem.x + dir[1];

            if (checkRange(ny, nx) and !visited[ny][nx])
            {
                if (ny == ty and nx == tx) return elem.count + 2;
                visited[ny][nx] = 1;
                q.push({ ny, nx, elem.count + 2 });
            }
        }

        for (const auto &dir: dirDiagonal)
        {
            int ny = elem.y + dir[0];
            int nx = elem.x + dir[1];

            if (checkRange(ny, nx) and !visited[ny][nx])
            {
                if (ny == ty and nx == tx) return elem.count + 3;
                visited[ny][nx] = 1;
                q.push({ ny, nx, elem.count + 3 });
            } 
        }
    }

    return 100;
}

int solve(int d, int ly, int lx, int ry, int rx)
{
    if (d == n) return 0;

    if (dp[d][ly][lx][ry][rx] != -1) return dp[d][ly][lx][ry][rx];

    auto cur = coord[ns[d] - '0'];

    if ((cur[0] == ly and cur[1] == lx) or (cur[0] == ry and cur[1] == rx))
        return dp[d][ly][lx][ry][rx] = 1 + solve(d + 1, ly, lx, ry, rx);

    return dp[d][ly][lx][ry][rx] = min(BFS(ly, lx, cur[0], cur[1]) + solve(d + 1, cur[0], cur[1], ry, rx), BFS(ry, rx, cur[0], cur[1]) + solve(d + 1, ly, lx, cur[0], cur[1]));
}

int solution(string numbers) {
    ns = numbers;
    n = numbers.size();
    memset(dp, -1, sizeof(dp));
    return solve(0, 1, 0, 1, 2);
}