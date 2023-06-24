#include <string>
#include <vector>
#include <deque>

using namespace std;

// Key point: ShiftRow 수행 시 각 행의 순서를 차례로 바꾸는 것이 아니라 첫번째 행을 가리키는 index 변수로 관리한다.
// Rotate 수행을 위해 첫번째 열과 마지막 열을 분리하여 관리한다. Rotation 수행 시 첫번째 열의 첫번째 원소가 첫번째 행 (index가 가리키는 행)의 맨 앞에 삽입되고, 그 행의 마지막 원소가 마지막 열의 첫번째 원소로 들어간다. 마지막 열의 마지막 원소가 마지막 행 ((index로부터 행의 총 개수 - 1) % 행의 총 개수의 결과로 나온 숫자에 해당하는 행)의 마지막 원소로 삽입되고 그 행의 첫번째 원소가 첫번째 열의 마지막 원소로 삽입되면 Rotate 수행이 정상적으로 이루어진다.

vector<vector<int>> solution(vector<vector<int>> rc, vector<string> operations) {
    int r = rc.size();
    int c = rc[0].size();
    vector<vector<int>> answer(r, vector<int>(c));
    deque<int> firstCol, lastCol;
    
    // Initialize first and last column.
    for(int i = 0; i < r; ++i)
    {
        firstCol.push_back(rc[i][0]);
        lastCol.push_back(rc[i][c - 1]);
    }
    
    // A matrix with first and last column removed
    deque<int> rows[r];
    for(int i = 0; i < r; ++i)
        for(int j = 1; j <= c - 2; ++j)
            rows[i].push_back(rc[i][j]);
    
    int idx = 0;
    for(auto operation : operations)
    {
        if (operation == "ShiftRow")
        {
            firstCol.push_front(firstCol.back());
            firstCol.pop_back();
            lastCol.push_front(lastCol.back());
            lastCol.pop_back();
            --idx;
            if(idx == -1) idx = r - 1;
        }
        else // Rotate
        {
            // 1. Move first element of the first column to front of first row of the matrix.
            rows[idx].push_front(firstCol.front());
            firstCol.pop_front();
            
            // 2. Move last element of first row of the matrix to front of the last column.
            lastCol.push_front(rows[idx].back());
            rows[idx].pop_back();
            
            // 3. Move last element of the first column to back of last row of the matrix.
            rows[(idx + r - 1) % r].push_back(lastCol.back());
            lastCol.pop_back();
            
            // 4. Move first element of last row of the matrix to back of the first column.
            firstCol.push_back(rows[(idx + r - 1) % r].front());
            rows[(idx + r - 1) % r].pop_front();
        }
    }
    
    for(int i = 0; i < r; i++)
    {
        answer[i][0] = firstCol[i];
        
        for (int j = 1; j <= c - 2; ++j)
            answer[i][j] = rows[(i + idx) % r][j - 1];
        
        answer[i][c - 1] = lastCol[i];
    }
    return answer;
}