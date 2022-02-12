#include <iostream>

#define MAX 1500010
#define Bigger(a, b) a > b ? a : b
#define endl '\n'

using namespace std;

int N, Answer;
int DP[MAX];
int Arr[MAX][2];

void Input()
{
    cin >> N;
    for (int i = 1; i <= N; i ++)
    {
        cin >> Arr[i][0] >> Arr[i][1];
    }
}

void Solution()
{
    int Current_Max = 0;
    for (int i = 1; i <= N + 1; i++)
    {
        Current_Max = Bigger(Current_Max, DP[i]);
        if (i + Arr[i][0] > N + 1) continue;
        
        DP[i + Arr[i][0]] = Bigger(Current_Max + Arr[i][1], DP[i + Arr[i][0]]);
    }
    Answer = Current_Max;
}

void Solve()
{
    Input();
    Solution();
    cout << Answer << endl;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    Solve();
 
    return 0;
}