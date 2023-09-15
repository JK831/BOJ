#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Key point: 빛의 방향과 위치가 빛이 시작했을 때의 그것과 같아졌을 때 사이클의 길이
// -> 각 노드들마다 어떤 방향에 대해 빛이 들어왔을 시 저장, 탐색 중에 저장된 방향에 대해 빛이 다시 들어왔을 시 한 사이클 완성된 것.
// --> Visited[Row][Column][Direction] = true or false

// 노드에서 다른 노드로 이동 시 범위 체크하여 적절한 노드로 이동시킨다.
// 모든 노드들에 대해 4가지 방향에 대한 경우 탐색
// S = 현재 방향 그대로. L, R에 따라 방향 전환


// 각 노드들마다 특정 방향으로 빛을 받은 적이 있는지 저장
bool Visited[501][501][4] = {false, };

// 상, 우, 하, 좌
int Dx[4] = {0, 1, 0, -1};
int Dy[4] = {-1, 0, 1, 0};

int SizeOfRow;
int SizeOfCol;

vector<int> answer;


void Search(int CurRow, int CurCol, int CurDir, int Length, const vector<string>& grid)
{
    Visited[CurRow][CurCol][CurDir] = true;
    
    switch (grid[CurRow][CurCol])
    {
    case 'L':
        CurDir = (CurDir + 3) % 4;
        break;
    case 'R':
        CurDir = (CurDir + 1) % 4;
        break;
    }
    
    // 방향에 따라 다음 노드 지정
    int NextRow = (CurRow + Dy[CurDir] + SizeOfRow) % SizeOfRow;
    int NextCol = (CurCol + Dx[CurDir] + SizeOfCol) % SizeOfCol;
    Length += 1;
    
    if (Visited[NextRow][NextCol][CurDir])
    {
        answer.push_back(Length);
        return;
    }
    
    Search(NextRow, NextCol, CurDir, Length, grid);
}

vector<int> solution(vector<string> grid) {
    SizeOfRow = grid.size();
    SizeOfCol = grid[0].size();
    
    // 모든 노드들마다 4방향에 대해 탐색
    for (int CurRow = 0; CurRow < SizeOfRow; ++CurRow)
    {
        for (int CurCol = 0; CurCol < SizeOfCol; ++CurCol)
        {
            for (int CurDir = 0; CurDir < 4; ++CurDir)
            {
                if (Visited[CurRow][CurCol][CurDir]) continue;
                
                Search(CurRow, CurCol, CurDir, 0, grid);
            }
            
        }
    }
    
    sort(answer.begin(), answer.end());
    return answer;
}