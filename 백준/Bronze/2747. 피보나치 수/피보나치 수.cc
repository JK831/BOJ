#include <iostream>
using namespace std;

int N, dp[50];
int main()
{
    dp[1] = 1;
	for (int i = 2; i <= 45; i++)
		dp[i] = dp[i - 1] + dp[i - 2];
    
    cin >> N;
    cout << dp[N];
    
    return 0;
}