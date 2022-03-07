#include <iostream>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int N;
queue<int> q;

void Input()
{
    cin >> N;
}

void Solution()
{
    for (int i = 1; i <= N; ++i)
    {
		q.push(i);
	}
 
	while (q.size() > 1)
    {
		q.pop();
		q.push(q.front());
		q.pop();
	}
 
	cout << q.front() << endl;
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