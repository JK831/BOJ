#include <string>
#include <vector>

using namespace std;

// Key point: 현재 건물을 보이는 자리에 배치, 또는 안 보이는 자리에 배치 하는 경우의 수가 있다. (가장 큰 건물 n은 작은 건물들 사이에 배치할 수 없다)

// 현재 건물을 보이게 배치할 시의 경우의 수 = 남은 건물들을 배치할 수 있는 경우의 수
// 현재 건물을 보이지 않게 배치할 시의 경우의 수 = 남은 건물들을 배치할 수 있는 경우의 수 * 남은 건물의 수 * 2 (현재 건물을 큰 건물 사이 사이에 배치할 시 보이지 않는다 -> 남은 건물의 수 * (큰 건물 사이에 배치하는 경우 + 큰 건물 뒤에 배치하는 경우)

// DP에 N건물을 배치할 때 k (0 <= k <= count) 개의 건물을 볼 수 있는 경우의 수 저장.
// DP[N][K] = N건물을 배치할 때 K개의 건물을 볼 수 있는 경우의 수

// 남은 건물의 수가 0이고 보인 건물의 수가 count와 같을 때 해당 경우 추가.
// DFS를 통해 빌딩을 배치할 수 있는 경우의 수 탐색

#define MOD 1000000007

vector<vector<int>> DP;

int DFS(int NumOfRemain, int Show)
{
    if (NumOfRemain == 0)
        return Show == 0 ? 1 : 0;
    if (NumOfRemain < Show || Show < 0)
        return 0;
    
    if (DP[NumOfRemain][Show] == 0)
    {
        long Result = 0;
        
        // 현재 건물을 보이게 배치한 경우
        Result += DFS(NumOfRemain - 1, Show - 1);
        
        // 현재 건물을 보이지 않게 배치한 경우
        long ResultOfRemain = DFS(NumOfRemain - 1, Show);
        Result += ResultOfRemain * (NumOfRemain - 1) * 2;
        
        DP[NumOfRemain][Show] = static_cast<int>(Result % MOD);
    }
    return DP[NumOfRemain][Show];
}

int solution(int n, int count) {
    int answer = 0;
    
    // DP 초기화
    DP.resize(n + 1);
    fill(DP.begin(), DP.end(), vector<int>(count + 1, 0));
    
    answer = DFS(n, count);
    return answer;
}