#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Key point: DFS 탐색을 통해 모든 티켓을 사용 가능한 경우를 탐색한다.
// 가능한 경로가 2개 이상일 경우 알파벳 순서가 앞서는 경로를 return 해야 하므로 tickets를 알파벳 순으로 정렬 후 탐색 시작

vector<string> result;
bool visited[100000001];
bool check = false;


bool DFS(string start, const vector<vector<string>>& tickets, int count)
{
    if(count == tickets.size()) // 모든 티켓을 사용했을 경우
        return true;

    for(int i = 0; i < tickets.size(); ++i)
    {
        if(!visited[i] and tickets[i][0] == start) // 주어진 출발지와 티켓의 출발지가 같을 시
        {
            visited[i] = true;
            result.push_back(tickets[i][1]); // 현재 티켓의 도착지를 도달 가능한 지점으로 저장
            
            bool searchResult = DFS(tickets[i][1], tickets, count + 1); // 현재 티켓의 도착지를 출발지로 하여 이어서 탐색
            if (searchResult) return true;
            
            visited[i] = false;
        }
    }
    
    result.pop_back(); // 마지막으로 설정된 출발지에서부터 남은 모든 공항에 도달할 수 있는 경로 찾을 수 없으므로 pop
    return false;
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    
    sort(tickets.begin(), tickets.end()); // 알파벳 순 정렬
    
    string start = "ICN";
    result.push_back(start);
    
    DFS(start, tickets, 0);
    answer = result;
    
    return answer;
}