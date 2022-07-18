#include <vector>
#define MAX 210
#define INF 2e9

using namespace std;

int Min(int A, int B) { if (A < B) return A; return B; }

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, int m, vector<vector<int>> edge_list, int k, vector<int> gps_log) {
    vector<int> Node[MAX];
    vector<vector<int>> DP(k, vector<int>(n + 1, INF));
    for (int i = 0; i < edge_list.size(); i++)
    {
        int N1 = edge_list[i][0];
        int N2 = edge_list[i][1];
        Node[N1].push_back(N2);
        Node[N2].push_back(N1);
    }
    
    // DP[A][B] = C : 경로의 A번 지점이 B가 되었을 때, 수정해야 하는 횟수
    // 초기값 = DP[0][gps_log[0]] = 0
    DP[0][gps_log[0]] = 0;
    
    for (int i = 1; i < k; i++)
    {
        for (int cur = 1; cur <= n; cur++)
        {
            if (DP[i - 1][cur] == INF) continue;
            for (int j = 0; j < Node[cur].size(); j++)
            {
                int Next = Node[cur][j];
                int alpha = 0;
                
                if (Next != gps_log[i]) alpha++;
                
                DP[i][Next] = Min(DP[i][Next], DP[i - 1][cur] + alpha);
            }
        }
    }
    if (DP[k - 1][gps_log[k - 1]] != INF) return DP[k - 1][gps_log[k - 1]];
    
    return -1;
}