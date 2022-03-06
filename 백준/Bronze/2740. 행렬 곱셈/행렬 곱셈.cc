#include <iostream>

using namespace std;

int N, M, K;

int matrix1[101][101];
int matrix2[101][101];
int res[101][101];

void Input()
{
    cin >> N >> M;
    
	for (int i = 0; i < N; i++)
    {
		for (int j = 0; j < M; j++)
			cin >> matrix1[i][j];
	}
	cin >> M >> K;
	for (int i = 0; i < M; i++)
    {
		for (int j = 0; j < K; j++)
        {
			cin >> matrix2[i][j];
		}
	}
}

void Solution()
{
    for (int i = 0; i < N; i++)
    {
		for (int j = 0; j < K; j++)
        {
			for (int k = 0; k < M; k++)
            {
				res[i][j] += matrix1[i][k] * matrix2[k][j];
			}
			cout << res[i][j] << " ";
		}
		cout << '\n';
	}
}

void Solve()
{
    Input();
    Solution();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
	Solve();
    
    return 0;	
}