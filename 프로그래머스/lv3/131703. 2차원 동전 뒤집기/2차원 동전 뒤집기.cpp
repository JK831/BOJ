#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Key point: 각 행이나 열에 대해 뒤집거나, 뒤집지 않는 경우가 존재하고 모든 행과 열에 대해 뒤집거나 뒤집지 않는 경우의 수의 총합은 2^(N + M)이 된다.
// 이 모든 경우의 수를 비트 연산을 통해 탐색한다.

int N, M;

void TurnUp(bool isRow, int y, int x, vector<vector<int>>& board)
{
    if(isRow)
        for(int col = 0; col < M; ++col) board[y][col] = board[y][col] == 1 ? 0 : 1;
    else for(int row = 0; row < N; ++row) board[row][x] = board[row][x] == 1 ? 0 : 1;
}

int solution(vector<vector<int>> beg, vector<vector<int>> tar) {
    int answer = 30;
    N = beg.size();
    M = beg[0].size();
    
    int k = 1 << (N + M);
    
    vector<vector<int>> copiedBeg;
    
    // 2^(N + M)개의 경우에 대해 탐색
    for (int bi = 0; bi < k; ++bi)
    {
        copiedBeg = beg;
        int turnCnt = 0;
        // 행 뒤집으며 탐색
        for (int i = 0; i < N; ++i)
        {
            int bi_i = 1 << i;
            // 뒤집기
            if ((bi & bi_i) != 0)
            {
                turnCnt++;
                TurnUp(true, i, 0, copiedBeg);
            }
        }
        
        // 열 탐색
        for (int j = 0; j < M; ++j)
        {
            int bi_j = 1 << (j + N);
            if ((bi & bi_j) != 0)
            {
                turnCnt++;
                TurnUp(false, 0, j, copiedBeg);
            }
        }
        
        if (copiedBeg == tar)
            answer = min(answer, turnCnt);
    }
    if (answer == 30) answer = -1;
    return answer;
}