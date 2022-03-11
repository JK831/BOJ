#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<long long>> matrix;
const long long mod = 1000000007;

long long N;

matrix operator * (matrix& a, matrix& b)
{
	matrix c(2, vector<long long>(2));

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++){
			for (int k = 0; k < 2; k++)
				c[i][j] += a[i][k] * b[k][j];

			c[i][j] %= mod;
		}
	return c;	
}

void Input()
{
    cin >> N;   
}

void Solution()
{
    matrix ans = {{1,0}, {0,1}};
	matrix a = {{1,1}, {1,0}};

	while (N > 0)
	{
		if (N % 2 == 1)
			ans = ans * a;
		a = a * a;
		N /= 2;
	}
	
	cout << ans[0][1] << '\n';
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