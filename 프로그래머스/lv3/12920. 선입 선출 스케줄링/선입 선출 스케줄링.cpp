#include <string>
#include <vector>

using namespace std;

// Key point: 이분 탐색을 통해 모든 코어를 사용하면서 n - 1개의 작업을 마칠 수 있는 시간을 구한 후, n번째 작업을 할당할 수 있는 코어를 찾아 할당

int solution(int n, vector<int> cores) {
    int answer = 0;
    int lo = -1, hi = 2e5, mid = 0;
    int numOfCores = cores.size();
    
    while (lo + 1 < hi) // 몇 시간만에 모든 작업을 할 수 있는지 체크
    {
        mid = (lo + hi) / 2;
        int finishedTask = numOfCores;
        // 각 코어 별로 현재 시간 (mid)동안 최대 몇 개의 작업을 할 수 있는지를 구하여 완료된 작업 수에 추가
        if (mid > 0) for(int i = 0; i < numOfCores; ++i) finishedTask += mid / cores[i];
        
        if (finishedTask < n) lo = mid; // 완료된 작업의 수가 목표보다 작다면
        else hi = mid;
    }
    
    if (lo == -1) answer = n;
    else
    {
        int finishedTask = numOfCores;
    
        // 각 코어 별로 구해진 시간동안 할 수 있는 작업 수 추가
        for (int i = 0; i < numOfCores; ++i) finishedTask += lo / cores[i];
        // n - 1개의 작업까지 완료한 이후 n번째 작업을 할 수 있는 코어의 번호 return
        for (int i = 0; i < numOfCores; ++i)
        {
            if ((lo + 1) % cores[i] == 0) finishedTask++;
            if (finishedTask == n)
            {
                answer = i + 1;
                break;
            }
        }    
    }
    
    return answer;
}