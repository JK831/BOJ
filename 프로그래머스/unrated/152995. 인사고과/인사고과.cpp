#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Key point: 정렬을 하여 완호보다 높은 점수를 가진 사람들의 수를 계산, 그 과정에서 인센티브를 받을 수 있는 지 없는 지 판별

// 근무 태도, 동료 평가 점수 둘 다 임의의 직원보다 낮은 경우에 인센티브를 받지 못하므로
// 근무 태도를 내림차순으로 정렬하면 동료 평가 점수에 대해 비교할 수 있다
// 정렬된 배열을 순회할 시 근무 태도 점수가 높은 직원부터 순회하게 되고,
// 근무 태도 점수가 높은 직원들의 동료 평가 점수를 기록하여 그 직원의 동료 평가 점수보다 동료 평가 점수가 높거나 같을 시
// 인센티브를 받을 수 있다. 반대로 동료 평가 점수가 기록된 점수보다 낮다면
// 임의의 직원보다 근무 태도 점수, 동료 평가 점수가 모두 낮은 것이므로 인센티브를 받지 못한다.
// -> 근무 태도 점수를 내림차순으로 정렬하고, 동료 평가 점수를 오름차순으로 정렬한 후 동료 평가 점수를 기록해나간다.
// -> 동료 평가 점수는 오름차순으로 기록되어 있으므로 동일한 근무 태도 점수를 가지고 있는 직원들에 대해
// -> 동료 평가 점수가 가장 높은 직원의 동료 평가 점수를 기록하게 되고
// -> 이후 근무 태도 점수가 낮은 직원을 탐색할 때 기존에 기록된 동료 평가 점수보다 해당 직원의 동료 평가 점수가 낮을 시
// -> 인센티브 받지 못함, 그리고 해당 직원이 완호일 경우 return -1
// -> 그렇지 않고 해당 직원의 점수의 총합이 완호의 점수의 총합보다 높을 시 ++answer

bool Compare(vector<int> a, vector<int> b) // 근무 태도 내림차순, 동료 평가 점수 오름차순 정렬
{
    if (a[0] > b[0])
        return true;
    else if (a[0] == b[0] && a[1] < b[1])
        return true;
    else
        return false;
}

int solution(vector<vector<int>> scores) {
    int answer = 1; // 순위는 1부터 매겨지므로
    vector<int> wanho = scores[0]; // 완호의 점수 저장
    int wanhoA = wanho[0], wanhoB = wanho[1], wanhoSum = wanhoA + wanhoB; // 완호의 근무 태도 점수, 동료 평가 점수, 두 점수의 합 저장
    sort(scores.begin(), scores.end(), Compare);
    
    int maxEval = 0;
    
    for (auto score : scores)
    {
        if (score[1] < maxEval) // 이전에 기록된 동료 평가 점수보다 현재 직원의 동료 평가 점수가 낮다면
        {
            if (score == wanho) // 그리고 그 직원이 완호라면
                return -1;
        }
        else
        {
            maxEval = max(maxEval, score[1]); // maxEval에 기록된 점수와 현재 점수를 비교해 더 높은 점수를 maxEval에 기록
            if (score[0] + score[1] > wanhoSum) // 만약 현재 직원의 점수의 총합이 완호의 점수 총합보다 높다면
                ++answer;
        }
    }
    return answer;
}