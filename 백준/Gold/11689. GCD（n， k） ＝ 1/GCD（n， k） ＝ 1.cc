#include <stdio.h>

long long n;
long long euler;

void Input()
{
    scanf("%lld", &n);
}

void Solution()
{
    euler = n;
    
    for (long long p = 2; p * p <= n; p++)
    {
        if (n % p == 0)
            euler = euler / p * (p - 1);
        while (n % p == 0)
            n = n / p;
    }
    
    if (n != 1)
		euler = euler / n * (n - 1);
    
    printf("%lld", euler);
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