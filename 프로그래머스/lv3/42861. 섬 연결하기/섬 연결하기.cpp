#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Key point: Kruskal 알고리듬 사용
// 비용이 작은 순으로 costs를 정렬
// 정렬된 costs를 사용하여 다리들을 연결, 연결한 다리들은 disjoint set에 넣는다.
// 이후 union-find를 사용하여 root 노드와 현재 노드의 root를 비교하여 사이클 생기는지 확인.

vector<int> parent(101);   // node의 parent를 저장하는 배열
 
int GetParent(int node)
{
    if(parent[node] == node) return node;
    return parent[node] = GetParent(parent[node]);
}
 
bool Cmp(const vector<int>& a, const vector<int>& b)
{
    return a[2] < b[2];
}
 
int solution(int n, vector<vector<int>> costs)
{
    int answer = 0;
 
    for (int i = 0; i < n; ++i)
        parent[i] = i;
    
    sort(costs.begin(), costs.end(), Cmp);  // 비용을 오름차순 정렬
 
    for (int i = 0; i < costs.size(); ++i)
    {
        int start = GetParent(costs[i][0]);
        int end = GetParent(costs[i][1]);
        int cost = costs[i][2];
 
        if (start != end) // cycle이 만들어지지 않을 경우 다리를 추가
        {
            answer += cost;
            parent[end] = start;
        }
    }
 
    return answer;
}
