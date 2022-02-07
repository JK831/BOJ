#define MAX 987654321
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int num, sx, sy;
char arr[50][50];
int check[50][50][4];

struct info {
	int x, y, dir;
};
info tmp;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

void Input()
{
    cin >> num;
}

void Solution()
{
    queue<info> q;
	for (int i = 0; i < num; i++)
		for (int j = 0; j < num; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == '#') {
				sx = j;
				sy = i;
			}
			for (int k = 0; k < 4; k++)
				check[i][j][k] = MAX;
		}
	tmp.x = sx;
	tmp.y = sy;
	for (int k = 0; k < 4; k++) {
		int nx = sx + dx[k];
		int ny = sy + dy[k];
		if (nx >= 0 && ny >= 0 && nx < num && ny < num && arr[ny][nx] != '*') {
			tmp.dir = k;
			q.push(tmp);
			check[sy][sx][k] = 0;
		}
	}
	arr[sy][sx] = '*';
	int result = MAX;
	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		int cd = q.front().dir;
		q.pop();
		if (arr[cy][cx] == '#')
			result = min(result, check[cy][cx][cd]);
		if (result <= check[cy][cx][cd]) continue;
		int nx = cx + dx[cd];
		int ny = cy + dy[cd];
		if (nx >= 0 && ny >= 0 && nx < num && ny < num && arr[ny][nx] != '*') {
			if (arr[ny][nx] == '!') {
				if (check[ny][nx][cd] > check[cy][cx][cd]) {
					check[ny][nx][cd] = check[cy][cx][cd];
					tmp.x = nx;
					tmp.y = ny;
					tmp.dir = cd;
					q.push(tmp);
				}
				int nd;
				nd = (cd + 1) % 4;
				if (nx >= 0 && ny >= 0 && nx < num && ny < num && arr[ny][nx] != '*' && check[ny][nx][nd]>check[cy][cx][cd] + 1) {		//거울 사용
					check[ny][nx][nd] = check[cy][cx][cd] + 1;
					tmp.x = nx;
					tmp.y = ny;
					tmp.dir = nd;
					q.push(tmp);
				}
				nd = (cd + 3) % 4;
				if (nx >= 0 && ny >= 0 && nx < num && ny < num && arr[ny][nx] != '*' && check[ny][nx][nd]>check[cy][cx][cd] + 1) {		//거울 사용
					check[ny][nx][nd] = check[cy][cx][cd] + 1;
					tmp.x = nx;
					tmp.y = ny;
					tmp.dir = nd;
					q.push(tmp);
				}
			}
			else if (arr[ny][nx] == '.' || arr[ny][nx] == '#') {
				if (check[ny][nx][cd] > check[cy][cx][cd]) {
					check[ny][nx][cd] = check[cy][cx][cd];
					tmp.x = nx;
					tmp.y = ny;
					tmp.dir = cd;
					q.push(tmp);
				}
			}
		}
	}
	cout << result;
}

void Solve()
{
    Input();
    Solution();
}

int main() {
    
    Solve();
	return 0;
}