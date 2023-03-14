#include <string>
#include <vector>

using namespace std;

// Key Point: DFS로 수를 탐색, 상대에게 최선의 결과 = 나에게 최악의 결과
// 각 플레이어는 최선의 결과만 리턴하면 된다
// 최선의 경우 -> 이긴 경우가 있을 시 이긴 경우 중 가장 이동횟수가 적은 경우 리턴, 모두 졌을 시 가장 이동횟수가 많은 경우 리턴

#define boardN 5
#define INF 2147483647

vector<vector<int>> GBoard;
int C, R; // 보드의 가로, 세로 길이 | X = 가로, Y = 세로
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

// A의 위치, B의 위치, 차례 (A = true, B = false)
int DFS(int ax, int ay, int bx, int by, bool turn)
{
    int x = turn ? ax : bx;
    int y = turn ? ay : by;
    
    vector<int> cases;
    
    for (int i = 0; i < 4; ++i)
    {
        // 다음에 이동할 좌표
        int nX = x + dx[i];
        int nY = y + dy[i];
        
        if (nX < 0 || nY < 0 || nX >= C || nY >= R || GBoard[nY][nX] == 0)
            continue;
        
        // 위치가 같을 경우 1번 움직인 후 바로 끝남
        if (ax == bx && ay == by)
        {
            cases.push_back(1);
            continue;
        }
        
        // Back tracking, 현재 이동한 위치에서 탐색을 시작한 후 탐색을 마치면 탐색 전 상태로 되돌려 놓는다.
        GBoard[y][x] = 0;
        int numOfMove;
        // 상대는 자신에게 최선의 수를 리턴한다 -> 나에게는 최악의 수, 상대의 수의 부호를 바꿔준다
        numOfMove = turn ? -DFS(nX, nY, bx, by, !turn) : -DFS(ax, ay, nX, nY, !turn);
        
        // 이번 턴의 이동횟수 추가해준다 -> 상대가 리턴한 결과의 절대값을 증가시켜줄 수 있도록 처리
        numOfMove >= 0 ? numOfMove++ : numOfMove--;
        cases.push_back(numOfMove);
        GBoard[y][x] = 1;
    }
    
    // 이긴 경우가 있을 시 이겼을 시의 최선의 상황 (움직인 횟수가 최소인 경우 -> 양수 최솟값)
    // 이긴 경우가 없을 시 최선의 상황 (움직인 횟수가 최대인 경우 -> 음수 최솟값(음수로 저장되어있으므로))
    int winMax = -INF, winMin = INF;
    int loseMax = -INF, loseMin = INF;
    
    
    // 리스트를 순회하며 각 인덱스의 수를 체크, 이긴 경우가 있다면 리스트 내에 0 이상의 수가 있다.
    // 체크한 수가 0 이상의 수일 시 해당 수와 저장된 최솟값과 비교하여 더 작은 수 저장
    // 진 경우의 수 또한 저장된 최솟값 (졌을 경우의 최선의 수)과 비교하여 더 작은 수 저장
    for (int i = 0; i < cases.size(); ++i)
    {
        int num = cases[i];
        if (num > 0) // 이긴 경우
        {
            winMax = max(winMax, num);
            winMin = min(winMin, num);
        }
        else // 진 경우
        {
            loseMax = max(loseMax, num);
            loseMin = min(loseMin, num);
        }
    }
    if (winMax == -INF && loseMax == -INF) return 0; // 리스트에 저장된 수가 없을 경우 (움직이지 못하는 경우)
    else if (winMax == -INF) return loseMin; // 이긴 경우가 없을 시
    else if (winMax != -INF) return winMin; // 이긴 경우가 있을 시
    
    // return 0; // 불가능한 경우
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    int answer = -1;
    C = board[0].size(); // 가로 길이
    R = board.size(); // 세로 길이
    GBoard = board;
    // DFS의 리턴 값이 음수일 수 있으므로 절대값으로 만들어준다.
    answer = abs(DFS(aloc[1], aloc[0], bloc[1], bloc[0], true));
    return answer;
}