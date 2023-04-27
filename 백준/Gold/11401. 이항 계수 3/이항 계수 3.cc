#include<iostream>
#include<cmath>
using namespace std;

long long N, K, A, B, half;
long long mod = 1000000007;

long long square(int x)
{
	if (x == 0) return 1;

	if (x % 2 == 1)
        return B * square(x - 1) % mod;
	else
	{
		half = square(x / 2);
		return half * half % mod;
	}
}

void Input()
{
    cin >> N >> K;
}

void Solution()
{
    A = 1;
	// A = N*(N-1)* .... *(N-K+1)
	for (int i = N; i >= N - K + 1; i--)
        A = (A * i) % mod;

	// B = K!
	B = 1;
	for (int i = 1; i <= K; i++) B = (B * i) % mod;

	// B = (K!)^(p-2)
	B = square(mod - 2);

	cout << A * B % mod;
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