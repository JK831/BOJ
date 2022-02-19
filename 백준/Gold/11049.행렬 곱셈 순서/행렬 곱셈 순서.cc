#include<iostream>

using namespace std;

#define INF 1000000000

int N, r, c;
int sum[501], matrix[501][2], dp[501][501];

void Input()
{
    cin >> N;

	for (int i = 1; i <= N; i++)
	{
		cin >> r >> c;
		matrix[i][0] = r;
		matrix[i][1] = c;
	}
}

void Solution()
{
    for (int i = 1; i < N; i++)
	{
		for (int j = 1; i + j <= N; j++)
		{
			dp[j][i + j] = INF;
			for (int k = j; k <= i + j; k++)
			{
				dp[j][i + j] = min(dp[j][i + j], dp[j][k] + dp[k + 1][i + j] + matrix[j][0] * matrix[k][1] * matrix[i+j][1]);
			}
		}

	}

	cout << dp[1][N];
}

void Solve()
{
    Input();
    Solution();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

	Solve();
    
    return 0;
}