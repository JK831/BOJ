#include <iostream>

#define endl '\n'
#define min(a, b) a > b ? b : a
using namespace std;

int N;
int dp[10001] = {0,}, A[10001] = {0,};

void Input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        dp[i] = 999999;
    }
}

void Solution()
{
    dp[0] = 0;
    
    for (int i = 0; i < N; i++)
    {
        if (A[i] != 0)
        {
            for (int j = 1; j <= A[i]; j++)
            {
                if (i + j >= N)
                    dp[i + j] = dp[i] + 1;
                else
                    dp[i + j] = min(dp[i + j], dp[i] + 1);
            }
        }
    }
    if (dp[N - 1] > 10001)
        cout << -1 << endl;
    else
        cout << dp[N - 1] << endl;
}

void Solve()
{
    Input();
    Solution();
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    Solve();
    return 0;
}