#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Key point: k번째 지점에 들어갈 수 있는 수는 자기 자신을 제외한 10,000,000 이하의 숫자 중 가장 큰 약수 이다.
// 어떤 수 k의 자기 자신을 제외한 모든 약수는 k / 2보다 작거나 같다.
// k의 어떤 약수와 그 약수보다 큰 또다른 약수가 곱해져 k를 만들 때, 작은 약수는 k의 제곱근보다 작다.
// -> 2부터 k의 제곱근과 같은 수가 될 때까지 1씩 증가시키며 k를 해당 수로 나눴을 때 나누어 떨어졌다면 k를 해당 수로 나눈 값이 가장 큰 약수이다.

vector<int> solution(long long begin, long long end) {
    vector<int> answer;
    answer.resize(end - begin + 1);
    
    for (long long curNum = begin; curNum <= end; ++curNum)
    {
        int block = 1;
        int sizeX = sqrt(curNum);
        for (int dividend = 2; dividend <= sizeX; ++dividend)
        {
            if (curNum % dividend == 0)
            {
                if (curNum / dividend <= 1e7)
                {
                    block = curNum / dividend;
                    break;
                }
                else if (curNum / dividend > 1e7 && dividend > block)
                {
                    block = dividend;
                }
            }
        }
            answer[curNum - begin] = block;
    }
    
    if (begin == 1)
        answer[0] = 0;
    
    return answer;
}