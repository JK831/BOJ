#include<iostream>
#include<queue>
using namespace std;

int N, K;
queue<int> q;

void Input()
{
    cin >> N >> K;
	for (int i = 1; i <= N; i++) q.push(i);
}

void Solution()
{
    cout << "<";

	while (q.size() != 0)
	{
		for (int i = 1; i < K; i++)
		{
			q.push(q.front()); // i번째 카드를 맨뒤로
			q.pop();
		}
		cout << q.front();
		if (q.size() != 1) cout << ", ";
		q.pop();
	}
	cout << ">";
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