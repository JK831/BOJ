#include <string>
#include <vector>

using namespace std;

// Key point: 누적합 이용
// (0, 0) ~ (3, 3)까지 특정 값 X를 더한다고 가정 시
// 범위의 첫 원소에 X를 더하고, 범위의 끝 다음 인덱스에 -(X) 더한다.
// 그 후, 배열 전체적으로 현재 인덱스의 원소 += 이전 인덱스의 원소
// => 지정된 범위에는 X가 더해지고 그 이외의 범위는 이전 값이 그대로 유지된다.

int AccSum[1010][1010];
 
void CalculateAccSum(const vector<vector<int>>& board, const vector<vector<int>>& skills)
{
    for (auto skill : skills)
    {
        int type = skill[0];
        int r1 = skill[1];
        int c1 = skill[2];
        int r2 = skill[3];
        int c2 = skill[4];
        int degree = skill[5];
        degree = type == 1 ? degree * -1 : degree;
        
        AccSum[r1][c1] += degree;
        AccSum[r2 + 1][c2 + 1] += degree;
        AccSum[r1][c2 + 1] -= degree;
        AccSum[r2 + 1][c1] -= degree;
    }
 
    for (int i = 0; i <= board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
            AccSum[i][j + 1] += AccSum[i][j];
    }
 
    for (int j = 0; j <= board[0].size(); j++)
    {
        for (int i = 0; i < board.size(); i++)
            AccSum[i + 1][j] += AccSum[i][j];
    }
}

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;
    
    CalculateAccSum(board, skill);
    
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] + AccSum[i][j] > 0)
                answer++;
        }
    }
    return answer;
}