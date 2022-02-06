#include<iostream>
#include<string>
#include<cstring>
 
#define endl "\n"
#define MAX 9
using namespace std;
 
int N, Tc;
int MAP[MAX][MAX];
bool Row[MAX][MAX + 1];    // 행
bool Col[MAX][MAX + 1];    // 열
bool Square[3][3][MAX + 1];
bool Tile[MAX + 1][MAX + 1];
bool Flag, Inp_Flag;
 
void Initialize()
{
    Flag = false;
    memset(MAP, 0, sizeof(MAP));
    memset(Row, false, sizeof(Row));
    memset(Col, false, sizeof(Col));
    memset(Square, false, sizeof(Square));
    memset(Tile, false, sizeof(Tile));
}
 
void Input()
{
    cin >> N;
    if (N == 0)
    {
        Inp_Flag = true;
        return;
    }
    
    for (int i = 0; i < N; i++)
    {
        int Num1, Num2;
        string Pos1, Pos2;
        cin >> Num1 >> Pos1 >> Num2 >> Pos2;
 
        int x = Pos1[0] - 'A';
        int y = Pos1[1] - '0' - 1;
        int xx = Pos2[0] - 'A';
        int yy = Pos2[1] - '0' - 1;
 
        Tile[Num1][Num2] = true;
        Tile[Num2][Num1] = true;
        
        MAP[x][y] = Num1;
        MAP[xx][yy] = Num2;
 
        Row[x][Num1] = true;
        Row[xx][Num2] = true;
 
        Col[y][Num1] = true;
        Col[yy][Num2] = true;
 
        Square[x / 3][y / 3][Num1] = true;
        Square[xx / 3][yy / 3][Num2] = true;
    }
 
    for (int i = 1; i <= 9; i++)
    {
        string Pos; cin >> Pos;
        int x = Pos[0] - 'A';
        int y = Pos[1] - '0' - 1;
 
        Row[x][i] = true;
        Col[y][i] = true;
        Square[(x / 3)][(y / 3)][i] = true;
        MAP[x][y] = i;
    }
}
 
bool Check(int x, int y, int N1, int N2, char C)
{    
    if (C == 'G')    
    {
        /* C = 'G' 일 경우 가로로 놓는 경우 Check. */
        /* (x, y)에 N1과 N2가 붙어있는 타일을 가로로 놓는다. */
        /* = (x, y)에 N1을 (x, y + 1)에 N2를 놓는다. */
 
        if (Row[x][N1] == true || Row[x][N2] == true) return false;
        if (Col[y][N1] == true || Col[y + 1][N2] == true) return false;
        if (Square[x / 3][y / 3][N1] == true || Square[x / 3][(y + 1) / 3][N2] == true) return false;
        return true;
    }
    else
    {
        /* C = 'S'일 경우 세로로 타일을 놓는 경우 Check.
         * (x, y)에 N1과 N2가 붙어있는 타일을 세로로 놓는다.
         * = (x , y)에 N1을, (x + 1, y)에 N2를 놓는다.
         */
        if (Row[x][N1] == true || Row[x + 1][N2] == true) return false;
        if (Col[y][N1] == true || Col[y][N2] == true) return false;
        if (Square[x / 3][y / 3][N1] == true || Square[(x + 1) / 3][y / 3][N2] == true) return false;
        return true;
    }
}
 
void MakeVisit(int x, int y, int N1, int N2, char C, bool T)
{
    Tile[N1][N2] = T;
    Tile[N2][N1] = T;
 
    if (C == 'G')
    {
        Row[x][N1] = Row[x][N2] = T;
        Col[y][N1] = Col[y + 1][N2] = T;
        Square[x / 3][y / 3][N1] = Square[x / 3][(y + 1) / 3][N2] = T;
 
        if (T == true)
        {
            MAP[x][y] = N1;
            MAP[x][y + 1] = N2;
        }
        else MAP[x][y] = MAP[x][y + 1] = 0;
    }
    else
    {
        Row[x][N1] = Row[x + 1][N2] = T;
        Col[y][N1] = Col[y][N2] = T;
        Square[x / 3][y / 3][N1] = Square[(x + 1) / 3][y / 3][N2] = T;
 
        if (T == true)
        {
            MAP[x][y] = N1;
            MAP[x + 1][y] = N2;
        }
        else MAP[x][y] = MAP[x + 1][y] = 0;
    }
}
 
void Print()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << MAP[i][j];
        }
        cout << endl;
    }
}
 
void DFS(int Idx)
{
    if (Flag == true) return;
    if (Idx == 81)
    {
        Flag = true;
        cout << "Puzzle " << Tc << endl;
        Print();
        return;
    }
 
    int x = Idx / MAX;
    int y = Idx % MAX;
 
    if (MAP[x][y] != 0) DFS(Idx + 1);
    else
    {
        if (y <= 7 && MAP[x][y + 1] == 0)
        {
            for (int i = 1; i <= 9; i++)
            {
                for (int j = i + 1; j <= 9; j++)
                {
                    if (Tile[i][j] == false)
                    {
                        if (Check(x, y, i, j, 'G') == true)
                        {
                            MakeVisit(x, y, i, j, 'G', true);
                            DFS(Idx + 2);
                            MakeVisit(x, y, i, j, 'G', false);
                        }
 
                        if (Check(x, y, j, i, 'G') == true)
                        {
                            MakeVisit(x, y, j, i, 'G', true);
                            DFS(Idx + 2);
                            MakeVisit(x, y, j, i, 'G', false);
                        }
                    }
                }
            }
        }
 
        if (x <= 7 && MAP[x + 1][y] == 0)
        {
            for (int i = 1; i <= 9; i++)
            {
                for (int j = i + 1; j <= 9; j++)
                {
                    if (Tile[i][j] == false)
                    {
                        if (Check(x, y, i, j, 'S') == true)
                        {
                            MakeVisit(x, y, i, j, 'S', true);
                            DFS(Idx + 1);
                            MakeVisit(x, y, i, j, 'S', false);
                        }
 
                        if (Check(x, y, j, i, 'S') == true)
                        {
                            MakeVisit(x, y, j, i, 'S', true);
                            DFS(Idx + 1);
                            MakeVisit(x, y, j, i, 'S', false);
                        }
                    }
                }
            }
        }
    }
}
 
void Solution()
{
    DFS(0);
}
 
void Solve()
{
    Tc = 1;
    while (1)
    {
        Initialize();
        Input();
        if (Inp_Flag == true) break;
        Solution();
        Tc++;
    }
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solve();
 
    return 0;
}
