#include <string>
#include <vector>

// Key point: n이 커짐에 따라 늘어나는 빈 공간과 추가되는 경우의 수에 초점을 맞추어 점화식을 세워 해결
// ex) n이 4일시: 1칸을 배치한 후 나머지 3칸을 배치하는 경우의 수 + 2칸을 배치한 후 나머지 2칸을 배치하는 경우의 수 + 3칸을 배치한 후 나머지 1칸을 배치하는 경우의 수 + 새로운 타일링 형식으로 배치하는 경우의 수

// n에 따른 추가되는 경우의 수 (타일링 형태)
// 1: 1
// 2: 2
// 3: 5
// 4, 7, 10: 2
// 5, 8, 11: 2
// 6, 9, 12: 4

// DP[X] = while (1 <= i <= X - 2) {(DP[X - i] * c[i])} + c[X];

// 4 이상부턴 3을 주기로 2, 2, 4가 반복되므로 식을 전개한 후 DP[X] - DP[X - 3]를 할 경우 최종적으로
// DP[X] = DP(X - 1) + 2DP(X - 2) + 6DP(X - 3) + DP(X − 4) − DP(X − 6);

using namespace std;

const int mod = 1'000'000'007;

int solution(int n) {
    int answer = 0;
    vector<int> DP = {1, 1, 3, 10, 23, 62};
    
    if (n < 6)
        return DP[n];
    
    DP.resize(n + 1);
    
    for (int i = 6; i < n + 1; ++i)
    {
        DP[i] = (DP[i - 1] + (2L * DP[i - 2]) % mod + (6L * DP[i - 3]) % mod + DP[i - 4] - DP[i - 6] + mod) % mod;
    }
    
    answer = DP[n];
    return answer;
}