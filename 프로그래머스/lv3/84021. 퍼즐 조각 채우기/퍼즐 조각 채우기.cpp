#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

int visited[51][51];
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

vector<vector<pair<int,int>>> allPairs;

// Key point:  조각의 좌표를 움직여 game_board의 처음부터(0, 0) 끝까지(n, n) 훑으며 해당 조각이 들어갈 수 있는 자리인지 검사한다.
// game_board의 해당 칸이 0이면 cnt 를 증가시키고, cnt가 조각의 칸 수와 같다면, 조각의 칸 하나하나를 순회하며 상하좌우가 0이 아닌지 검사한다.
// 만약 0이라면, 조각과 모양이 꼭 맞지 않는 것이므로, answer에 추가되지 않는다.
// 만약 딱 맞는다면 answer에 조각 칸 수를 추가하고, 조각모음 visit 배열을 만들어 해당 조각은 다음에 사용하지 않도록 한다.
// game_board에도 1로 만들어 다음에 해당 칸에 또 조각을 끼워맞추지 않도록 한다.

// 1. 우선 DFS로 table 을 순회하며 1인 곳의 좌표를 저장한 2차원 vector 조각모음을 만들어 준다.
// 2. game_board를 90 도 만큼 회전시켜 좌표를 갱신한다.
// 3. 해당 game_board를 가지고, 1에서 저장한 조각모음들과 하나씩 비교하며 조각이 들어갈 수 있는지 판별


// table을 순회하며 조각모음을 만들어준다.
void DFS(int y, int x, int n, vector<pair<int,int>> &block, vector<vector<int>> &table)
{
    if(visited[y][x])
		return;
    if(table[y][x] == 0)
		return;
    
    visited[y][x] = 1;
    block.push_back({ y, x });

    for(int i = 0; i < 4; i++)
    {
        int ny = y + dy[i];
		int nx = x + dx[i];
        if(ny < 0 || nx < 0 || ny >= n || nx >= n)
			continue;
        DFS(ny, nx, n, block, table);
    }
}

bool solve(vector<vector<int>>& board, vector<pair<int,int>>& block)
{
    int n = board.size();

    for(int r = -n + 1; r < n; r++)
    {
        for(int c = -n + 1; c < n; c++)
        {
            vector<pair<int,int>> fitBlock;
            for(auto b : block)
				fitBlock.push_back({b.first + r, b.second + c});

            // game_board의 칸을 순회하며 현재 조각이 들어갈 수 있는지 체크
            int cnt = 0;
            for(int i = 0; i < fitBlock.size(); i++)
            {
                pair<int,int> cur = fitBlock[i];
                if(cur.first < 0 || cur.second < 0 || cur.first >= n || cur.second >= n)
					break;
                if(board[cur.first][cur.second] == 1)
					break;
                cnt++;
            }
            
            // 만약 조각이 들어갈 수 있다면
            if(cnt == fitBlock.size())
            {
                bool fit = true;
                for(auto a : fitBlock)
					board[a.first][a.second] = 1;
                
                for(int i = 0; i < fitBlock.size(); i++)
                {
                    pair<int,int> cur = fitBlock[i];
                    
                    // 현재 칸의 상하좌우가 0이 아닌지 체크
                    for(int d = 0; d < 4; d++)
                    {
                        int ny = cur.first + dy[d];
						int nx = cur.second + dx[d];

                        if(ny < 0 || nx < 0 || ny >= n || nx >= n)
							continue;
                        if(board[ny][nx] == 0)
                        {
                            fit = false;
							break;
                        }
                    }
                    
                    if(fit == false)
						break;
                }
                
                if(fit == false)
                {
                    // board 원상복구
                    for(auto a : fitBlock)
						board[a.first][a.second] = 0;
                }
                else
					return true;
            }
        }
    }
    return false;
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    int answer = 0;
    int n = table.size();

    for(int i = 0; i < table.size(); i++)
    {
        for(int j = 0; j < table[0].size(); j++)
        {
            if(table[i][j] == 1)
            {
                vector<pair<int,int>> block;
                DFS(i, j, table.size(), block, table);
                if(block.size())
					allPairs.push_back(block);
            }
        }
    }

    vector<vector<int>> rotateBoard(n, vector<int>(n,0));
    vector<bool> pairsVis(allPairs.size(), false);
    
    for(int rot = 0; rot < 4; rot++)
    {
        // copy rotated game_board to rotateBoard
        for(int r = 0; r < n; r++)
        {
            for(int c = 0; c < n; c++)
                rotateBoard[r][c] = game_board[c][n-r-1];
        }

        for(int i = 0; i < allPairs.size(); i++)
        {
            if(pairsVis[i] == 0 && solve(rotateBoard, allPairs[i]))
            {
                answer += allPairs[i].size();
                pairsVis[i] = 1;
            }
        }

        // copy rotateBoard to game_board for next roop
        for(int r = 0; r < n; r++)
        {
            for(int c = 0; c < n; c++)
                game_board[r][c] = rotateBoard[r][c];
        }
    }

    return answer;
}