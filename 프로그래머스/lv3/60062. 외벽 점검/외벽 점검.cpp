#include <vector>
#include <algorithm>

using namespace std;

// Key point: 각 지점에서 각 친구를 다른 순서로 보내어 최소 인원의 친구들을 보낼 수 있는 경우를 체크하는 완전 탐색 방식으로 탐색.
// 반시계 방향 이동은 시계 방향 이동과 거리로는 똑같으므로 반시계 방향 이동을 따로 처리하지 않고 시계 방향 이동으로 처리한다.
// -> 모든 지점에서 시계 방향 탐색이 가능해야 하므로 각 지점 별로 (지점 + N) 값을 가지는 지점을 추가해준다.

#define FRIEND_MAX 10

int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = FRIEND_MAX;
    
    int weakSize = weak.size();
    weak.reserve(weakSize * 2);
    
    for(int i = 0; i < weakSize - 1; ++i) // 시계 방향 탐색을 위해 weak에 추가로 weak[i] + n의 값들을 넣어준다
    {
        weak.push_back(weak[i] + n);
    }
    
    sort(dist.begin(), dist.end()); // next_permutation 사용 위해 정렬해준다
    
    do {
        for (int i = 0; i < weakSize; ++i)
        {
            int start = weak[i];
            int end = weak[i + weakSize - 1];
            
            for (int friendNum = 0; friendNum < dist.size(); ++friendNum)
            {
                start += dist[friendNum]; // 현재 지점에서 친구 이동
                
                if (start >= end) // 모든 지점 도달 하였을 경우
                {
                    answer = min(answer, friendNum + 1);
                    break;
                }
                
                // 외벽 점검을 모두 마치지 못했으면 다음 취약 지점으로 이동
                for (int nextPoint = i + 1; nextPoint < i + weakSize; ++nextPoint)
                {
                    if (weak[nextPoint] > start)
                    {
                        start = weak[nextPoint];
                        break;
                    }
                }
            }
        }
    } while (next_permutation(dist.begin(), dist.end()));
    
    if (answer == FRIEND_MAX) return -1;
    
    return answer;
}