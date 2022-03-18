#include <stdio.h>

long long N, K;
int M;
int result = 1;


int nCk(int N, int K, int M)
{
    int A = 1, B = 1;
    for (int i = N; i > N-K; i--)
        A = A*i %M;
	
    for (int i = K; i >= 2; i--)
        B = B*i %M;

    N = 1, K = M-2; // 모듈러 연산의 성질을 적용시키기 위해 페르마의 소정리를 이용하여 분모값 B를 분자로 올려준다
                    // a^(p - 1)(mod k) = a^-1(mod k) => (1 / B)(mod k) = B^(k - 2)(mod k)
    while (K)
    {
        if (K & 1) N = N*B %M;
        K >>= 1;
        B = B*B %M;
    }
    return A*N %M;
}

void Input()
{
    scanf("%lld %lld %d", &N, &K, &M);
}

void Solution()
{
    while (N || K)
    {
        result = result*nCk(N%M, K%M, M) %M;
        N /= M, K /= M;
    }
    printf("%d", result);
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