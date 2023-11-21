#include <string>
#include <vector>

using namespace std;

// Key point: O, X가 각각 승리할 경우, 무승부일 경우의 O와 X의 개수가 게임 규칙에 따라 나올 수 있는 개수인지 체크

// O가 승리할 경우: O가 X보다 1개 더 많다
// X가 승리할 경우: O와 X의 개수가 같다.
// 무승부일 경우: O가 X보다 1개 더 많거나 같고 빙고가 없다.

// 빙고의 개수를 세어 누가 승리했는지를 파악하고 O와 X 개수 조건에 맞는지 체크


int solution(vector<string> board) {
    vector<int> NumOfOX(2, 0);
    vector<int> NumOfBingo(2, 0);
    
    // O와 X의 개수 Count
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if (board[row][col] == '.') continue;
            board[row][col] == 'O' ? ++NumOfOX[0] : ++NumOfOX[1];
        }
    }
    
    // X가 O보다 많은 경우나 O가 X보다 2개 이상 많을 경우 = 잘못된 경우
    if (NumOfOX[0] < NumOfOX[1] || NumOfOX[0] - NumOfOX[1] > 1)
        return 0;
    
    for (int row = 0; row < 3; ++row)
    {
        // 행 빙고 체크
        if (board[row][0] != '.' && board[row][0] == board[row][1] && board[row][0] == board[row][2])
        {
            board[row][0] == 'O' ? ++NumOfBingo[0] : ++NumOfBingo[1];
        }
        // 열 빙고 체크
        if (board[0][row] != '.' && board[0][row] == board[1][row] && board[0][row] == board[2][row])
        {
            board[0][row] == 'O' ? ++NumOfBingo[0] : ++NumOfBingo[1];
        }
    }
    
    // 좌->우 대각선 빙고 체크
    if (board[0][0] != '.' && board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        board[0][0] == 'O' ? ++NumOfBingo[0] : ++NumOfBingo[1];
    }
    
    // 우->좌 대각선 빙고 체크
    if (board[0][2] != '.' && board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        board[0][2] == 'O' ? ++NumOfBingo[0] : ++NumOfBingo[1];
    }
    
    
    // 무승부일 경우
    if (NumOfBingo[0] == NumOfBingo[1] && NumOfBingo[0] == 0)
    {
        return NumOfOX[0] == NumOfOX[1] + 1 || NumOfOX[0] == NumOfOX[1];
    }
    
    // O가 승리했을 경우
    if (NumOfBingo[0] > NumOfBingo[1])
    {
        return NumOfOX[0] == NumOfOX[1] + 1;
    }
    
    // X가 승리했을 경우
    if (NumOfBingo[0] < NumOfBingo[1])
    {
        return NumOfOX[0] == NumOfOX[1];
    }
    
    // 위 경우들에 해당하지 않을 시 잘못된 경우이다.
    return 0;
}