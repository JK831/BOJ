#include <string>
#include <vector>

using namespace std;

// Key point: 멀리 있는 집부터 배달 및 수거하며 남은 용량을 누적하고 누적된 용량을 그 다음 집에 사용한다.

// -> deliveries[i]이나 pickups[i]가 각각 누적된 배달, 수거 용량보다 크다면
// --> 배달, 수거 용량을 각각 누적하며 각 용량이 현재 집에 배달, 수거해야 하는 양보다 커질 때까지 왔다 가야하는 횟수 count
// -> 누적된 용량에서 현재 집에 배달, 수거해야 하는 용량을 빼준다.
// -> 왔다 간 횟수 * (i + 1) * 2가 i번째 집에 배달을 완료하기 위해 오가야 하는 거리

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    long long answer = 0;
    long long DRem = 0, PRem = 0;
    
    for (int i = n - 1; i >= 0; --i)
    {
        if (deliveries[i] == 0 && pickups[i] == 0)
            continue;
        
        int Share = 0;
        
        while (DRem < deliveries[i] || PRem < pickups[i])
        {
            Share += 1;
            DRem += cap;
            PRem += cap;
        }
        
        DRem -= deliveries[i];
        PRem -= pickups[i];
        
        answer += Share * (i + 1) * 2;
    }
    
    return answer;
}