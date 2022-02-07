#include<iostream>
#include<queue>

using namespace std;

int T;
priority_queue<int> Max; //작은것들의 Max값이 top
priority_queue<int,vector<int>,greater<int>> Min; //큰것들의 min값이 top

void Input()
{
    cin >> T;
}

void Solution()
{
    while (T--) {
        int a;
        cin >> a;
        if (Max.size() == Min.size())
            Max.push(a);
        else
            Min.push(a);

        if (!Max.empty() && !Min.empty() && Max.top() > Min.top()) {
            int Max_val, Min_val;
            Max_val = Max.top();
            Min_val = Min.top();
            Max.pop();
            Min.pop();
            Max.push(Min_val);
            Min.push(Max_val);


        }
        cout << Max.top() << "\n";
    }
}

void Solve()
{
    Input();
    Solution();
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    Solve();
    return 0;
}
