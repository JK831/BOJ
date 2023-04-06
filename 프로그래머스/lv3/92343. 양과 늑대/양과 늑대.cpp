#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// Key point: 노드들의 존재와 노드들의 조합을 비트마스크를 활용한 상태로 나타낸다. 일반적인 DFS, 백트래킹으로 접근 시 시간 초과
// 정점에 방문해서 정점에 도달했을 때 여태까지 방문한 정점의 수와 발견된 늑대의 수를 비교하여
// 방문한 정점이거나 (늑대의 수 * 2 >= 방문한 정점의 수)일 시 탐색 종료
// 각 상태에서 현재 상태의 양의 수가 저장된 최대 양의 수보다 많을 경우 최대 양의 수 갱신
// 그 후 다음 상태 탐색 (자식 노드가 있을 시 자식노드가 다음 탐색할 상태가 된다).

// 왼쪽 자식, 오른쪽 자식, 양/늑대 값
int l[20], r[20], val[20];
int n;
int ans = 1;
bool visited[1 << 17]; // vis[x] : 상태 x를 방문했는가?

// 상태에 대한 dfs 함수
void DFS(int state)
{
    if(visited[state]) return;
    visited[state] = true;
    
    // wolf : 늑대의 수, num : 방문한 정점의 수
    int wolf = 0, num = 0;
    for(int i = 0; i < n; i++)
    {
        if(state & (1 << i))
        {
            ++num;
            wolf += val[i];
        }
    }
    
    // 만약 늑대가 절반 이상일 경우 방문할 수 없는 상태이니 종료
    if(wolf * 2 >= num) return;
    // 현재 state의 양의 수가 ans보다 클 경우 ans를 갱신
    ans = max(ans, num - wolf);
    // 다음 상태 탐색
    for(int i = 0; i < n; i++)
    {
        // i번째 비트가 꺼져있는 경우 해당 정점이 없으니 넘어감
        if((state & (1 << i)) == false) continue;
        // 현재 보고 있는 i번째 정점의 left가 있다면
        if(l[i] != -1)
            DFS(state | (1 << l[i]));
        // 현재 보고 있는 i번째 정점의 right가 있다면 
        if(r[i] != -1)
            DFS(state | (1 << r[i]));
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    n = info.size();
    
    fill(l,l + n, -1);
    fill(r,r + n, -1);
    
    for(int i = 0; i < n; i++) val[i] = info[i];
    
    for(int i = 0; i < n - 1; i++)
    {
        int a = edges[i][0]; // 부모
        int b = edges[i][1]; // 자식
        if(l[a] == -1) l[a] = b;
        else r[a] = b;
    }
    
    DFS(1); // 0번 노드만 포함된 상태에서 dfs 시작
    return ans;
}