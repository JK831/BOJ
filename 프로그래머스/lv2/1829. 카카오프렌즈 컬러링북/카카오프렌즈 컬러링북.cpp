#include <vector>
#include <queue>

using namespace std;

int MAX_SIZE;
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
bool Visit[100][100];

int BFS(int fy, int fx, int m, int n, vector<vector<int>> MAP)
{
    int color = MAP[fy][fx];
    int size = 1;
    queue<pair<int, int>> Q;
    Q.push(make_pair(fy, fx));
    Visit[fy][fx] = true;
    
    while (Q.empty() == 0)
    {
        int y = Q.front().first;
        int x = Q.front().second;
        Q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && ny >= 0 && nx < n && ny < m)
            {
                if (MAP[ny][nx] == color && Visit[ny][nx] == false)
                {
                    Q.push(make_pair(ny, nx));
                    Visit[ny][nx] = true;
                    size++;
                }
            }
        }
    }
    return size;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    for(int i = 0 ; i < m; i++)
    {        
        for(int j = 0 ; j < n; j++)
        {
            Visit[i][j] = false;
        }
    }
    
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (picture[i][j] != 0 && Visit[i][j] == false)
            {
                int size = BFS(i, j, m, n, picture);
                if (size > max_size_of_one_area) max_size_of_one_area = size;
                number_of_area++;
            }
        }
    }
    
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    
    return answer;
}