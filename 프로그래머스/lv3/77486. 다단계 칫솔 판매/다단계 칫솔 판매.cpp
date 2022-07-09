#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

map<string, string> refer;
map<string, int> cost;

void DFS(string name, int money)
{
    if (name == "center")
        return;
    if (money < 1)
        return;
    cost[name] += money - floor(money * 0.1);
    DFS(refer[name], floor(money * 0.1));
    
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;
    for (int i = 0; i < enroll.size(); i++)
    {
        string name = enroll[i];
        string ref = referral[i];
        
        if (ref == "-")
            refer.insert({name, "center"});
        else
            refer.insert({name, ref});
        
        cost.insert({name, 0});
    }
    
    for (int i = 0; i < seller.size(); i++)
    {
        string name = seller[i];
        int money = amount[i] * 100;
        
        DFS(name, money);
    }
    
    for (int i = 0; i < enroll.size(); i++)
    {
        answer.push_back(cost[enroll[i]]);
    }
    
    return answer;
}