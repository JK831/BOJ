#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int N_MAX = 1000;

int N, M;

vector<int> dp(N_MAX, INT_MAX);
vector<int> names(N_MAX, 0);

void Input()
{
    cin >> N >> M;
	for(int i = 0; i < N; i++)
		cin >> names[i];
}

int Solution(int idx)
{
	if(dp[idx] < INT_MAX)
		return dp[idx];

	int remain = M - names[idx];

	for(int i = idx + 1; i <= N && remain >= 0; i++)
    {
		if(i == N)
        {
			dp[idx] = 0;
			break;
		}
		dp[idx] = min(dp[idx], remain * remain + Solution(i));
		remain -= names[i] + 1;
	}

	return dp[idx];
}

void Solve()
{
    Input();
    
    dp[N - 1] = 0;

	cout << Solution(0) << '\n';
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Solve();

	return 0;
}