#include <iostream>
#include <vector>
#include <algorithm>
 
// Key point: 겹쳐서 그릴 수 있는 선분들의 길이를 누적해가며 답을 구한다.

// 1. 선분들을 시작점 순으로 정렬한다. 최소 시작점과 최대 끝점은 가장 작은 수로 초기화 해둔다.
// 2. 정렬된 모든 선분들을 순회하며 현재 선분의 시작점을 체크하여
// 시작점이 이전 최대 끝점 이전 지점이거나 끝점과 겹친다면
// -> 이전 선분과 겹쳐서 그릴 수 있는 선분이므로 현재 선분의 끝점을 체크하여 이전 선분의 끝점보다 뒤에 있다면 이어서 그릴 수 있는 선분의 길이가 더 길어지므로 끝점 갱신
// 시작점이 최대 끝점 이후 지점이라면
// -> 이전 선분과 겹쳐서 그릴 수 없는 선분이므로 해당 선분의 시작점과 끝점을 다시 최소 시작점, 최대 끝점으로 설정하고 그 선분의 길이를 최대 길이에 누적

using namespace std;

#define MAX 1'000'010
#define INF 1'000'000'010
 
struct Line
{
    int Start;
    int End;
};

int N;
vector<Line> lines(MAX);
 
bool Compare(Line A, Line B)
{
    if (A.Start < B.Start) return true;
    return false;
}
 
void Input()
{
    cin >> N;
    
    for (int i = 1; i <= N; ++i)
    {
        cin >> lines[i].Start >> lines[i].End;
    }
}
 
void Solve()
{
    int answer = 0;
    int Left = -INF;
    int Right = -INF;
    
    sort(lines.begin() + 1, lines.begin() + N + 1, Compare);
    
    for (int i = 1; i <= N; ++i)
    {
        if (lines[i].Start <= Right) // 만약 이전 최대 끝점보다 시작점이 앞에 있거나 겹친다면
            Right = max(Right, lines[i].End);
        else // 이전 최대 끝점보다 시작점이 뒤에 있다면
        {
            answer += Right - Left; // 이전 선분의 길이 누적
            Left = lines[i].Start;
            Right = lines[i].End;
        }
    }
    
    answer += Right - Left;
    cout << answer << endl;
}
 
void Solution()
{
    Input();
    Solve();
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solution();
 
    return 0;
}