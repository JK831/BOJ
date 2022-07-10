#include<vector>
#include<queue>

using namespace std;

int M, N;
bool check[101][101] = {0, };
int dist[101][101] = {0, };

queue<pair<int, int>> q;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int solution(vector<vector<int> > maps)
{
    int answer = 0;
    M = maps[0].size();
    N = maps.size();
    
    q.push(make_pair(0, 0));
    check[0][0] = true;
    dist[0][0] = 1;
    while (!q.empty())
    {
        int curX  = q.front().first;
        int curY =  q.front().second;
        q.pop();
        
        for (int i = 0; i < 4; i++)
        {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            
            if (nx < 0 || ny < 0 || nx >= M || ny >= N)
            {
                continue;
            }
            
            if (check[ny][nx]) continue;
            
            if (maps[ny][nx] == 0) continue;
            
            check[ny][nx] = true;
            q.push(make_pair(nx, ny));
            dist[ny][nx] = dist[curY][curX] + 1;
        }
    }
    
    if (dist[N - 1][M - 1] == 0) return -1;
    else return dist[N - 1][M - 1];
}