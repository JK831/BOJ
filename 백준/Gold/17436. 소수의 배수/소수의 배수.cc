#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n, m;
vector<ll> v;
ll res = 0;

void cal(int idx, int h, int h2=0, ll mul=1)
{
    if (h2 >= h)
    {
        ll p = h % 2 == 0 ? -1 : 1;
        res += p * (m / mul);
        return;
    }
 
    for (int i = idx; i < n; i++)
        cal(i + 1, h, h2 + 1, mul * v[i]);
}

void Input()
{
    cin >> n >> m;
    v.resize(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
}

void Solution()
{
    for (int i = 0; i < n; i++)
        cal(0, i+1);
    
    cout << res << "\n";
}

void Solve()
{
    Input();
    Solution();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Solve();    
}