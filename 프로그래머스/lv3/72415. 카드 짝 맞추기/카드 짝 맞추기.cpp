#include <string>
#include <vector>
#include <queue>
#include <cstring>
 
#define MAX 4
#define CARD_MAX 7
#define INF 987654321
using namespace std;
 
vector<bool> Select(CARD_MAX, false);
vector<int> Card_List;
vector<int> Card_Order;
vector<int> SameCard_Order;
vector<pair<int, int>> Card_Pos[CARD_MAX];
 
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

// Key point: 보드에 놓여있는 카드의 갯수, 카드의 위치 정보를 저장한 후 이를 이용하여 카드를 찾는 순서를 구성하여 가장 조작 횟수가 적은 순서의 조작 횟수 리턴
// 짝을 이루는 카드들도 순서를 바꿔 탐색할 시 조작횟수가 달라질 수 있으므로 짝을 이루는 카드들의 선택 순서도 고려하여 탐색
// 카드의 순서를 정한 후엔, 카드의 순서대로 BFS로 현재 카드의 짝 카드로 도달하는 최단경로를 구해준다.
// -> BFS 내에서 현재 칸에서 특정 방향으로 한 칸 이동하는 경우와 해당 방향의 가장 가까운 카드로 한 번에 이동하는 경우를 함께 구해준다.


// 앞면인 카드 전부 저장하는 함수
void Find_Exist_Card(const vector<vector<int>>& board)
{
    vector<bool> Exist(CARD_MAX, false);
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0) continue;
            if (Exist[board[i][j]] == false)
            {
                Exist[board[i][j]] = true;
                Card_List.push_back(board[i][j]);
            }
        }
    }
}

// 카드의 위치 정보 저장하는 함수
void Find_Card_Pos(const vector<vector<int>>& board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0) continue;
            Card_Pos[board[i][j]].push_back(make_pair(i, j));
        }
    }
}

// 각 카드에서 다른 카드로의 최단경로를 BFS로 구해준다
int BFS(int Sx, int Sy, int Find_Cnt, int Card, int Idx, vector<vector<int>>& Map)
{
    if (Find_Cnt == 2) return 0;
    
    queue<pair<pair<int, int>, int>> Q;
    vector<vector<bool>> Visit(Map.size(), vector<bool>(Map.size(), false));
    Q.push(make_pair(make_pair(Sx, Sy), 0));
    Visit[Sx][Sy] = true;
    
    int Ex, Ey;
    if (Find_Cnt == 0) // 처음 카드를 찾고 있는 경우
    {
        Ex = Card_Pos[Card][Idx].first;
        Ey = Card_Pos[Card][Idx].second;
    }
    else // 짝 카드를 찾고 있는 경우
    {
        Ex = Card_Pos[Card][!Idx].first;
        Ey = Card_Pos[Card][!Idx].second;
    }
 
    while (Q.empty() == 0)
    {
        int x = Q.front().first.first;
        int y = Q.front().first.second;
        int Cnt = Q.front().second;
        Q.pop();
 
        if (x == Ex && y == Ey)
        {
            Map[x][y] = 0;
            Cnt += BFS(x, y, Find_Cnt + 1, Card, Idx, Map);
            return Cnt;
        }
        
        // 한 칸씩 이동하는 경우
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < MAX && ny < MAX)
            {
                if (Visit[nx][ny] == false)
                {
                    Visit[nx][ny] = true;
                    Q.push(make_pair(make_pair(nx, ny), Cnt + 1));
                }
            }
        }
        
        // 가장 가까운 카드로 이동하는 경우
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            while (1)
            {
                if (nx < 0 || ny < 0 || nx >= MAX || ny >= MAX)
                {
                    nx -= dx[i];
                    ny -= dy[i];
                    break;
                }
                if (Map[nx][ny] != 0) break;
                nx += dx[i];
                ny += dy[i];
            }
 
            if (Visit[nx][ny] == false)
            {
                Visit[nx][ny] = true;
                Q.push(make_pair(make_pair(nx, ny), Cnt + 1));
            }
        }
    }
}

// 같은 카드의 선택 순서를 다르게 하여 탐색하는 함수
void Setting_Search_SameCard_Order(int Cnt, const vector<vector<int>>& Map, int r, int c, int& answer)
{
    if (Cnt == Card_List.size())
    {
        int Result = 0;
        int Sx = r;
        int Sy = c;
        vector<vector<int>> T_MAP = Map;
        for (int i = 0; i < Card_List.size(); i++)
        {
            int Card = Card_Order[i];
            int Idx = SameCard_Order[i];
            Result += BFS(Sx, Sy, 0, Card, Idx, T_MAP);
            
            Sx = Card_Pos[Card][!Idx].first;
            Sy = Card_Pos[Card][!Idx].second;
        }
        answer = min(answer, Result);
        return;
    }
    
    for (int i = 0; i < 2; i++)
    {
        SameCard_Order.push_back(i);
        Setting_Search_SameCard_Order(Cnt + 1, Map, r, c, answer);
        SameCard_Order.pop_back();
    }
}

// 카드의 선택 순서를 다르게 하여 탐색하는 함수
void Setting_Search_Card_Order(int Cnt, const vector<vector<int>>& Map, int r, int c, int &answer)
{
    if (Cnt == Card_List.size())
    {
        Setting_Search_SameCard_Order(0, Map, r, c, answer);
        return;
    }
 
    for (int i = 0; i < Card_List.size(); i++)
    {
        if (Select[i] == true) continue;
        Select[i] = true;
        Card_Order.push_back(Card_List[i]);
        Setting_Search_Card_Order(Cnt + 1, Map, r, c, answer);
        Card_Order.pop_back();
        Select[i] = false;
    }
}
 
int solution(vector<vector<int>> board, int r, int c) 
{
    int answer = INF;
    Find_Exist_Card(board);
    Find_Card_Pos(board);
    Setting_Search_Card_Order(0, board, r, c, answer);
    answer += (Card_List.size() * 2);
    return answer;
}
