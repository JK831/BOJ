#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

// Key point: 현재 시간에 특정 온도에 도달하기 위한 최소 비용을 저장하고 활용하여 마지막 시간에 도달했을 때의 최소 비용을 구한다.
// DP[Time][Temp] = 특정 시간에 특정 온도에 도달할 때 필요한 최소 비용.
// 특정 온도에 도달하기 위해선 이전 시간의 온도가 현재 온도보다 1도 적거나 같거나 1도 높은 경우만 가능하다.
// DP[CurTime][CurTemp] = 현재 시간 특정 온도에 도달하기 위한 최소 비용

// 승객이 탑승할 때에는 반드시 t1 ~ t2 사이에 있어야 함

// 가능한 경우:
// - 현재 실내 온도가 외부 온도와 같은 경우 -> 비용 없이 현재 온도 유지가능
// - 실내 온도와 외부 온도가 다른 경우 -> 온도가 조정되거나(에어컨을 끈 경우), 실내 온도를 변화시키거나(희망 온도와 실내 온도가 다른 경우), 실내 온도 유지(희망 온도 = 실내 온도)



int solution(int temperature, int t1, int t2, int a, int b, vector<int> onboard) {
    if (temperature >= t1 && temperature <= t2) // temperature가 적정 온도 사이라면 바로 return
        return 0;
    
    int answer = 0;
    const int INF = 987654321;
    const int LastTime = onboard.size() - 1;
    const int AdjustedTemp = temperature + 11;
    const int AdjustedT1 = t1 + 11;
    const int AdjustedT2 = t2 + 11;
    const int Adjustment = temperature < t1 ? -1 : 1; // 에어컨을 켜지 않았을 시 시간이 지남에 따라 변화될 온도 수치
    
    // 만족해야 할 조건: 승객이 탑승했을 때 현재 실내 온도가 [t1, t2] 구간에 포함되어야 한다.
    // 각 시간 별 조건을 만족할 때의 최소 비용을 저장할 DP 배열
    vector<vector<int>> DP(LastTime + 1, vector<int>(53, INF)); // 온도를 인덱스로 하여 DP 배열에 수월하게 접근하기 위해 time * 전체 온도 범위 + 2의 크기로 배열 선언
    DP[0][AdjustedTemp] = 0;
    
    
    for (int CurTime = 1; CurTime <= LastTime; ++CurTime)
    {
        // Adjustment가 -1인지 1인지 모르므로 DP 배열 인덱스 범위를 넘어가는 인덱스에 접근할 가능성이 있으므로 시작 범위와 끝 범위를 1씩 증가시켜준다.
        int start = 1;
        int end = 51;
        
        if (onboard[CurTime] == 1)
        {
            start = AdjustedT1;
            end = AdjustedT2;
        }
        
        for (int CurTemp = start; CurTemp <= end; ++CurTemp)
        {
            // 현재 실내 온도가 실외 온도와 같은 경우
            if (CurTemp == AdjustedTemp)
            {
                // 이전 시간에도 실내 온도가 실외 온도와 같았고 에어컨을 가동하지 않고 온도를 유지시킨 경우
                if (DP[CurTime - 1][CurTemp] < DP[CurTime][CurTemp])
                    DP[CurTime][CurTemp] = DP[CurTime - 1][CurTemp];
                
                
            }
            else
            {   
                // 에어컨을 가동하여 실내 온도를 변경시킨 경우
                if (DP[CurTime - 1][CurTemp + Adjustment] + a < DP[CurTime][CurTemp])
                    DP[CurTime][CurTemp] = DP[CurTime - 1][CurTemp + Adjustment] + a;
                
                
                // 에어컨을 가동하여 실내 온도를 유지시킨 경우
                if (DP[CurTime - 1][CurTemp] + b < DP[CurTime][CurTemp])
                    DP[CurTime][CurTemp] = DP[CurTime - 1][CurTemp] + b;
    
            }
            // 에어컨을 가동하지 않아 실내 온도가 실외 온도를 따라가는 경우
            if (DP[CurTime - 1][CurTemp - Adjustment] < DP[CurTime][CurTemp])
                DP[CurTime][CurTemp] = DP[CurTime - 1][CurTemp - Adjustment];   
        }
    }
    
    
    
    answer = *min_element(DP[LastTime].begin(), DP[LastTime].end());
    return answer;
}