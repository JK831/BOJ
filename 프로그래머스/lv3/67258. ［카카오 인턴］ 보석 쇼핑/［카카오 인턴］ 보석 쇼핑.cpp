#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer = {1, (int)gems.size()};
    map<string, int> m;
    int start = 0;
    int end = 0;
    int total = 0;
    int Min = gems.size() - 1;
    
    for (string s: gems)
    {
        m[s]++;
    }
    
    total = m.size();
    m.clear();
    
    while (true)
    {
        if (m.size() == total)
        {
            if (end - start < Min)
            {
                Min = end - start;
                answer[0] = start + 1;
                answer[1] = end;
            }
            
            if (m[gems[start]] == 1)
            {
                m.erase(gems[start]);
                start++;
            }
            else
            {
                m[gems[start]]--;
                start++;
            }
        }
        else if (end == gems.size())
            break;
        else
        {
            m[gems[end]]++;
            end++;
        }
    }
    
    return answer;
}