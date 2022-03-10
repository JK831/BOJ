#include<iostream>

using namespace std;

long long dp[1500050];
int INF = 1000000;
long long N;

void Input()
{
    cin >> N;
}

void Solution()
{
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 0; i < 1500000; i++)
        dp[i + 2] = (dp[i + 1] + dp[i]) % INF;
    
    cout << dp[N % 1500000] << "\n";
}

void Solve()
{
    Input();
    Solution();
}
 
int main()
{
    Solve();
    
    return 0;
}