#include <iostream>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b)
{
	return b ? gcd(b, a % b) : a;
}

ll dp[22][22];
int n, m;

void Input()
{
    cin >> n >> m;
}

void Solution()
{
    dp[1][1] = 1;
	for (int i = 1; i <= n; i++)
    {
		for (int j = 1; j <= i; j++)
        {
			if (i == 1 && j == 1) continue;
			dp[i][j] = dp[i - 1][j - 1] + (i - 1) * dp[i - 1][j]; //새로운 사이클에 끼는 경우 + 기존 사이클에 끼는 경우
		}
	}

	for (int i = 1; i <= n; i++) dp[n][i] += dp[n][i - 1];
}

void Solve()
{
    Input();
    Solution();
    
    ll g = gcd(dp[n][m], dp[n][n]);
	cout << dp[n][m] / g << "/" << dp[n][n] / g;
}

int main()
{
	
	Solve();
    
    return 0;
}
