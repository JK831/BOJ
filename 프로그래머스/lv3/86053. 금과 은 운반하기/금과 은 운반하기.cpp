#include <string>
#include <vector>

using namespace std;

template<typename T>
T Min(T a, T b)
{
    return a < b ? a : b;
}

bool search (int a, int b, const vector<int>& g, const vector<int>& s, const vector<int>& w, const vector<int>& t, long long mid)
{
    long long total_gold = 0;
    long long total_silver = 0;
    long long total_mineral = 0;
    
    for (int i = 0; i < g.size(); i++)
    {
        long long time = t[i];
        long long round_time = time * 2;
        long long move_cnt = mid / round_time;
        if (mid % round_time >= time) move_cnt++;
        long long max_weight = w[i] * move_cnt;
        
        total_gold += Min((long long)g[i], max_weight);
        total_silver += Min((long long) s[i], max_weight);
        total_mineral += Min((long long) g[i] + s[i], max_weight);
    }
    
    if (total_gold >= a && total_silver >= b && total_mineral >= a + b) return true;
    return false;
}

long long solution(int a, int b, vector<int> g, vector<int> s, vector<int> w, vector<int> t) {
    long long answer = -1;
    long long start = 0;
    long long end = 10e14 * 3;
    answer = end;
    
    while (start <= end)
    {
        long long mid = (start + end) / 2;
        if (search(a, b, g, s, w, t, mid))
        {
            answer = Min(answer, mid);
            end = mid - 1;
        }
        else
            start = mid + 1;
    }
    
    return answer;
}