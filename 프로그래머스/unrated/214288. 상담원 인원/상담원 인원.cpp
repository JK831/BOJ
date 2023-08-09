#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

// Key point: 각 유형 별로 멘토의 수를 하나씩 증가시키면서 멘토의 수가 증가함에 따라 줄어든 대기 시간을 구하고 현재 대기 시간이 가장 많이 줄어드는 유형에 멘토를 배치한다.
// 멘토가 이용가능한 시각을 우선순위 큐에 넣어 다음 상담자가 멘토를 이용할 수 있는 가장 빠른 시간을 구한다.
// 우선순위 큐가 비어있거나, 우선순위 큐의 사이즈가 이용가능한 멘토의 수보다 작을 시 바로 이용 가능 (상담 종료 시간 = 도착 시각 + 상담 시간)
// 그렇지 않다면 우선순위 큐의 top 원소에 저장되어 있는 (상담 종료 시간 - 도착 시각)이 대기시간이 되고 (상담 종료 시간 + 상담 시간)이 새로운 상담 종료 시간이 된다.

// 빠른 시각에 도착한 참가자부터 상담 시작
// 유형별로 도착 시각, 상담 시간 저장후 도착 시각 기준으로 오름차순으로 정렬
// 그 후 가장 빨리 마친 멘토를 다음 상담자에게 배치 -> 우선순위 큐에 상담을 종료하는 (이용 가능한) 시간 삽입

bool Compare(const tuple<int, int>& a, const tuple<int, int>& b)
{
    return get<0>(a) < get<0>(b);
}

int CalculateWaiting(const vector<tuple<int, int>>& times, int numOfMento)
{
    priority_queue<int, vector<int>, greater<int>> earliestTime;
    int waitingTime = 0;
    
    for (auto time : times)
    {
        int arrivedTime = get<0>(time);
        int duration = get<1>(time);
        
        if (earliestTime.empty() || earliestTime.size() < numOfMento)
        {
            earliestTime.push(arrivedTime + duration);
        }
            
        else
        {
            int nextAvailableTime = earliestTime.top();
            earliestTime.pop();
            
            if (arrivedTime < nextAvailableTime)
            {
                // 기다린 시간 = (이용 가능한 시각 - 도착한 시각)
                waitingTime += nextAvailableTime - arrivedTime;
                // 다음 이용 가능한 시각 = 이용 가능한 시각 + 상담 시간
                earliestTime.push(nextAvailableTime + duration);
            }
            else // 도착한 시각 + 상담 시간 = 상담을 마친 시각
            {
                earliestTime.push(arrivedTime + duration);
            }
                
        }
    }
    
    return waitingTime;
}

int solution(int k, int n, vector<vector<int>> reqs) {
    int answer = 0;
    int ExtraMento = n - k;
    
    // 유형 별 도착 시각, 상담 시간
    vector<vector<tuple<int, int>>> timeByType(k + 1);
    // 유형 별 멘토의 수에 따른 대기 시간
    vector<vector<int>> waitingTimeByMentoNum(k + 1, vector<int>(n - k + 1));
    // 유형 별 배치된 멘토의 수
    vector<int> numOfMentoByType(k + 1, 1);
    
    // 타입 별로 도착 시각과 상담 시간을 저장
    for (auto req : reqs)
    {
        int arrivedTime = req[0];
        int duration = req[1];
        int type = req[2];
        
        timeByType[type].push_back({arrivedTime, duration});
    }
    
    for (auto time : timeByType)
    {
        // 도착 시각을 기준으로 오름차순으로 정렬
        sort(time.begin(), time.end(), Compare);
    }
    
    // 타입 별로 멘토 수에 따른 대기시간을 계산한다.
    for (int type = 1; type < k + 1; ++type)
    {
        for (int numOfMento = 1; numOfMento < n - k + 1; ++numOfMento)
        {
            int waitingTime = CalculateWaiting(timeByType[type], numOfMento);
            // 현재 유형의 멘토의 숫자 별 대기시간을 저장
            waitingTimeByMentoNum[type][numOfMento] = waitingTime;
        } 
    }
    
    while (ExtraMento-- > 0)
    {
        int maxReducedWaitingTime = 0;
        int choosedType = 0;
        
        for (int type = 1; type < k + 1; ++type)
        {
            // 현재 멘토의 수
            int currentNumOfMento = numOfMentoByType[type];
            // 멘토의 수에 따른 대기시간
            int currentWaitingTime = waitingTimeByMentoNum[type][currentNumOfMento];
            // 멘토의 수가 1 증가 했을 때 줄어드는 대기시간
            int reducedWaitingTime = currentWaitingTime - waitingTimeByMentoNum[type][currentNumOfMento + 1];
            
            // 줄어든 대기시간이 저장된 최대값보다 크다면
            if (reducedWaitingTime >= maxReducedWaitingTime)
            {
                // 최댓값 갱신
                maxReducedWaitingTime = reducedWaitingTime;
                // 최댓값을 갱신한 유형 저장
                choosedType = type;
            }
        }
        
        // 대기시간이 줄어들지 않았다면 탐색 종료
        if (maxReducedWaitingTime == 0) break;
        
        // 최댓값을 갱신한 유형의 멘토 수를 1 증가시킨다.
        ++numOfMentoByType[choosedType];
    }
    
    // 타입별로 갱신된 멘토의 수에 따른 대기시간을 계산하여 answer에 더한다.
    for (int type = 1; type < k + 1; ++type)
    {
        if (timeByType[type].empty()) continue;
        answer += CalculateWaiting(timeByType[type], numOfMentoByType[type]);
    }
    
    return answer;
}