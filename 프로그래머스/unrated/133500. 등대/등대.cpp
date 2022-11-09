/*------문제 풀이 방법------*/
// 리프 등대와 연결된 등대를 켜는 것이 등대를 최소한으로 켤 수 있는 방법
// 따라서 이미 불이 켜진 등대와 그 등대와 연결된 리프 노드들을 등대 set에서 제외하고
// 기존의 등대를 리프 등대로 만들어 연결된 등대를 켜는 식으로 반복 진행한다

// DFS를 사용하여 리프 등대들과 연결된 등대들부터 켜는 방식으로 진행한다.
// 첫 등대부터 DFS 시작, 각 등대들마다 불이 켜지지 않았고 방문하지 않은 등대 찾는다.
// 연결된 등대가 하나라면 (set의 size가 1이라면) 리프 등대
// 현재 등대가 켜지지 않았고 리프 등대라면 해당 등대와 연결된 등대를 켜주고 리프 등대를 연결된 등대의 연결 상태를 나타내는 set에서 삭제(구조상 for문이 그 set에서 등대들을 꺼내오기 때문에 함수 내에서 직접 삭제하진 않고, 대신 미리 연결된 등대들의 숫자를 저장하고 그 숫자를-- 해준다.)
// 위 과정 진행 시 리프 등대와 연결되어있던 등대가 리프 등대가 된다.
// 따라서 위 과정을 반복하면 리프 등대와 연결된 등대들을 켜주는 식으로 동작하여 최소 값을 구할 수 있다.
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

const int N = 100001;
bool lighting[N] = {false};
bool visited[N] = {false};

// 리프 등대들부터 키기 시작한다.
void TurnOnLight(int& answer, int InIndex, int InPrevIndex, vector<unordered_set<int>>& InLinkedSet, unsigned long& InCount)
{
    if (visited[InIndex])
        return;

    visited[InIndex] = true;
    
    unsigned long newCount = InLinkedSet[InIndex].size();

    for (int node : InLinkedSet[InIndex])
    {
        if (lighting[node] == false && visited[node] == false)
        {
            TurnOnLight(answer, node, InIndex, InLinkedSet, newCount);
        }
    }
    
    if (newCount == 1)
    {
        InCount--;
        
        if (lighting[InIndex] || lighting[InPrevIndex])
            return;

        lighting[InPrevIndex] = true;
        answer++;
        return;
    }
}


int solution(int n, vector<vector<int>> lighthouse) {
    int answer = 0;
    vector<unordered_set<int>> linkedSetVector(N); 
    
    // 특정 번호 등대가 어떤 등대들과 연결 되었는지 index에 해당하는 set을 통해 나타낸다.
    for (int i = 0; i < lighthouse.size(); i++)
    {
        linkedSetVector[lighthouse[i][0]].insert(lighthouse[i][1]);
        linkedSetVector[lighthouse[i][1]].insert(lighthouse[i][0]);
    }
    
    unsigned long indexOneLinkedSize = linkedSetVector[1].size();
    TurnOnLight(answer, 1, 0, linkedSetVector, indexOneLinkedSize);
    

    return answer;
}

