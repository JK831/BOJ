#include <string>
#include <vector>

using namespace std;

// Key point: 어떤 점수를 만들기 위해 던져야 하는 최소 횟수는 저장한 후 더 큰 점수를 만들기 위한 최소 횟수를 위해 사용할 수 있다. => DP 사용
// 1 ~ 20, 50 = 1번에 가능
// 트리플 = 3으로 나누어 떨어짐
// 더블 = 2로 나누어 떨어짐

int dp[100001][2];

void CalBestCase(int target)
{
    if (dp[target - 60][0] == dp[target - 50][0])
    {
        dp[target][0] = dp[target - 60][0] + 1;
        dp[target][1] = max(dp[target - 60][1], dp[target - 50][1] + 1);
    }
    else if (dp[target - 60][0] < dp[target - 50][0])
    {
        dp[target][0] = dp[target - 60][0] + 1;
        dp[target][1] = dp[target - 60][1];
    }
    else
    {
        dp[target][0] = dp[target - 50][0] + 1;
        dp[target][1] = dp[target - 50][1] + 1;
    }
}

vector<int> solution(int target) {
    vector<int> answer(2);
    
    for (int i = 1; i <= target; ++i)
    {
        if (i == 50 || i <= 20)
        {
            dp[i][0] = 1;
            dp[i][1] = 1;
        }
        else if (i <= 60 && i % 3 == 0)
        {
            dp[i][0] = 1;
            dp[i][1] = 0;
        }
        else if (i <= 40 && i % 2 == 0)
        {
            dp[i][0] = 1;
            dp[i][1] = 0;
        }
        else if (i > 50 && i <= 70)
        {
            dp[i][0] = 2;
            dp[i][1] = 2;
        }
        else if (i < 70)
        {
            if (i < 40)
            {
                dp[i][0] = 2;
                dp[i][1] = 2;
            }
            else
            {
                dp[i][0] = 2;
                dp[i][1] = 1;
            }
        }
        else
        {
            CalBestCase(i);
        }
    }
    answer[0] = dp[target][0];
    answer[1] = dp[target][1];
    
    return answer;
}