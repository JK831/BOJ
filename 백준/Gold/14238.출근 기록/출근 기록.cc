#include <iostream>
#include <string>
using namespace std;

int worker[3];
bool DP[51][51][51][3][3] = { false, };
char res[51];
string S;

void Input()
{
    cin >> S;
}

bool Solution(int a, int b, int c, int pp, int p)
{
	if (a == worker[0] && b == worker[1] && c == worker[2])
		return true;

	if (DP[a][b][c][pp][p])
        return false;
    
	DP[a][b][c][pp][p] = true;

	if (a + 1 <= worker[0]) {
		res[a + b + c] = 'A';
		if (Solution(a + 1, b, c, p, 0))
			return true;
	}
	if (b + 1 <= worker[1]) {
		res[a + b + c] = 'B';
		if (p != 1 && Solution(a, b + 1, c, p, 1))
			return true;
	}
	if (c + 1 <= worker[2]) {
		res[a + b + c] = 'C';
		if (pp != 2 && p != 2 && Solution(a, b, c + 1, p, 2))
			return true;
	}
	return false;
}

void Solve()
{
    Input();
    
    for (int i = 0; i < S.size(); i++)
    {
		if (S[i] == 'A')
			worker[0]++;
		else if (S[i] == 'B')
			worker[1]++;
		else
			worker[2]++;
	}
    
	if (Solution(0, 0, 0, -1, -1))
		for (int i = 0; i < S.size(); i++)
			cout << res[i];
	else
		cout << -1;
    
	cout << '\n';
}

int main()
{
	Solve();
	
	return 0;
}