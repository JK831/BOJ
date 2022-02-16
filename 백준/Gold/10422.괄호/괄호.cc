#include <cstdio>
#define MOD 1000000007
typedef long long int ll;
int t, l;
int dp[2501] = { 1, 1 };
int main() {
    scanf("%d", &t);
    for (int i = 2; i <= 2500; i++) {
        ll s = 0;
        for (int j = 1; j <= i / 2; j++) s += (ll)dp[i - j] * dp[j - 1] % MOD;
        dp[i] = (2 * s + (i % 2 ? (ll)dp[i / 2] * dp[i / 2] : 0) ) % MOD;
    }
    while (t--) {
        scanf("%d", &l);
        printf("%d\n", l % 2 ? 0 : dp[l/2]);
    }
}