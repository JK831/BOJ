#include <string>
#include <vector>

using namespace std;

int N, M, Size, Point;
vector<vector<int>> MAP;

void Make_MAP(vector<vector<int>> lock)
{
    int lock_x = 0;
    int lock_y = 0;
    
    for (int i = M - 1; i < Size - (M - 1); i++, lock_y++)
    {
        for (int j = M - 1; j < Size - (M - 1); j++, lock_x++)
        {
            MAP[i][j] = lock[lock_y][lock_x];
            if (MAP[i][j] == 0) Point++;
        }
        lock_x = 0;
    }
}

int Sum_Key_And_Lock(int Sy, int Sx, vector<vector<int>> key)
{
    int x_idx = 0;
    int y_idx = 0;
    int check = 0;
    
    for (int i = Sy; i < Sy + M; i++, y_idx++)
    {
        for (int j = Sx; j < Sx + M; j++, x_idx++)
        {
            if (MAP[i][j] == 1 && key[y_idx][x_idx] == 1) return -1;
            if (MAP[i][j] == 0 && key[y_idx][x_idx] == 0) return -1;
            if (MAP[i][j] == 0 && key[y_idx][x_idx] == 1) check++;
        }
        x_idx = 0;
    }
    
    return check;
}

void Rotate_Key(vector<vector<int>>& key)
{
    //(0 , 0)에는 (2 , 0)의 값이
    //(0 , 1)에는 (1 , 0)의 값이
    //(0 , 2)에는 (0 , 0)의 값이
    //(1 , 0)에는 (2 , 1)의 값이
    //(x , y)에는 (M - 1 - y , x)의 값이 들어가게 된다.
    vector<vector<int>> Temp = key;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            Temp[i][j] = key[M - 1 - j][i];
        }
    }
    key = Temp;
}

bool Move_MAP(vector<vector<int>> key)
{
    for (int R = 0; R < 4; R++)
    {
        for (int i = 0; i < N + M - 1; i++)
        {
            for (int j = 0; j < N + M - 1; j++)
            {
                int Result = Sum_Key_And_Lock(i, j, key);
                if (Result == Point) return true;
            }
        }
        Rotate_Key(key);
    }
    return false;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    M = key.size();
    N = lock.size();
    Size = N + 2 * (M - 1);
    MAP.resize(Size, vector<int>(Size, 2));
    Make_MAP(lock);
    
    bool answer = Move_MAP(key);
    return answer;
}