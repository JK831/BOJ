#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 10001
using namespace std;

int n, m, a, t[MAX];
int indegree[MAX];
int dp[MAX];
vector<int> graph[MAX];
queue<int> executableTaskQ;

void Input()
{
    cin >> n;
	for (int i = 1; i <= n; i++)
    {
		cin >> t[i] >> m;
		while (m--)
        {
			cin >> a;
			graph[a].push_back(i);
			indegree[i]++;
		}
	}
}

void Solution()
{
    for (int i = 1; i <= n; i++)
    {
		if (indegree[i] == 0)
        {
			dp[i] = t[i];
			executableTaskQ.push(i);
		}
	}

	int ans = 0;
    
	while (!executableTaskQ.empty())
    {
		int x = executableTaskQ.front();
		executableTaskQ.pop();
		for (int nxt : graph[x])
        {
			if (--indegree[nxt] == 0) // 더 수행해야 할 선행 작업이 없을 시 수행 가능한 상태이므로 큐에 넣어준다
                executableTaskQ.push(nxt);
			dp[nxt] = max(dp[nxt], dp[x] + t[nxt]); // dp[x]는 선행작업에 걸리는 시간이고 가장 오래 걸리는 선행작업을
            //마친 후에 nxt 작업 가능하므로 현재 보고 있는 선행 작업 + nxt 수행시간과 이전에 저장된 수행시간 중 큰 것 저장 
		}
        
		ans = max(ans, dp[x]);
	}
	cout << ans;
}

void Solve()
{
    Input();
    Solution();
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	Solve();
}