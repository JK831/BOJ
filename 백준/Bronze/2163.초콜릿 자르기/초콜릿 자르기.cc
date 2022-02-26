#include<iostream>
 
#define endl "\n"
#define MAX 300
using namespace std;
 
int N, M;
 
void Input()
{
    cin >> N >> M;
}
 
void Solution()
{
    cout << N * M - 1 << endl;
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