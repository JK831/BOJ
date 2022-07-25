#include <string>
#include <vector>

#define INF 100000000

using namespace std;

template <typename T>
T Min (T a, T b)
{
    return a < b ? a : b;
}

void make_distance(const vector<vector<int>>& fares, vector<vector<int>>& dist, int n)
{
    for (int i = 0; i < fares.size(); i++)
    {
        int S = fares[i][0];
        int E = fares[i][1];
        int F = fares[i][2];
        
        dist[S][E] = F;
        dist[E][S] = F;
    }
    for (int i = 1; i <= n; i++) dist[i][i] = 0;
}

void floyd_warshall(vector<vector<int>>& dist, int n)
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j || i == k || j == k) continue;
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = Min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    make_distance(fares, dist, n);
    floyd_warshall(dist, n);
    
    answer = dist[s][a] + dist[s][b];
    
    for (int i = 0; i < dist.size(); i++)
    {
        if (dist[s][i] != INF && dist[i][a] != INF && dist[i][b] != INF)
            answer = Min(answer, dist[s][i] + dist[i][a] + dist[i][b]);
    }
    
    return answer;
}