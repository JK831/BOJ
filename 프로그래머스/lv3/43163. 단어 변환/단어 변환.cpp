#include <string>
#include <vector>

using namespace std;

int answer = 50;

bool visited[50] = {false, };

bool check_diff(const string& a, const string& b)
{
    int diff_count = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            diff_count++;
    }
    
    if (diff_count == 1) return true;
    return false;
}

void DFS(const string& curWord, const string& target, const vector<string>& words, int changeCount)
{
    if (answer <= changeCount) return;
    
    if (curWord == target)
    {
        answer = min(answer, changeCount);
        return;
    }
    
    for (int i = 0; i < words.size(); i++)
    {
        if (visited[i] == false && check_diff(curWord, words[i]))
        {
            visited[i] = true;
            DFS(words[i], target, words, changeCount + 1);
            visited[i] = false;
        }
    }
}

int solution(string begin, string target, vector<string> words) {
    DFS(begin, target, words, 0);
    
    if (answer == 50) answer = 0;
    return answer;
}