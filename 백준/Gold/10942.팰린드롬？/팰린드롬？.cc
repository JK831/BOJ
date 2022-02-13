#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int arr[2001];
bool palindrom[2001][2001] = { false, };
int N, M, s, e;

void Input()
{
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
	}
}

void Solution()
{
    for (int i = 1; i <= N - 1; i++) {
		if (arr[i] == arr[i + 1])
			palindrom[i][i + 1] = true;
	}

	for (int i = 1; i <= N; i++) {
		palindrom[i][i] = true;
	}

	for (int i = N - 1; i >= 1; i--) {
		for (int j = i + 2; j <= N; j++) {
			if (arr[i] == arr[j] && palindrom[i + 1][j - 1] == true) {
				palindrom[i][j] = true;
			}
		}
	}

	cin >> M;

	for (int i = 0; i < M; i++) {
		cin >> s >> e;
		cout << palindrom[s][e] << '\n';
	}
}

void Solve()
{
    Input();
    Solution();
}

int main()
{
	cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);

	Solve();

	return 0;
}