#include <cstdio>
 
using namespace std;
 
long long DP[101];
int N;
 
int Max(int x, int y) {
    return x < y ? x : y;
}

void Input()
{
    scanf("%d", &N);
}

void Solution()
{
    DP[0] = 0;
    for (int i = 1; i <= 6; i++)
        DP[i] = i;
    
    for (int i = 7; i <= N; i++) {
        DP[i] = DP[i-1] + 1;
        for (int j = 3; j <= i; j++) {
            if (DP[i] < DP[i-j]*(j-1)) DP[i] = DP[i-j]*(j-1);
        }
    }
    printf("%lld\n", DP[N]);
}

void Solve()
{
    Input();
    Solution();
}
 
int main() {
    Solve();
}