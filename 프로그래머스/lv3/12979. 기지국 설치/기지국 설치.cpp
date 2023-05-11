#include <iostream>
#include <vector>
using namespace std;

// Key point: 하나의 기지국이 커버할 수 있는 범위 = W * 2 + 1 이므로 이미 설치된 기지국이 커버할 수 없는 영역의 범위를 구하여 최소의 기지국을 설치한다.

// 하나의 기지국이 커버할 수 있는 아파트의 개수가 M이고 커버받아야 하는 아파트의 개수가 K라면
// 설치해야 하는 기지국의 개수:
//  if (K % M == 0) K / M
//  else if (K % M != 0) (K / M) + 1

int Install(int Start, int End, int W)
{
    int installRange = End - Start + 1;
    int coverRange = W * 2 + 1;
 
    if (installRange <= 0) return 0;
    if (installRange % coverRange == 0) return installRange / coverRange;
    return (installRange / coverRange) + 1;
}
 
int solution(int n, vector<int> stations, int w)
{
    int answer = 0;
    
    // 첫번째 기지국 이전의 커버받지 못하는 영역 먼저 계산
    answer = answer + Install(1, stations[0] - w - 1, w);
 
    for (int i = 1; i < stations.size(); i++)
    {
        // 각 기지국 사이 커버받지 못하는 영역 계산
        answer = answer + Install(stations[i - 1] + w + 1, stations[i] - w - 1, w);
    }
    
    // 마지막 기지국 이후 커버받지 못하는 영역 계산
    answer = answer + Install(stations[stations.size() - 1] + w + 1, n, w);
 
    return answer;
}
