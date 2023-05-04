#include <vector>
#include <algorithm>

using namespace std;

// Key point: 조건을 체크하여 설치할 수 있는 지 없는 지 판별. 삭제의 경우엔 해당 구조물 삭제시 해당 구조물 위에 있는 구조물을 설치할 수 있는 지를 판별한다.

int arr[101][101][2];
int N;

// 설치를 위한 조건 체크 및 설치
bool InstallStructure(int x, int y, int a)
{
    if(a == 0)
    { // 기둥 설치
        if(y == 0) return true; // 바닥 위
        if(x > 0 and arr[x - 1][y][1]) return true; // 보의 오른쪽 끝 위
        if(y < N and arr[x][y][1]) return true; // 보의 왼쪽 끝 위
        if(y > 0 and arr[x][y - 1][0]) return true; // 다른 기둥 위
    }
    else
    { // 보 설치
        if(y > 0 and arr[x][y - 1][0]) return true; // 왼쪽 끝 아래에 기둥이 있는 경우
        if(x < N and y > 0 and arr[x + 1][y - 1][0]) return true; // 오른쪽 끝 아래에 기둥이 있는 경우
        if(x > 0 and x < N and arr[x - 1][y][1] and arr[x + 1][y][1]) return true; // 양쪽 끝 부분에 다른 보 설치할 경우
    }
    return false;
}

// 삭제 = 삭제했을 경우 위에 있는 구조물이 설치될 수 있는 지 체크
bool RemoveStructure(int x, int y, int a)
{
    arr[x][y][a] = 0;
    
    if(a == 0) // 기둥 삭제
    {
        // 위에 기둥 있을 때, 설치 가능?
        if(y < N and arr[x][y + 1][0] and !InstallStructure(x, y + 1, 0)) return false;
        
        // 위에 보 있을 때, 설치 가능?
        if(y < N and arr[x][y + 1][1] and !InstallStructure(x, y + 1, 1)) return false;
        if(x > 0 and y < N and arr[x - 1][y + 1][1] and !InstallStructure(x - 1, y + 1, 1)) return false;
    }
    else
    {
        // 위에 기둥 있을 때, 설치 가능?
        if(arr[x][y][0] and !InstallStructure(x, y, 0)) return false;
        if(x < N and arr[x + 1][y][0] and !InstallStructure(x + 1, y, 0)) return false;
        
        // 다른 보와 연결되어 있을 때, 설치 가능?
        if(x > 0 and arr[x - 1][y][1] and !InstallStructure(x - 1, y, 1)) return false;
        if(x < N and arr[x + 1][y][1] and !InstallStructure(x + 1, y, 1)) return false;
    }
    
    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    N = n;
    vector<vector<int>> answer;
    
    for (auto frame: build_frame)
    {
        int x = frame[0];
        int y = frame[1];
        int a = frame[2];
        int b = frame[3];
        
        if(b == 0)
        {
            if(!RemoveStructure(x, y, a)) arr[x][y][a] = 1;
        }
        else
        {
            if(InstallStructure(x, y, a)) arr[x][y][a] = 1;
        }
    }
    
    for(int i = 0; i <= n; ++i)
    {
        for(int j = 0; j <= n; ++j)
        {
            if(arr[i][j][0]) answer.push_back({i, j, 0});
            if(arr[i][j][1]) answer.push_back({i, j, 1});
        }
    }
    
    return answer;
}