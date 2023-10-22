#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Key point: 요격 구간을 설정하여 그 구간에서 요격 가능한 미사일을 포함. 포함한 미사일의 s, e에 따라 구간을 갱신하며 발사 횟수를 탐색한다.

// 요격 가능 구간: 여러 개의 미사일을 어떤 지점에서 요격 가능할 시 해당 지점은 미사일들 중 가장 큰 시작 지점 ~ 가장 작은 종료 지점 구간에 포함됨. (종료지점 > 시작지점)

// 미사일을 끝 지점 기준으로 오름차순으로 정렬하여
// 현재 미사일의 시작 지점이 이전 미사일의 종료 지점보다 작고 종료 지점이 이전 미사일의 것보다 크거나 같은지 체크한다.
// 만약 그럴 시 겹치는 미사일이고, 그렇지 않다면 요격 횟수 + 1, 이전 미사일 종료 지점을 현재 미사일의 종료 지점으로 설정
// 반복

bool Compare(const vector<int>& A, const vector<int>& B)
{
    return A[1] < B[1];  
}

int solution(vector<vector<int>> targets) {

    int answer = 0;
    int End = -1;
    
    sort(targets.begin(), targets.end(), Compare);
    
    for (const auto& Target : targets)
    {
        if (Target[0] < End && Target[1] >= End )
        {
            continue;
        }
        else
        {
            End = Target[1];
            ++answer;
        }
    }
    
    return answer;
}