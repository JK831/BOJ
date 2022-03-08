#include <iostream>
using namespace std;

long long N, B;
int arr[5][5];
int result[5][5];
int temp[5][5];

void MatrixMul(int v1[5][5], int v2[5][5])
{
	

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
        {
			temp[i][j] = 0;
			for (int k = 0; k < N; k++)
				temp[i][j] += (v1[i][k] * v2[k][j]);
			temp[i][j] %= 1000;
		}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) 
			v1[i][j] = temp[i][j];		
}

void Input()
{
    cin >> N >> B;
}

void Solution()
{
    for (int i = 0; i < N; i++)
    {
		for (int j = 0; j < N; j++)
        {
			cin >> arr[i][j];
		}
		result[i][i] = 1;
	}
	while (B)
    {
		if (B % 2 == 1)
        {
			MatrixMul(result, arr);
		}
		MatrixMul(arr, arr);
		B /= 2;
	}


	for (int i = 0; i < N; i++)
    {
		for (int j = 0; j < N; j++)
			cout << result[i][j] << ' ';
		cout << endl;
	}
}

void Solve()
{
    Input();
    Solution();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	Solve();

	return 0;
}