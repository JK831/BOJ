#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    
    vector<vector<int>> graph(n + 1); // 인접 리스트로 나타낸 그래프
    queue<int> q; // 각 노드에서 다음 노드를 탐색할 때 bfs 사용, 그 때 사용할 queue 
    vector<int> distance(n + 1, -1); // 1번 노드에서 각 인덱스에 해당하는 노드들 사이의 거리
    
    for (int i = 0; i < edge.size(); i++)
    {
        int from = edge[i][0];
        int to = edge[i][1];
        
        graph[from].push_back(to); // from에서 이어진 노드들을 모두 from인덱스의 벡터에 넣어준다.
        graph[to].push_back(from); // to도 from과 이어준다.
    }
    
    distance[1] = 0; // 1번 노드의 거리 = 0;
    
    q.push(1);
    
    while(q.empty() == false) // bfs 탐색 시작
    {
        int current = q.front();
        q.pop();
        
        for (int next : graph[current])
        {
            if (distance[next] == -1)
            {   
                distance[next] = distance[current] + 1;
                q.push(next);
            }
        }
    }
    
    int mostFar = *max_element(distance.begin(), distance.end()); // distance의 값들 중 가장 큰 값 찾아낸다.
    
    for (int i = 0; i < distance.size(); i++)
    {
        if (distance[i] == mostFar) // 가장 큰 값과 현재 distance 배열의 요소가 일치한다면 answer++
            answer++;
    }
    
    return answer;
}