#include <vector>
#include <queue>

using namespace std;

struct Node { int x, y, cnt;};

bool visit[102][102] = {false, };
int Diretion_X[4] = {0, 0, -1, 1};
int Diretion_Y[4] = {-1, 1, 0, 0};
vector<vector<int>> maps(102, vector<int>(102, 0)); // 사각형을 그릴 맵

// Key point: 사각형을 맵에 그려주는데 좌표를 주어진 그대로 사용할 시 사각형이 이어져 있지 않더라도 탐색할 수 있는 경우가 있다
// -> 모든 좌표에 2를 곱하여 계산한 후 결과 도출하고 다시 2를 나눠준다.
// 그 후 BFS로 최단거리 구하기

int BFS(vector<vector<int>>& maps,int cX, int cY, int iX, int iY)
{
    int count = 0;
    queue<Node> q;
    q.push({cX, cY, 0});
    visit[cX][cY] = true;

    while (!q.empty())
    {
        Node des;
        des = q.front();
        q.pop();

        for (int i = 0; i < 4 ; i++)
        {
            int dx = des.x + Diretion_X[i];
            int dy = des.y + Diretion_Y[i];

            if (dx < 0 || dy < 0) // 맵의 범위 벗어난 경우
                continue;

            if (maps[dx][dy] == 0 || visit[dx][dy] == true) // 벽이거나 이미 방문한 좌표라면
                continue;

            if (dx == iX && dy == iY) // 다음으로 이동할 좌표가 아이템 좌표라면
                return (des.cnt + 1);

            q.push({dx, dy, des.cnt + 1});
            visit[dx][dy] = true;
        }
    }

    return -1;
}

void CreateMaps(vector<vector<int>>& maps, vector<vector<int>>& rectangle, int rectCount)
{
    for (int i = 0; i < rectCount; i++)
    {
        int startX = rectangle[i][0] * 2;
        int startY = rectangle[i][1] * 2;
        int endX = rectangle[i][2] * 2;
        int endY = rectangle[i][3] * 2;
        
        // 사각형을 그려준다
        for (int j = startX; j < endX; j++)  // 왼쪽 하단 부터 오른쪽 하단
        {
            if (visit[j][startY] != true)
                maps[j][startY] = 1;
        }

        for (int j = startY; j < endY + 1; j++)      // 왼쪽 하단부터 왼쪽 상단
        {
            if (visit[startX][j] != true)
                maps[startX][j] = 1;
        }

        for (int j = endX; j > startX; j--)       // 오른쪽 상단부터 왼쪽 상단
        {
            if (visit[j][endY] != true)
                maps[j][endY] = 1;
        }

        for (int j = endY; j > startY - 1; j--)       // 오른쪽 상단부터 오른쪽 하단
        {
            if (visit[endX][j] != true)
                maps[endX][j] = 1;
        }

        for (int k = startX + 1; k < endX; k++)        // 도형이 겹치는구간은 접근할 수 없도록 좌표 0으로 변경
        {
            for (int o = startY + 1; o < endY; o++)
            {
                if (maps[k][o] == 1 && visit[k][o] == true)
                    maps[k][o] = 0;
                else
                    visit[k][o] = true;
            }
        }

        for (int k = startX; k <= endX; k++)         // 다음 도형그릴때 반영하기 위한 플래그 셋
        {
            for (int o = startY; o <= endY; o++)
                visit[k][o] = true;
        }
    }
}

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    int rectCount = rectangle.size();

    CreateMaps(maps, rectangle, rectCount); // 좌표 만들기

    for (int k = 0; k < 102; k++)       // 방문기록 초기화
    {
        for (int i = 0; i < 102; i++)
            visit[k][i] = false;
    }

    answer = BFS(maps, characterX * 2, characterY * 2, itemX * 2, itemY * 2);   // 예외 처리 위해 2배를 곱함

    return answer / 2;    // 계산을 위해 좌표들에 2배가 곱해져 있으므로 2배를 다시 나눔
}

