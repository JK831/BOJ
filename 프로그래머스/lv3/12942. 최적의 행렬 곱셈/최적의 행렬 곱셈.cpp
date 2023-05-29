#include <string>
#include <vector>

using namespace std;

// Key point: Chained Matrix Multiplication 알고리듬을 사용하여 해결한다
// dp[i][j] = i번째 행렬과 j번째 행렬을 곱할 때 시행할 수 있는 연산의 최솟값

int dp[201][201];
int d[201];

const int INF = 987654321;

int solution(vector<vector<int>> matrix_sizes) {
    int answer = 0;
    int numOfMatrices = matrix_sizes.size();
    
    d[0] = matrix_sizes[0][0];
    for (int i = 0; i < numOfMatrices; ++i)
    {
        d[i + 1] = matrix_sizes[i][1];
    }
    
    for (int n = 0; n < numOfMatrices; ++n)
    {
        for (int i = 1; i <= numOfMatrices - n; ++i)
        {
            int j = i + n; // 곱할 행렬의 번호
            if (i == j)
                dp[i][j] = 0;
            
            else
            {
                dp[i][j] = INF;
                for (int k = i; k <= j - 1; ++k) // 곱할 행렬들 사이에 있는 행렬들끼리 저장된 최소 곱셈 연산수와 비교하며 횟수가 더 작은 경우를 선택
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + d[i - 1] * d[k] * d[j]);
            }
        }
    }
    
    answer = dp[1][numOfMatrices];
    
    return answer;
}