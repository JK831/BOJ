#include <iostream>
#include <vector>
using namespace std;

// Key point: DP를 사용하여 x번째 스티커까지 뜯어냈을 때 얻을 수 있는 최대값을 저장하고 이용한다.

// DP[x] = x번째 스티커까지 뜯었을 때 얻을 수 있는 최대값
// x번째 스티커를 떼어냈을 때 얻을 수 있는 값 -> DP[x - 2] + sticker[i]
// x번째 스티커를 떼어내지 않았을 때 얻을 수 있는 값 -> DP[x - 1]
// => 둘 중 큰 값을 DP[x]로 저장한다.

// 첫번째 스티커와 마지막 스티커가 연결되어 있으므로 첫번째 스티커를 뜯어냈을 경우엔 마지막 스티커를 뜯어내지 못한다.
// -> 첫번째 스티커를 뜯어낸 경우, 뜯지 않은 경우로 나누어 계산한 후 최종적으로 큰 결과를 return

int DP[100010];
 
int solution(vector<int> sticker)
{
    int answer = 0;
    int N = sticker.size();
    if (N == 1) return sticker[0];
 
    DP[0] = sticker[0];
    DP[1] = sticker[0];
    for (int i = 2; i < N - 1; ++i)
        DP[i] = max(DP[i - 2] + sticker[i], DP[i - 1]);
    
    answer = max(answer, DP[N - 2]);
    
    DP[0] = 0;
    DP[1] = sticker[1];
    for (int i = 2; i < N; ++i)
        DP[i] = max(DP[i - 2] + sticker[i], DP[i - 1]);
    
    answer = max(answer, DP[N - 1]);
 
    return answer;
}
