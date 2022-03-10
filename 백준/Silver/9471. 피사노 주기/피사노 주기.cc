#include <iostream>
 
using namespace std;
 
int T, m, m1, m2, cnt;
int N;

void Input()
{
    cin >> N;
}

void Solution()
{
    while (N--)
    {
        cin >> T >> m;
 
        m1 = 0;
        m2 = 1;
        cnt = 0;
 
        while(1)
        {
            if(m1 == 0 && m2 == 1 && cnt != 0)
                break;

            int temp = m1;
            m1 = m2;
            m2 = (temp + m1) % m;
            cnt++;
        }

        cout << T << ' ' << cnt << endl;
    }
}

void Solve()
{
    Input();
    Solution();
}
 
int main()
{
    Solve();
    
    return 0;
}