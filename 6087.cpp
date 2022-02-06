#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 100;
const int INF = 987654321;

typedef struct
{
	int y, x;
}Dir;

Dir moveDir[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; // E S W N

int W, H;
int cnt;
bool flag;
vector<pair<int, int>> v;
string graph[MAX];
int dist[MAX][MAX][4];

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> H >> W;

	for (int i = 0; i < W; i++)
	{
		cin >> graph[i];

		for (int j = 0; j < H; j++)
		{
			if (graph[i][j] == 'C')
			{
				v.push_back({ i, j });
			}
		}
	}

	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				dist[i][j][k] = INF;
			}
		}
	}

	int y = v[0].first;
	int x = v[0].second;

	queue<pair<pair<int, int>, int>> q;
	
	for (int k = 0; k < 4; k++)
	{
		q.push({ {y, x}, k });

		dist[y][x][k] = 0;
	}

	for (int k = 0; k < 4; k++)
	{
		int len = 1;

		while (1)
		{
			int nextY = y + moveDir[k].y * len;
			int nextX = x + moveDir[k].x * len;

			if (nextY < 0 || nextY >= W || nextX < 0 || nextX >= H)
			{
				break;
			}

			if (graph[nextY][nextX] == '*')
			{
				break;
			}

			q.push({ {nextY, nextX}, k });

			dist[nextY][nextX][k] = 0;

			len++;
		}
	}

	int cnt = 1;

	while (!q.empty())
	{
		int qSize = q.size();

		for (int i = 0; i < qSize; i++)
		{
			int y = q.front().first.first;
			int x = q.front().first.second;
			int dir = q.front().second;
			q.pop();

			for (int k = 0; k < 4; k++)
			{
				if (k == dir)
				{
					continue;
				}
					
				int len = 0;

				while (1)
				{
					int nextY = y + moveDir[k].y * len;
					int nextX = x + moveDir[k].x * len;

					if (nextY < 0 || nextY >= W || nextX < 0 || nextX >= H)
					{
						break;
					}

					if (graph[nextY][nextX] == '*' || dist[nextY][nextX][k] < INF)
					{
						break;
					}

					q.push({ {nextY, nextX}, k });

					dist[nextY][nextX][k] = cnt;

					len++;
				}
			}
		}

		cnt++;
	}

	int result = INF;
	y = v[1].first;
	x = v[1].second;
	
	for (int k = 0; k < 4; k++)
	{
		result = min(result, dist[y][x][k]);
	}

	cout << result << "\n";

	return 0;
}
