#include<iostream>
 
#define endl "\n"
#define MAX 1001
using namespace std;
 
int N, M;
int MAP[MAX][MAX];
int Candy[MAX][MAX];
 
int Bigger(int A, int B) { if (A > B) return A; return B; }
 
void Input()
{
    cin >> N >> M; 
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            cin >> MAP[i][j];
        }
    }
}
 
void Solution()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            int Result = Bigger(Bigger(Candy[i - 1][j], Candy[i][j - 1]), Candy[i - 1][j - 1]);
            Candy[i][j] = Result + MAP[i][j];
        }
    }
 
    cout << Candy[N][M] << endl;
}
 
void Solve()
{
    Input();
    Solution();
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
 
    return 0;
}