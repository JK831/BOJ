#include <string>
#include <vector>

using namespace std;

// Key point: 연속합을 사용하여 가장 큰 합을 구한다.
// 펄스 배열이므로 홀수 번째 자리의 원소에 -1을 곱해준 후
// 해당 배열의 값을 더해가며 얻은 최댓값 (1, -1, 1)과 빼가며 얻은 최댓값(-1, 1, -1)을 비교하여 더 큰 값을 return

const int INF = 987654321;

long long max(long long a, long long b)
{
    if (a > b)  return a;
    return b;
}

long long solution(vector<int> sequence) {
    long long answer = 0;
    
    long long psum = 0;
    long long ret = -INF;
    
    vector<long long> purseSeq(sequence.size());
    
    for(int i = 0; i < sequence.size(); ++i)
    {
        purseSeq[i] = sequence[i];
        if(i % 2 == 1)
            purseSeq[i] *= -1;
    }
    for(int i = 0; i < purseSeq.size(); ++i)
    {
        psum = max(psum, 0) + purseSeq[i];
        ret = max(ret, psum);
    }
    
    psum = 0;
    for(int i = 0; i < purseSeq.size(); ++i)
    {
        psum = max(psum, 0) - purseSeq[i];
        ret = max(ret, psum);
    }
    
    answer = ret;
    
    return answer;
}