#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    int max_idx = 0;
    int h;
    
    sort(works.begin(), works.end(), greater<int>());
    
    while (max_idx < works.size() - 1)
    {
        while (max_idx < works.size() - 2 && works[max_idx] == works[max_idx + 1])
            max_idx++;
        h = works[max_idx] - works[max_idx + 1];
        if (h * (max_idx + 1) > n)
            break;
        n -= h * (max_idx + 1);
        max_idx++;
    }
    
    int val = works[max_idx];
    if (val * (max_idx + 1) <= n) return 0;
    
    val -= n / (max_idx + 1);
    n -= n / (max_idx + 1) * (max_idx + 1);
    
    answer += (long long)val * (long long)val * (long long)(max_idx + 1 - n);
    answer += (long long)(val - 1) * (long long)(val - 1) * (long long)n;
    
    for (int i = max_idx + 1; i < works.size(); i++)
    {
        answer += (long long)(works[i] * works[i]);
    }
    
    return answer;
}