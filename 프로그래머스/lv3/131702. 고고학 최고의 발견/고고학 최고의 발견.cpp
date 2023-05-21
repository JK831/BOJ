#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Key point: 4번 이상 회전시키는 것은 의미 없으며 첫번째 행을 제외한 나머지 행들은 윗 행의 상태에 따라 회전할 수 있는 횟수가 정해진다.
// 맨 윗행이 회전에 따라 만들어낼 수 있는 모든 경우의 수에 대해 밑의 행들을 조작하며 맨 밑의 행이 모두 12시 방향을 향하고 있는지 체크한다.

const int INF = 2'147'483'647;
int N;
int result = INF;
vector<vector<int>> board; // Contain rest num to rotate for making zero
vector<int> firstRow;
vector<int> rotationNumOfFirstRow;

// 중 상 우 하 좌
int dx[5] = {0, 0, 1, 0, -1};
int dy[5] = {0, -1, 0, 1, 0};

void DFS(int idx)
{
    if (idx == N)
    {
        vector<vector<int>> tempMap = board;
        vector<int> curNumOfRotation = rotationNumOfFirstRow; // Copy the row made by combination
        int curResult = 0;
        
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                curResult += curNumOfRotation[j];
                
                for (int dir = 0; dir < 5; ++dir)
                {
                    int nx = j + dx[dir];
                    int ny = i + dy[dir];
                    if (nx < 0 || ny < 0 || nx >= N || ny >= N)
                        continue;
                    
                    tempMap[ny][nx] = tempMap[ny][nx] - curNumOfRotation[j] >= 0 ? tempMap[ny][nx] - curNumOfRotation[j] : tempMap[ny][nx] - curNumOfRotation[j] + 4;
                }
            }
            
            curNumOfRotation = tempMap[i]; // 다음 행에서 행해야 하는 회전의 횟수 = 현재 행의 남은 회전 횟수
        }
        
        // 마지막 행 체크 (모두 12시 방향인지)
        for (int j = 0; j < N; ++j)
        {
            if (curNumOfRotation[j] != 0)
                return;
        }
        
        result = min(result, curResult);
        return;
    }
    
    for (int i = 0; i < 4; ++i)
    {
        rotationNumOfFirstRow[idx] = i;
        DFS(idx + 1);
    }
}

int solution(vector<vector<int>> clockHands) {
    int answer = 0;
    N = clockHands.size();
    board.resize(N);
    
    for (int i = 0; i < N; ++i)
    {
        vector<int> row(N);
        for (int j = 0; j < N; ++j)
            row[j] = 4 - clockHands[i][j] == 4 ? 0 : 4 - clockHands[i][j];
        board[i] = row;
    }
    
    rotationNumOfFirstRow.resize(N); // N 크기로 resize
    
    DFS(0);
    
    answer = result;
    
    return answer;
}