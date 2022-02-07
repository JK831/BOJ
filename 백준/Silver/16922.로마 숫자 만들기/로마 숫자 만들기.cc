#include<iostream>

using namespace std;
 
int N, Answer;
int Roma[] = { 1, 5, 10, 50 };
bool Visit[1000 + 1];
 
void Input()
{
    cin >> N;
}
 
void DFS(int Cnt, int D, int Total)
{
    if (Cnt == N)
    {
        if (Visit[Total] == false)
        {
            Visit[Total] = true;
            Answer++;
        }
        return;
    }
 
    for (int i = D; i < 4; i++)
    {
        DFS(Cnt + 1, i, Total + Roma[i]);
    }
}
 
 
void Solution()
{
    DFS(0, 0, 0);
    cout << Answer << endl;
}
 
void Solve()
{
    Input();
    Solution();
}
 
int main(void)
{
    Solve();
 
    return 0;
}