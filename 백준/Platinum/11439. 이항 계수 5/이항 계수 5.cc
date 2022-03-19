#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
 
int n, k, m;
 
bool nprime[4000001];
vector<int> pnum;
unordered_map<int, int> pcnt;
 
ll po(ll a, int b)
{
    if (!b)
        return 1;
 
    if (b == 1)
        return a;
    
    if (b & 1)
        return po(a, b - 1) * a % m;
    
    return po(a * a % m, b / 2);
}

void Input()
{
    cin >> n >> k >> m;
}

void Solution()
{
    nprime[1] = true;
 
    for (int i = 2; i <= n; ++i)
    {
        if (nprime[i])
            continue;
        
        pnum.push_back(i);
 
        for (int j = i + i; j <= n; j += i)
            nprime[j] = true;
    }
 
    for (int j = 0; j < pnum.size(); ++j)
        for (ll h = pnum[j]; h <= n; h *= pnum[j])
            pcnt[pnum[j]] += n / h - k / h - (n - k) / h;
 
    ll res = 1;
 
    for (auto it = pcnt.begin(); it != pcnt.end(); ++it)
    {
        res *= po(it->first, it->second);
        res %= m;
    }
 
    cout << res;
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
