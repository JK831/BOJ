#include <cstdio>
#include <cstring>
 
using namespace std;
 
long long d[101][101];
int n, m, p;

long long cal(int len, int pick)
{
    int sur = n - pick;

    if (len == p) {
 
        if (sur == 0) return 1;
 
        else return 0;
    }
 
    auto &chk = d[len][pick];
    if (chk != -1) return chk;
 
    chk = 0;
 
    if (sur > 0) chk += cal(len + 1, pick + 1) * sur;
 
    if (pick > m) chk += cal(len + 1, pick)*(pick - m);
 
    chk %= 1000000007;
 
    return chk;
}

void Input()
{
    scanf("%d %d %d", &n, &m, &p);
}

void Solution()
{
    memset(d, -1, sizeof(d));
    printf("%lld\n", cal(0, 0));
}

void Solve()
{
    Input();
    Solution();
}
 
int main ()
{
    Solve();
    
    return 0;
}