#include <string>
#include <vector>

using namespace std;

// Key point: k번째 집까지 털었을 때 얻을 수 있는 최대 값을 배열에 저장하고 사용한다.

// 첫번째 집에서 시작 or 두번째 집에서 시작하는 경우 but 첫번째 집에서 시작할 시 마지막 집을 탐색할 수 없다 (첫번째 집과 붙어있으므로)
// -> 세번째 집부터 이전 집의 값과 전전 집의 값 + 현재 집의 값을 비교하여 큰 값을 저장한다.
// DP[k] = max(DP[k - 1], DP[k - 2] + DP[k]);

// 각 집에서 가질 수 있는 최댓값을 배열의 원소에 저장하게 되므로 똑같은 배열에서 두 케이스를 탐색할 수는 없다.
// -> 첫번째 집에서 시작하는 경우와 두번째 집에서 시작하는 경우의 최댓값을 저장하는 배열 분리, 분리된 배열의 첫번째 원소에 0을 넣음으로써 세번째 원소부터 점화식에 맞게 탐색할 수 있게 한다.



int solution(vector<int> money) {
    int answer = 0;
    
    int SizeOfMoney = money.size();
    
    // 배열 분리 후 첫번째 원소 0으로 초기화
    vector<int> case1(SizeOfMoney); // 첫번째 집부터 탐색하는 케이스
    vector<int> case2(SizeOfMoney); // 두번째 집부터 탐색하는 케이스
    case1[0] = case2[0] = 0;
    
    // money의 원소 복사
    copy(money.begin(), money.end() - 1, case1.begin() + 1);
    copy(money.begin() + 1, money.end(), case2.begin() + 1);
    
    for (int index = 2; index < SizeOfMoney; index++)
    {
        case1[index] = max(case1[index - 1], case1[index - 2] + case1[index]);
        case2[index] = max(case2[index - 1], case2[index - 2] + case2[index]);
    }
    
    answer = max(case1[SizeOfMoney - 1], case2[SizeOfMoney - 1]);
    
    return answer;
}