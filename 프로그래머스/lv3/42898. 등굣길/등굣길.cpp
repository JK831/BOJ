#include <string>
#include <vector>

#define DIV_NUM 1000000007;

using namespace std;

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    int DP[101][101] = {0, };
    
    for (int i = 0; i < puddles.size(); i++)
        DP[puddles[i][1]][puddles[i][0]] = -1;
    
    DP[1][1] = 1;
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (DP[i][j] == -1)
            {
                DP[i][j] = 0;
                continue;
            }
            DP[i][j] += (DP[i - 1][j] + DP[i][j - 1]) % DIV_NUM;
        }
    }
    
    answer = DP[n][m];
    return answer;
}