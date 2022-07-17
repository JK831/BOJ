#include <string>
#include <vector>
#include <set>

using namespace std;

bool visited[8];
set<string> s;

void dfs(const vector<string>& user_id, const vector<string>& banned_id, int idx)
{
    if (idx == banned_id.size())
    {
        string str = "";
        
        for (int i = 0; i < user_id.size(); i++)
        {
            if (visited[i] == true)
            {
                str += user_id[i];
            }
        }
        s.insert(str);
        return;
    }
    
    for (int i = 0; i < user_id.size(); i++)
    {
        if (visited[i] == true)
            continue;
        if (user_id[i].size() != banned_id[idx].size())
            continue;
        
        bool check = true;
        for (int j = 0; j < user_id[i].size(); j++)
        {
            if (banned_id[idx][j] == '*')
                continue;
            if (user_id[i][j] != banned_id[idx][j])
            {
                check = false;
                break;
            }
        }
        
        if (check)
        {
            visited[i] = true;
            dfs(user_id, banned_id, idx + 1);
            visited[i] = false;
        }
    }
}


int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;
    dfs(user_id, banned_id, 0);
    answer = s.size();
    return answer;
}