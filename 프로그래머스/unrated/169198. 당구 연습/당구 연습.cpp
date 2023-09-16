#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Key point: 사방의 벽을 기준으로 시작점을 대칭이동하여 목표 지점과의 거리를 구한다.
// -> 벽의 입사각과 반사각이 똑같으므로 원래 시작점에서 특정 벽을 맞추고 목표까지 이동하는 거리와 그 벽을 기준으로 대칭이동한 지점에서 목표까지 이동해야 하는 거리는 똑같다.

// 시작점을 각각의 벽들에 대해 대칭이동 시켰을 때의 좌표와 목표 공의 위치와의 거리를 계산하여 가장 작은 값을 저장.
// ** 시작점의 X좌표가 목표 공의 X좌표와 같을 경우 시작점의 Y좌표가 목표 공의 Y좌표보다 클 경우 왼쪽 벽에 원쿠션 불가능, 작을 경우 오른쪽 벽에 원쿠션 불가능
// Y좌표가 목표공의 Y좌표와 같을 경우 시작점의 X좌표가 목표 공의 X좌표보다 클 경우 아래 벽에 원쿠션 불가능, 작을 경우 윗 벽에 원쿠션 불가능

// 각 벽을 기준으로 대칭 이동시 벽 별 시작점의 위치
// 윗벽 startY + 2 (n - startY) = 2m - startY
// 아랫벽 -startY
// 왼벽 -startX
// 오른벽 startX + 2 (m - startX) = 2m - startX

const int INF = 12345678;

vector<int> solution(int m, int n, int startX, int startY, vector<vector<int>> balls) {
    vector<int> answer;
    answer.reserve(balls.size());
    
    for (int i = 0; i < balls.size(); ++i)
    {
        // 최소거리 저장
        int MinDistance = INF;
        
        // 윗벽
        if (!(startX == balls[i][0] && startY < balls[i][1]))
            MinDistance = min(MinDistance, (int)(pow(balls[i][0] - startX, 2) + pow(balls[i][1] - 2*n + startY, 2)));
        // 아랫벽
        if (!(startX == balls[i][0] && startY > balls[i][1]))
            MinDistance = min(MinDistance, (int)(pow(balls[i][0] - startX, 2) + pow(balls[i][1] + startY, 2)));
        // 왼벽
        if (!(startY == balls[i][1] && startX > balls[i][0]))
            MinDistance = min(MinDistance, (int)(pow(balls[i][0] + startX, 2) + pow(balls[i][1] - startY, 2)));
        // 오른벽
        if (!(startY == balls[i][1] && startX < balls[i][0]))
            MinDistance = min(MinDistance, (int)(pow(balls[i][0] - 2*m + startX, 2) + pow(balls[i][1] - startY, 2)));
          
        answer.push_back(MinDistance);
    }
    return answer;
}