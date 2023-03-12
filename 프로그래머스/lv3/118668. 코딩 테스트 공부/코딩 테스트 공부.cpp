#include <string>
#include <vector>

using namespace std;

// Key Point: DP를 사용하여 특정 알고력, 코딩력에 도달할 때의 최소 비용을 저장해둔다.
// DP[alp][cop] = alp, cop에 도달하기 위한 최소 비용
// DP[a + alp_rwd][b + cop_rwd] = min(DP[a + alp_rwd][b + cop_rwd], DP[a][b] + cost)
// 문제를 풀어 도달할 알고력, 코딩력이 목표 알고력, 코딩력을 넘어가는 경우가 생기는데
// 이런 경우 (목표 알고력, 코딩력의 값)과 (현재 능력치에 도달하는 데 필요한 비용 + 문제의 비용)과 비교하여 더 작은 값으로 갱신한다.

#define INF 2147483647
#define MAX_POWER 152
#define MAX_PROBLEMS 100

int DP[MAX_POWER][MAX_POWER];

int solution(int alp, int cop, vector<vector<int>> problems) {
    int answer = 0;
    int goal_alp = 0;
    int goal_cop = 0;
    
    // 문제들 중 가장 높은 요구 알고력, 코딩력을 찾는다.
    for (auto problem : problems)
    {
        if (problem[0] > goal_alp)
            goal_alp = problem[0];
        if (problem[1] > goal_cop)
            goal_cop = problem[1];
    }
    
    // alp, cop가 이미 문제들이 요구하는 요구 알고력, 코딩력 이상일 시 바로 0 return
    if (goal_alp <= alp && goal_cop <= cop)
        return 0;
    
    if (alp >= goal_alp)
        alp = goal_alp;
    if (cop >= goal_cop)
        cop = goal_cop;
    
    // 초기값 설정
    for (int i = 0; i < MAX_POWER; i++)
    {
        for (int j = 0; j < MAX_POWER; j++)
            DP[i][j] = INF;
    }
    
    // 초기 능력치까지 도달하는 데 필요한 비용 = 0
    DP[alp][cop] = 0;
    
    // 현재 능력치(알고력 or 코딩력) + 1 까지 도달하는 데 필요한 비용 = 현재 능력치까지 도달하는 데 필요한 비용 + 1 한 값을 저장해준다.
    // 문제를 풀어 특정 수치의 능력치에 도달할 때에 든 비용과
    // 그냥 현재 능력치에서 1의 시간을 들여 1의 능력치를 증가시켰을 때의 비용을 비교하여 더 적은 비용을 저장해둔다.
    for (int i = alp; i <= goal_alp; i++)
    {
        for (int j = cop; j <= goal_cop; j++)
        {
            DP[i + 1][j] = min(DP[i + 1][j], DP[i][j] + 1);
            DP[i][j + 1] = min(DP[i][j + 1], DP[i][j] + 1);
            
            for (auto problem : problems)
            {
                if (i >= problem[0] && j >= problem[1])
                {
                    // 만약 현재 능력치에서 문제를 풀어 증가하여 도달한 알고력, 코딩력이 목표 알고력,코딩력보다 크다면
                    // 현재 능력치 + 문제의 비용과 목표 알고력, 코딩력의 값을 비교하여 더 작은 값을 목표 알고력, 코딩력에 저장
                    if (i + problem[2] > goal_alp && j + problem[3] > goal_cop)
                        DP[goal_alp][goal_cop] = min(DP[goal_alp][goal_cop], DP[i][j] + problem[4]);
                    
                    // 알고력, 코딩력 모두 크진 않으나 증가하여 도달한 알고력이 목표 알고력보다 크다면
                    // 현재 능력치 + 문제의 비용과 목표 알고력, 증가하여 도달한 코딩력 값을 비교하여 더 작은 값을 목표 알고력, 증가하여 도달한 코딩력에 저장
                    else if (i + problem[2] > goal_alp)
                        DP[goal_alp][j + problem[3]] = min(DP[goal_alp][j + problem[3]], DP[i][j] + problem[4]);
                    
                    // 알고력, 코딩력 모두 크진 않으나 증가하여 도달한 코딩력이 목표 코딩력보다 크다면
                    // 현재 능력치 + 문제의 비용과 증가하여 도달한 알고력, 목표 코딩력 값을 비교하여 더 작은 값을 증가하여 도달한 알고력, 목표 코딩력에 저장
                    else if (j + problem[3] > goal_cop)
                        DP[i + problem[2]][goal_cop] = min(DP[i + problem[2]][goal_cop], DP[i][j] + problem[4]);
                    
                    // 증가하여 도달한 알고력, 코딩력이 모두 목표 알고력, 목표 코딩력보다 작다면
                    // 현재 능력치에 도달하는 데 필요한 값 + 문제의 비용과 증가하여 도달한 알고력, 코딩력 값을 비교하여 더 작은 값을
                    // 증가하여 도달한 알고력, 코딩력 값에 저장
                    else if (i + problem[2] <= goal_alp && j + problem[3] <= goal_cop)
                        DP[i + problem[2]][j + problem[3]] = min(DP[i + problem[2]][j + problem[3]], DP[i][j] + problem[4]);
                }
            }
        }
    }
    
    answer = DP[goal_alp][goal_cop];
    
    return answer;
}