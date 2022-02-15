#include <iostream>
#include <algorithm> //min
#include <cstring> //memset

using namespace std;

int N;
int DP[61][61][61];
int HP[3] = { 0, };//SCV없으면 그냥 0

void Input()
{
    cin >> N;
	memset(DP, -1, sizeof(DP));
	for (int i = 0; i < N; i++) {
		cin >> HP[i];
	}
}

int Solution(int x, int y, int z) {
	//파괴된 SCV가 있을 경우
	if (x < 0)return Solution(0, y, z);
	if (y < 0)return Solution(x, 0, z);
	if (z < 0)return Solution(x, y, 0);
	
	//모든 SCV가 파괴된 경우
	if (x == 0 && y == 0 && z == 0)
		return 0;
	
	int& res = DP[x][y][z];

	//이미 구해둔 값이면
	if (res != -1)
		return res;

	res = 99999999;
	res = min(res, Solution(x - 9, y - 3, z - 1) + 1);
	res = min(res, Solution(x - 9, y - 1, z - 3) + 1);
	res = min(res, Solution(x - 3, y - 9, z - 1) + 1);
	res = min(res, Solution(x - 1, y - 9, z - 3) + 1);
	res = min(res, Solution(x - 3, y - 1, z - 9) + 1);
	res = min(res, Solution(x - 1, y - 3, z - 9) + 1);

	return res;
}

void Solve()
{
    Input();
    cout << Solution(HP[0], HP[1], HP[2]) << '\n';
}

int main() {
    
	Solve();
	
	return 0;
}