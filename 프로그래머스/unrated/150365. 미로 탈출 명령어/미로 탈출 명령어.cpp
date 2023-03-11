#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <cstdlib>

using namespace std;

// Key point: DFS를 사용하여 목적지까지 가는 루트 탐색, 현재 지점에서의 목적지까지의 거리와 남은 이동횟수를 가지고 도달 가능한 지를 미리 체크한다
// 목적지까지의 거리가 남은 이동횟수보다 크거나, (남은 이동횟수 - 목적지까지의 거리)가 홀수일 때에는 도달할 수 없다. -> CanArrive로 체크
// DFS를 사용할 때 알파벳 순 (d l r u)으로 탐색하도록 한다.
// 다음에 이동할 위치, 이동 횟수 + 1, 현재까지의 string + 다음 위치로 이동할 때의 알파벳을 Queue에 push


int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, 1, -1, 0};
char dChar[4] = {'u', 'r', 'l', 'd'};

int N, M, sx, sy, ex, ey;

int GetDistance(int curX, int curY, int destX, int destY)
{
    return abs(destX - curX) + abs(destY - curY);
}

bool CanArrive(int curX, int curY, int nCount)
{
    int d = GetDistance(curX, curY, ex, ey);
    if(d > nCount || (nCount - d) % 2 == 1 )
        return false;
    
    return true;
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    
    
    if (x == r && y == c)
        return answer;
    
    answer = "impossible";
    
    ex = r;
    ey = c;
    stack<tuple<int, int, int, string>> st;
    
    // 시작 지점에서 목적지까지 도달할 수 있는지 미리 체크
    if (!CanArrive(x, y, k))
        return answer;
    
    st.push({x, y, k, ""});
    while (!st.empty())
    {
        int qx = get<0>(st.top());
        int qy = get<1>(st.top());
        int count = get<2>(st.top());
        string qAns = get<3>(st.top());
        st.pop();
        
        if (count == 0) // 만약 현재 이동횟수가 k와 같다면
        {
            // x와 y가 각각 r, c와 같은 지 체크하고 둘 모두 일치한다면 answer 갱신 후 while문 탈출
            if (qx == r && qy == c)
            {
                answer = qAns;
                break;
            }
        }
        else
        {
            int nCount = count - 1;
            // d, l, r, u 순으로 Queue에 push
            for (int i = 0; i < 4; i++)
            {
                // Queue에 push할 원소들: 다음으로 이동할 x, y, 현재 남은 이동 횟수 -1, 현재 문자열 + 이동 방향에 해당하는 문자
                int nx = qx + dx[i];
                int ny = qy + dy[i];
                
                // 격자 범위를 벗어나는 지 체크
                if (nx < 1 || ny < 1 || nx > n || ny > m || !CanArrive(nx, ny, nCount))
                    continue;

                st.push({nx, ny, nCount, qAns + dChar[i]});
            }
        }
    }
    return answer;
}