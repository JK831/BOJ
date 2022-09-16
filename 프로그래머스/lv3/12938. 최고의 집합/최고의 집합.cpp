#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer;
    
    if (n > s)
        answer.push_back(-1);
    else
    {   int quotient = s / n;
        int remain = s % n;
        for (int i = 0; i < n; i++)
        {
            if (i >= n - remain)
                answer.push_back(quotient + 1);
            else
                answer.push_back(quotient);
        }
    }
    return answer;
}