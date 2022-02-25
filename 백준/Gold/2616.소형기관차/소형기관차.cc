#include<bits/stdc++.h>

using namespace std;

int n, k;
vector<int> v, sum;
int dp[4][50001];

void Input()
{
    cin >> n;
    v.resize(n + 1);
    sum.resize(n + 1);
    
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i];
        sum[i] += v[i] + sum[i - 1];
    }
    cin >> k;
 
}

void Solution()
{
    for (int i = 1; i <= 3; i++)
    {
        for (int j = i * k; j <= n; j++)
            dp[i][j] = max(dp[i][j - 1], dp[i - 1][j - k] + (sum[j] - sum[j - k]));
    }
    cout << dp[3][n] << "\n";
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
    cout.tie(0);

    Solve();
    
    return 0;
}