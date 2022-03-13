#include <iostream>
using namespace std;

int N, K;

int factorial(int t)
{
    int ans = 1;
    
    for (int i = t; i > 0; i--)
        ans *= i;
    
    return ans;
}

void Input()
{
    cin >> N >> K;
}

void Solution()
{
    int result = factorial(N) / (factorial(K) * factorial(N - K));
    cout << result;
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
