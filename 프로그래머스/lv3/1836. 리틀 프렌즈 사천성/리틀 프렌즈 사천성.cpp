#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define INF 987654321
#define alpha first 
#define pos second 

struct Pos
{
    int y; // 행
    int x; // 열
    int dir; // 방향 (현재 향하고 있는 방향을 알아서 다음 위치를 큐에 삽입할 때 꺾어야할지를 알 수 있다.) 
};

vector<string> Board;
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int M, N;
map<char, Pos> pos_record; // key : 알파벳  value : 위치 (두 알파벳 중 하나만. 그리고 나머지는 BFS 로 찾는다.)

Pos BFS(Pos start, char start_alpha)
{ // start 출발 위치, start_alpha 출발지 알파벳
    queue<Pos> q;
    vector<vector<int>> turn_and_check(M, vector<int>(N, INF)); // 꺾은 횟수 저장

    // 출발 지점 예약
    start.dir = -1;
    q.push(start);
    turn_and_check[start.y][start.x] = 0;

    bool not_first = false; // 출발지의 알파벳과 동일한 위치에서 종료할건데 바로 출발지의 알파벳과 동일하다고 판정되어 종료되면 안되기 때문에 사용할 플래그
    while (!q.empty())
    {
        // 방문
        Pos now = q.front();
        q.pop();

        // 짝꿍을 찾았다면! (출발지가 아니고!)
        if (not_first && Board[now.y][now.x] == start_alpha)
            return { now.y, now.x }; // 제거 가능하다는 뜻이다. 이 짝꿍 알파벳 위치를 리턴하고 종료.
        not_first = true; // 출발지 방문시에만 false 상태고 나머지 위치 방문시엔 모두 true 인 상태

        for (int i = 0; i < 4; ++i)
        {
            int nextY = now.y + dy[i];
            int nextX = now.x + dx[i];
            int nextDir = i;
            int next_turn_count = turn_and_check[now.y][now.x]; // 현재 방문 위치까지 꺾은 횟수가 초기값
            if (now.dir != -1 && now.dir != nextDir) // 출발지가 아니고(출발지의 방향은 -1로 하였다. 출발지에서 예약되는 위치들은 꺾였다고 판단되지 않기 위해) 방향이 일치하지 않으면 꺾어야 한다. 꺾는 횟수를 1 증가시켜야 한다.
                next_turn_count++;

            // 다음 방문 후보 검사
            if (nextY < 0 || nextY >= M || nextX < 0 || nextX >= N) // 1. 범위 내에 있어야 함
                continue;
            if (next_turn_count >= 2) // 2. 꺾은 횟수가 2 이상이 되면 그 위치는 탐색하지 않는다.
                continue;
            if (Board[nextY][nextX] != '.' && Board[nextY][nextX] != start_alpha) // 3. 장애물이 아니어야 함
                continue;
            if (turn_and_check[nextY][nextX] >= next_turn_count)
            { // 4. 기존에 찾은 꺾은 횟수 그 이하로 꺾을 수 있다면 더 적은 횟수로 꺾을 수 있는 가능성이 있는 탐색 경로가 되므로 또 삽입
                q.push({ nextY, nextX, nextDir });
                turn_and_check[nextY][nextX] = next_turn_count; // 위치별 현재까지 꺾은 횟수 업데이트
            }
        }
    }
    return { -1, -1 }; // while문을 빠져나왔다면 짝꿍알파벳을 찾지 못한 것이다. 즉, 제거 불가능! 제거 불가능시에는 {-1, -1}를 리턴하기로 했다.
}

string solution(int m, int n, vector<string> board)
{
    string answer = "";
    M = m;
    N = n;
    Board = board;

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (board[i][j] >= 'A' && board[i][j] <= 'Z')
                pos_record[board[i][j]] = { i, j }; // 두 위치 중 하나의 위치만 담음. 

    while (true)
    {
        bool canRemove = false; // 이번 board에서 제거 할 수 있는 알파벳이 있었다는 것을 표시
        // 현재 board 상태에서 처음으로 제거 가능한 알파벳을 발견하자마자 break (알파벳은 딱 한 종류만 제거함)
        // pos_record 는 map 이기 때문에 letter 는 자동으로 알파벳 순서대로 
        for (auto& letter : pos_record)
        {
            char start_alpha = letter.alpha;
            Pos start = letter.pos;
            Pos dest = BFS(start, start_alpha); // 짝꿍 알파벳 위치 (못찾았다면, 즉 제거 불가능하다면 {-1, -1} 리턴받음)
            if (dest.y != -1 && dest.x != -1)
            { // 제거 가능하다면
                canRemove = true; 
                Board[start.y][start.x] = '.'; // 제거
                Board[dest.y][dest.x] = '.'; // 제거
                answer += start_alpha; // answer 에 반영
                pos_record.erase(start_alpha); // map 에서 지우기
                break;
            }
        }

        if (canRemove) // 지울 수 있는 알파벳이 있었다면 다시 현재의 board 에서 또 제거 가능한 알파벳 중 가장 앞선 순서의 알파벳 제거하러 고고 
            continue;

        if (pos_record.empty()) // map 이 비었다는건 알파벳을 전부 제거했다는 의미
            return answer;
        else // canRemove 는 false 인데 (즉 더 이상 board에서 지울 수 있는게 없음) map 은 비지 않았다면 제거 불가능한 알파벳들이 있다는 의미
            return "IMPOSSIBLE";
    }
}