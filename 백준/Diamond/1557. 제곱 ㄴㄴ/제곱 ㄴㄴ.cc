#include <cstdio>

long long int K;
long long int low, high;
long long int mobius[1000001] = {0,};

/*
 * GOAL: Set Mobius function
 */
void buildMobius()
{
    mobius[1] = 1;
    for(int i = 1; i <= 1000000; i++)
    {
        if(mobius[i] != 0)
            for(int j = 2 * i; j <=1000000; j += i)
            {
                mobius[j] -= mobius[i];
            }
    }
}

long long int squareFree(long long int n)
{
    long long int k = 0;
    for(long long int i = 1; i * i <= n; ++i)
        k += (mobius[i] * (n / (i * i)));
    return k;
}

int main()
{
    low = 0;
    high = 2e9;
    scanf("%lld", &K);
    buildMobius();
    while(low + 1 < high)
    {
        long long int mid = (low + high) / 2;
        if(squareFree(mid) < K)
            low = mid;
        else high = mid;
    }

    printf("%lld", high);

    return 0;
}