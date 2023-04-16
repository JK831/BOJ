#include <string>
#include <vector>

using namespace std;

// Key point: 목적지에서 시작하여 쿼리를 역으로 추적, 공이 도달할 수 있는 범위를 만들어줘야 한다.

// 열 번호가 감소하는 방향으로 dx칸 이동하는 쿼리는 해당 쿼리를 실행할 시 목적지 기준 dx만큼 오른쪽에 있는 칸이 목적지에 도달할 수 있는 칸이다.
// => 범위의 시작, 끝 열 번호 dx 만큼 증가
// 열 번호가 증가하는 방향 => 목적지 기준 dx만큼 왼쪽에 있는 칸이 목적지에 도달할 수 있는 칸. => 범위의 시작, 끝 열 번호 dx만큼 감소
// 행 번호가 감소하는 방향 => 목적지 기준 dx만큼 아래쪽에 있는 칸이 목적지에 도달할 수 있는 칸. => 범위의 시작, 끝 행 번호 dx만큼 증가
// 행 번호가 증가하는 방향 => 목적지 기준 dx만큼 위쪽에 있는 칸이 목적지에 도달할 수 있는 칸. => 범위의 시작, 끝 행 번호 dx만큼 감소

// 현재 범위의 시작점이 0이라면 (첫번째 행 or 열) 행 or 열 번호가 감소하는 쿼리 실행할 때 시작범위는 증가되지 않아야 한다.
// => ex) (0, 1) 이 목적 지점일 때 행 번호가 감소하는 쿼리 실행 시 (0, 1)에 도달할 수 있는 칸은 (1, 1), (0, 1) 이다.
// 현재 범위의 끝지점이 격자의 마지막 행 or 열이라면 (행 or 열 번호가 증가하는 쿼리) 종료 범위는 감소되지 않아야 한다.
// => ex) (3, 2) 가 목적 지점일 때 행 번호가 증가하는 쿼리 실행 시 (3, 2)에 도달할 수 있는 칸은 (2, 2), (3, 2) 이다.


long long solution(int n, int m, int x, int y, vector<vector<int>> queries) {
    long long answer = 0;
    int size = queries.size();
    
    long long row_start = x, row_end = x;
    long long col_start = y, col_end = y;
    
    for(int i = size - 1; i >= 0; i--)
    {
        int dir = queries[i][0];
        int dist = queries[i][1];
        
        if(dir == 0)
        { // 열 증가시킴
            if(col_start != 0) 
                col_start = col_start + dist;
            
            col_end = col_end + dist;
            if(col_end > m - 1) 
                col_end = m - 1; 
            
        }
        else if(dir == 1)
        { // 열 감소시킴
            col_start = col_start - dist;    
            if(col_start < 0) 
                col_start = 0;
            
            if(col_end != m - 1) 
                col_end = col_end - dist;
            
        }
        else if(dir == 2)
        { // 행 증가시킴
            if(row_start != 0) 
                row_start = row_start + dist;
            
            row_end = row_end + dist;
            if(row_end > n - 1) 
                row_end = n - 1;
            
        }
        else if(dir == 3)
        { // 행 감소시킴
            row_start = row_start - dist;    
            if(row_start < 0) 
                row_start = 0;
            
            if(row_end != n - 1) 
                row_end = row_end - dist;
            
        }
        
        // 범위의 시작이 격자의 끝 지점을 넘었거나, 범위의 끝이 격자의 시작 지점보다 작은 값이라면 목적지에 도달할 수 있는 경우가 없음.
        if(row_start > n - 1 || row_end < 0 || col_start > m - 1 || col_end < 0) 
            return answer;
    }
    answer = (row_end - row_start + 1) * (col_end - col_start + 1);
    
    return answer;
}