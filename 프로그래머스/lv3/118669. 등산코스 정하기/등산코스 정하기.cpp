#include <string>
#include <vector>
#include <queue>

using namespace std;

// 출발지에서 산봉우리까지 갔을 시 끝
// 그 동안의 intensity가 가장 작은 경로 찾아줘야 함
// heap을 사용하여 최소 가중치 찾아준다. heap에는 정점과 가중치(해당 지점까지 도달하는 동안의 최대 가중치) 들어간다.
// 출입구의 intensity에는 -1을 넣어주어서 가중치 비교 시 항상 비교 지점의 가중치보다 작게 한다.
// 이렇게 할 시 출입구는 항상 intensity를 -1로 유지한 상태에서 연결된 지점들을 탐색할 수 있게 된다.
// bool 배열 사용하여 산봉우리인지 아닌지 저장
// heap에 데이터가 있는 동안 heap에 있는 데이터를 꺼내오고
// 꺼내온 데이터의 가중치가 intensity[현재 지점]보다 클 시 continue
// 꺼내온 데이터의 지점이 산봉우리일 시
// ansIntensity와 현재 지점의 intensity 비교
// 현재 intensity가 ansIntensity보다 작을 시
// ansIntensity = curIntensity, summit = 현재 지점
// 그렇지 않고, curIntensity가 ansIntensity와 같고 지점 번호가 summit보다 작을 시엔 summit = 현 지점 한 후 continue;

// 여기까지 진행했다면 현재 지점의 intensity가 이전보다 더 작은 값으로 갱신되었다.

// 자식 노드들을 순회
// 현재까지의 가중치와 자식 노드와의 가중치를 비교하여 더 큰 값을 구하고 intensity[자식 노드] 와 비교
// intensity[자식 노드] 보다 그 값이 작다면 intensity[자식 노드]를 위에서 구한 더 큰 값으로 갱신하고
// heap에 자식 노드와 가중치 넣어준다

// 탐색을 마친후 return summit, ansIntensity

#define MaxN 500001


bool isSummit[MaxN] = {false, };
int intensity[MaxN];

vector<vector<pair<int, int>>> graph(MaxN);

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    for (int i = 1; i <= n; i++)
        intensity[i] = 1e8;
    for (auto s : summits)
        isSummit[s] = true;
    for (auto p : paths)
    {
        graph[p[0]].push_back(make_pair(p[2], p[1]));
        graph[p[1]].push_back(make_pair(p[2], p[0]));
    }
    
    priority_queue<pair<int, int>> pq;
    for (auto g : gates)
    {
        intensity[g] = -1;
        pq.push({0, g});
    }
    
    int ansIntensity = 1e9;
    int summit = 1e9;
    
    while(pq.empty() == false)
    {
        auto [curMaxIntensity, curNode] = pq.top(); pq.pop(); // = int curMaxintensity, curNode; tie(curMaxIntensity, curNode) = pq.top(); pq.pop();
        if (curMaxIntensity > ansIntensity)
            continue;
        if (isSummit[curNode])
        {
            if (curMaxIntensity < ansIntensity)
            {
                ansIntensity = curMaxIntensity;
                summit = curNode;
            }
            else if (curMaxIntensity == ansIntensity && curNode < summit)
            {
                summit = curNode;
            }
            continue;
        }
        
        for (auto nextNode : graph[curNode])
        {
            if (intensity[nextNode.second] > max(curMaxIntensity, nextNode.first))
            {
                intensity[nextNode.second] = max(curMaxIntensity, nextNode.first);
                pq.push({intensity[nextNode.second], nextNode.second});
            }
        }
    }
    
    vector<int> answer = {summit, ansIntensity};
    return answer;
}