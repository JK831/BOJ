#include <bits/stdc++.h>
using namespace std;

int N, K;
bool dp[31][31][31][450] = {false,};
char ans[31];

void Input()
{
    cin >> N >> K;
}

bool Solution(int n, int a, int b, int p){
    if( n == N )
    {
        if( p == K )
            return true;
        return false;
    }
    
    if( dp[n][a][b][p] )
    {
        return false;
    }
    
    dp[n][a][b][p] = true;
    
    ans[n] = 'A';
    if (Solution(n+1, a+1, b, p))
        return true;
    
    ans[n] = 'B';
    if (Solution(n+1, a, b+1, p+a))
        return true;
    
    ans[n] = 'C';
    if (Solution(n+1, a, b, p+a+b))
        return true;
    
    return false;
}

void Solve()
{
    Input();
    
    if(Solution(0, 0, 0, 0))
    {
        cout << ans;
        return;
    }
    
    cout << -1;
}
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    Solve();
    
    return 0;
}