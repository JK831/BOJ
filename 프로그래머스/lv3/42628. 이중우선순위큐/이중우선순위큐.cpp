#include <string>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    priority_queue<int, vector<int>, less<int>> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;
    
    int cnt = 0;
    
    for (int i = 0; i < operations.size(); i++)
    {
        stringstream ss;
        ss.str(operations[i]);
        string temp;
        ss >> temp;
        
        if (temp == "I")
        {
            ss >> temp;
            max_heap.push(stoi(temp));
            min_heap.push(stoi(temp));
            ++cnt;
        }
        else if (temp == "D" && cnt > 0)
        {
            ss >> temp;
            if (temp == "-1")
            {
                min_heap.pop();
            }
            else if (temp == "1")
            {
                max_heap.pop();
            }
            --cnt;
            
            if (cnt == 0)
            {
                while (max_heap.empty() == false)
                {
                    max_heap.pop();
                }
                while (min_heap.empty() == false)
                {
                    min_heap.pop();
                }
            }
        }
    }
    
    if (cnt == 0)
    {
        answer.push_back(0);
        answer.push_back(0);
    }
    
    else
    {
        answer.push_back(max_heap.top());
        answer.push_back(min_heap.top());
    }
    
    return answer;
}