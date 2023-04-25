#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Key point: 자신의 값이 왼쪽의 최솟값과 오른쪽의 최솟값보다 클 경우 반드시 삭제 됨 (왼쪽이나 오른쪽에 자신보다 큰 값이 있는 경우 남아 있을 수 있다.)
// 남길 수 있는 풍선을 저장하는 Set을 만든다 (Set 사용시 왼쪽, 오른쪽 한 번씩 순회하며 값을 넣어도 값이 중복 되지 않음)
// 1. 왼쪽의 최솟값과 비교하여 자신의 값이 작거나 왼쪽에 아무 값이 없을 경우 Set에 insert
// 2. 오른쪽의 최솟값과 비교하여 자신의 값이 작거나 오른쪽에 아무 값이 없을 경우 Set에 insert
// 3. answer = Set의 크기


set<int> canDeleteList; // 삭제 가능한 풍선의 집합

int solution(vector<int> a) {
    
    int answer = 0;
    
    int check;
    
    // 왼쪽부터 확인
    for(int i = 0; i < a.size(); ++i)
    {
        // 맨 첫번째 값
        if (i == 0)
        {
            check = a[i];
            canDeleteList.insert(i); // 왼쪽에 아무 값도 없으므로 삭제 가능
        }
        else
        {
            // 지금 풍선이 왼쪽 값들 중 최솟값보다 작은 경우
            if(check > a[i])
            {
                check = a[i]; // 최솟값 업데이트
                canDeleteList.insert(i); // 왼쪽에 자신보다 큰 값이 있으므로 삭제 가능
            }
        }
    }
    
    // 오른쪽부터 확인
    for(int i = a.size() - 1; i >= 0; --i)
    {
        // 맨 첫번째 값
        if (i == a.size() - 1)
        {
            check = a[i];
            canDeleteList.insert(i); // 오른쪽에 아무 값도 없으므로 삭제 가능
        }
        else
        {
            // 지금 풍선이 오른쪽쪽 값들 중 최솟값보다 작은 경우
            if(check > a[i])
            {
                check = a[i]; // 최솟값 업데이트
                canDeleteList.insert(i); // 오른쪽에 자신보다 큰 값이 있으므로 삭제 가능
            }
        }
    }
    
    answer = canDeleteList.size();
    
    return answer;
}