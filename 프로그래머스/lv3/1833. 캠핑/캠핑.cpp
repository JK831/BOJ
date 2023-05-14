#include <vector>
#include <algorithm>

using namespace std;

// Key point: x, y 값이 각각 다른 두 좌표를 선택하여 해당 좌표 사이에 포함되는 좌표가 있는지 체크한다.

// 1. 좌표 오름차순으로 정렬
// 2. 정렬된 좌표를 순회하며 첫번째 좌표를 선택
// 3. 두번째 좌표를 선택, 이때 첫번째 좌표와 x와 y가 각각 다른 좌표를 선택한다.
// 4. 두 좌표 사이의 범위에 포함되는 좌표가 있는지 체크

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<vector<int>> data) {
    int answer = 0;
    sort(data.begin(), data.end());
    
    for (int i = 0; i < n; ++i)
    {
        int x1 = data[i][0];
        int y1 = data[i][1];
        
        for (int j = i + 1; j < n; ++j)
        {
            int x2 = data[j][0];
            int y2 = data[j][1];
            
            if (x1 == x2 or y1 == y2) continue; // x나 y좌표가 같은 경우 continue
            
            // 두 좌표 사이에 포함되는 좌표가 있는지 확인
            bool flag = true;
            for (int k = i + 1; k < j; ++k)
            {
                int cx = data[k][0];
                int cy = data[k][1];
                
                if (x1 < cx and cx < x2 and min(y1, y2) < cy and cy < max(y1, y2))
                {
                    flag = false;
                    break;
                }
            }
            if (flag) ++answer;
        }
    }
    return answer;
}