#include <vector>
#include <cstring>

using namespace std;

int MOD = 20170805;

int N, M;
int DP[510][510][2];

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) {
    M = m;
    N = n;
    memset(DP, 0, sizeof(DP));
    
    DP[1][1][0] = DP[1][1][1] = 1;
    
    for (int i = 1; i <= M; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (city_map[i - 1][j - 1] == 0)
            {
                DP[i][j][0] = (DP[i][j][0] + DP[i][j - 1][0] + DP[i - 1][j][1]) % MOD;
                DP[i][j][1] = (DP[i][j][1] + DP[i][j - 1][0] + DP[i - 1][j][1]) % MOD;
            }
            else if (city_map[i - 1][j - 1] == 1) DP[i][j][0] = DP[i][j][1] = 0;
            else
            {
                DP[i][j][0] = DP[i][j - 1][0] % MOD;
                DP[i][j][1] = DP[i - 1][j][1] % MOD;
            }
        }
    }
    return DP[M][N][0] % MOD;
}