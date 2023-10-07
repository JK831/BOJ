#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Key point: DP[n] = n일 때 만들 수 있는 경우의 수라 할 때 DP[cur] = DP[2] * DP[cur - 2] + 2 (DP[cur - 4] + DP[cur - 6] ...) + DP[2] + 2
// DP[2] = 3
// 마지막에 붙은 2는 새롭게 추가되는 경우 2가지
// -> DP[n - 2] - DP[n - 4] = (DP[2] - 1) * DP[n - 4] + 2 (DP[n - 6] + DP[n - 8] ...) + DP[2] + 2 이므로
// --> DP[n] = (DP[2] + 1) * DP[n - 2] - DP[n - 4] = 4DP[n - 2] - DP[n - 4]



int solution(int n) {
    if (n % 2) return 0;
    int answer = 0;
    const long long INF = 1000000007;
    vector<long long> DP(n + 1, 0);
    
    DP[0] = 1;
    DP[2] = 3;
    DP[4] = 11;
    
    for (int i = 6; i < n + 1 ; i += 2)
    {
        DP[i] = (DP[i - 2] * 3) % INF;
        for (int j = i - 4 ; j >= 0 ; j -= 2)
        {
            DP[i] += (DP[j] * 2) % INF;
        }
    }
    
    answer = DP[n] % INF;
    
    return answer;
}