#include<iostream>
using namespace std;

int n, s;
int arr[22];
int cnt;

void func(int length, int total)
{
	if (length == n)
	{
		if (total == s)	// 각 수가 들어가는지 안들어가는지 모든 경우의 수(cur==n)를 구하는 것이므로
						// 합이 s면 return;
		{
			cnt++;
		}
		return;
	}
	func(length + 1, total);
	func(length + 1, total + arr[length]);
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> s;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	func(0, 0);

	if (s == 0) cnt--;	//s가 0일때는 공집합 일때를 고려(-1)
	cout << cnt;

	return 0;
}