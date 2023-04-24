#include <string>
#include <vector>

using namespace std;

// Key point: a 배열에서 가장 많이 가지고 있는 수를 스타수열의 교집합의 원소로 삼을 때 스타수열의 길이가 가장 길어진다.

// 1. a와 같은 사이즈의 count 배열을 만들고 a 배열을 순회하며 가장 많이 나온 수 카운트, answer의 초기 값을 0으로 설정
// 2. count 배열을 순회하며 count[i]가 answer 이하면 continue, 현재 i에 대해 a[j] == i 이거나 a[j + 1] == i 이고 a[j] != a[j + 1]일 시 결과 값에 1을 더해주고 j를 2 증가시켜 현재 j보다 2 큰 수를 j로 설정한 후 다시 탐색
// 3. 결과가 현재 answer보다 클 시 answer에 결과 저장 -> 다음 탐색 시 count[i]가 answer보다 작을 시 탐색할 필요가 없는 이유
// 4. 최종 answer에 2를 곱하여 return

int solution(std::vector<int> a) {
    int answer = 0;
    
    vector<int> count(a.size());
    
    // a에 어떤 원소가 몇 개씩 있는지 count
    for(int i = 0; i < a.size(); i++)
        count[a[i]]++;
    
    // 가장 많이 가지고 있는 수를 가지고 조건에 맞는 수열을 만들 시의 수열의 길이 도출해낸다.
    for(int i = 0; i < count.size();i++)
    {
        if (count[i] <= answer)
            continue;
        
        int result = 0;
        
        for(int j = 0; j < a.size() - 1; j++)
        {
            // 조건에 맞는지 체크
            if ((a[j] == i || a[j + 1] == i) && a[j] != a[j + 1])
            {
                result++;
                j++; // for문에서 +1, 여기서 +1 하여 j를 최종적으로 2 증가시킴
            }
            
            
        }
        
        answer = max(answer, result);
    }
    
    return answer * 2;
}