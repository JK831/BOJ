#include <string>
#include <vector>

using namespace std;

// Key point: DP를 사용하여 n원을 만들 수 있는 경우의 수를 DP 배열에 저장한 후 이후의 계산에 사용한다.
// n원 = 현재 사용 동전원 + 거스름돈원
// -> n원을 만들 수 있는 경우의 수 = 이전 동전을 사용했을 때의 경우의 수 + 거스름돈을 만들 수 있는 경우의 수

// 0원을 만들 수 있는 경우의 수 = 0

const int MAX = 1'000'000'007;

int solution(int n, vector<int> money) {
    int answer = 0;
    
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    
    int change = 0;
    
    for (auto kind : money)
    {
        // 가지고 있는 동전의 종류 별로
        for (int i = 1; i <= n; ++i)
        {
            // 현재 목표 원보다 작거나 같은지 (i원을 만들 수 있는지) 체크하여 만들 수 있다면 경우의 수 추가
            change = 0;
            if (i >= kind)
            {
                change = i - kind;
                dp[i] = (dp[i] + dp[change]) % MAX;
            }
            else
                continue;
            
        }
    }
    
    answer = dp[n];
    return answer;
}