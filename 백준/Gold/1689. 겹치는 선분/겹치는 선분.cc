#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Key point: 선분들의 시작점 = 구간 시작, 끝점 = 구간 끝 이므로 구간의 시작을 1로, 구간이 끝난 것을 -1로 나타내준다.
// -> 모든 점들을 정렬한 후에 순회하면서 넣어준 구간의 시작 or 구간의 끝을 나타내는 값을 count에 더하면서 answer에 가장 큰 count값을 저장해준다.

int N;

vector<pair<int,int>> lines(2000001);

void Input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int start, end;
        cin >> start >> end;
        lines[i] = {start, 1};
        lines[i + N] = {end, -1};
    }
}

void Solve()
{
    sort(lines.begin(), lines.end());
    
    int ans = 0, cnt = 0;
    for(auto line : lines)
    {
        cnt += line.second;
        ans = max(cnt, ans);
    }
    
    cout << ans;
}

void Solution()
{
    Input();
    Solve();
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    Solution();
}