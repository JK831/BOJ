#include <iostream>
using namespace std;

int N;
long long dp[91] = {0,};

void Input()
{
    cin >> N;
}

void Solution()
{
    dp[1] = 1;
    
    for(int i = 2; i <= N; i++)
        dp[i] = dp[i-1] + dp[i-2];

    cout << dp[N];
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