#include <string>
#include <vector>

using namespace std;

long long answer = 0;

// Key point: 트리를 만들어 DFS 순회 => leaf 노드부터 차례로 0을 만들고
// 0을 만들기 위해 뺀 값을 부모 노드의 가중치와 answer에 더해준다 (그냥 나의 가중치를 부모 노드에 더하면 된다)


// now : 현재 방문 중인 노드,  parent : 부모 노드 (바로 이전에 방문한 노드)
void DFS(vector<vector<int>>& graph, vector<long long>& sum, int now, int parent) {  
    for (int i = 0; i < graph[now].size(); ++i)
        if (graph[now][i] != parent) // 트리 이므로 연결 된 노드에서 부모 노드가 아닌 것만 거르는 식으로 방문 하면 된다.
            DFS(graph, sum, graph[now][i], now); // leaf 노드에 도달할 때까지
    
    // DFS 끝내고 돌아온 이후
    sum[parent] += sum[now]; // 현재 방문 중인 노드값을 부모 노드에 더한다 (현재 방문 중인 노드는 0 이 되었다고 가정)
    answer += abs(sum[now]); // 1씩 더하거나 뺀 횟수를 answer에 더해준다 (위 sum[now]의 절대값 = 1씩 더하거나 뺀 횟수) 
}

long long solution(vector<int> a, vector<vector<int>> edges) {

    vector<long long> sum(a.size()); // long long 버전의 a, 가중치를 Leaf 노드부터 변화시켜가며 올라갈 것. 
    for (int i = 0; i < a.size(); ++i)
        sum[i] = a[i];

    // 그래프 (트리) 생성
    vector<vector<int>> graph(a.size());
    for (int i = 0; i < edges.size(); ++i)
    {
        graph[edges[i][0]].push_back(edges[i][1]);
        graph[edges[i][1]].push_back(edges[i][0]);
    }
    
    DFS(graph, sum, 0, 0); // 출발점(루트)은 0 으로 선정. (루트의 부모는 자기 자신)
    
    if (sum[0] == 0) return answer; // 모든 정점을 0 으로 만드는 게 가능한 트리라면 sum 의 모든 원소가 0 이 되어 있는 상태여야 한다 => 루트 정점만 체크해보면 됨.
    else return - 1; // 루트 가중치가 0 이 아니라면 이 트리는 모든 정점을 0 으로 만드는게 불가능한 트리
}