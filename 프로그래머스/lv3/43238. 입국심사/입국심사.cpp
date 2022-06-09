#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long binary_search(long long mid, const vector<int>& Times)
{
    long long result = 0;
    for (int i = 0; i < Times.size(); i++)
    {
        result += mid / (long long)Times[i];
    }
    
    return result;
}

long long solution(int n, vector<int> times) {
    long long answer;
    sort(times.begin(), times.end());
    // 가장 큰 값을 뽑기 위해 정렬
	// 해당 함수는 max_element()를 사용해도 됨.

    long long min = 1;
    long long max = (long long)n * times.back();
    long long avg;
    
    answer = max;
    // 최대값과 최소값이 교차하는 구간이 최소 시간(목표 지점)
    while(min <= max)
    {
        avg = (min + max) / 2;
        
        if (binary_search(avg, times) < n) min = avg + 1;
        else
        {
            max = avg - 1;
            if (avg < answer)
                answer = avg;
        }   
    }
    return answer;
}