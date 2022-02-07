#include <iostream>
#include <algorithm>
using namespace std;

int row, col, sum = 0, v;
int r[1000], c[1000];

void Input()
{
    cin >> row >> col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++) {
			cin >> v;
			if (i == 0 || i == row - 1 || j==0 ||j==col-1) {
				if ((i == 0 && j == 0) || (i == 0 && j == col - 1) || (i == row - 1 && j == 0) || (i == row - 1 && j == col - 1)) {
					r[i] += v;
					c[j] += v;
					sum += v;
				}
				else {
					r[i] += (2 * v);
					c[j] += (2 * v);
					sum += (2 * v);
				}
			}
			else {
				r[i] += (4 * v);
				c[j] += (4 * v);
				sum += (4 * v);
			}
		}
}

void Solution()
{
    int temp = -9876543210;
	for (int i = 1; i < row - 1; i++) {
		temp = max(temp, sum - r[i]/2 + r[0]);
		temp = max(temp, sum - r[i]/2 + r[row - 1]);
	}
	for (int i = 1; i < col - 1; i++) {
		temp = max(temp, sum - c[i]/2 + c[0]);
		temp = max(temp, sum - c[i]/2 + c[col-1]);
	}
	sum = max(sum, temp);
    cout << sum;
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