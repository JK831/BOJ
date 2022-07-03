#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct compare
{
    bool operator()(vector<int> a, vector<int> b)
    {
        return a[1] > b[1];
    }
};

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    priority_queue<vector<int>, vector<vector<int>>, compare> pq;
    
    int current_time = 0;
    int task_cnt = 0;
    
    sort(jobs.begin(), jobs.end());
    
    while (task_cnt < jobs.size() || !pq.empty())
    {
        if (task_cnt < jobs.size() && jobs[task_cnt][0] <= current_time)
        {
            pq.push(jobs[task_cnt++]);
            continue;
        }
        
        if (!pq.empty())
        {
            current_time += pq.top()[1];
            answer += current_time - pq.top()[0];
            pq.pop();
        }
        else
        {
            current_time = jobs[task_cnt][0];
        }
    }
    
    return answer / jobs.size();
}