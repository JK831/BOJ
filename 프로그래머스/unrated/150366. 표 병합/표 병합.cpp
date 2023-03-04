#include <string>
#include <vector>
#include <sstream>

using namespace std;

#define N 50
#define CHART_SIZE N * N

int parent[CHART_SIZE + 1];
string chart[CHART_SIZE + 1];

// Key point: Union-Find를 사용하여 셀을 병합하고 값을 관리한다.
// 셀을 병합할 때 첫번째 셀의 root 를 두번째 셀의 parent로 지정
// 셀을 병합할 때 두번째 셀의 값은 비워지고 첫번째 셀(첫번째 셀의 root)에 첫번째 셀의 값이 쓰여진다.(값이 존재할 시. 값이 존재하지 않을 시엔 두번째 셀의 값이 쓰임.)
// 결과적으로 셀을 병합하면 root 셀에만 값이 존재하게 된다.
// 병합 해제할 때에는 지정한 셀 번호에 값이 쓰여지므로 해당 셀의 root 의 값을 저장해둔 뒤 병합되어 있는(같은 root를 가지고 있는) 셀들을 저장해두고
// 병합되었던 셀들의 parent를 자기 자신으로 수정해준다.

// 2차원 배열을 사용할 시 메모리 공간 낭비가 생기므로 1차원 배열로 직렬화하여 사용


int Find(int a) // 해당 셀의 root를 찾아 return
{
    if (parent[a] == a)
        return a;
    return Find(parent[a]);
}

void Union(int a, int b) // b 셀을 a 셀이 속한 집합으로 합친다.
{
    a = Find(a);
    b = Find(b);
    
    if (a != b)
        parent[b] = a;
}

int SerializeNum(int row, int col) // row, column을 이용하여 1차원 배열의 인덱스에 접근하기 위한 함수
{
    return (row - 1) * N + col;
}

vector<string> solution(vector<string> commands) {
    vector<string> answer;
    
    // Initialization
    for (int i = 1; i <= CHART_SIZE; i++)
    {
        parent[i] = i;
        chart[i] = "";
    }
    
    for (auto command : commands)
    {
        // string split
        string word;
        vector<string> words;
        stringstream sstream(command);
        while (getline(sstream, word, ' '))
            words.push_back(word);
        
       
        if (words[0] == "UPDATE")
        {
            if (words.size() == 4)
            {
                int root = Find(SerializeNum(stoi(words[1]), stoi(words[2]))); // Update 하려는 셀의 root 셀 찾는다.
                chart[root] = words[3]; // root 셀 값 변경
            }
            else
            {
                for (int i = 1; i < CHART_SIZE; i++)
                {
                    if (chart[i] == words[1])
                        chart[i] = words[2];
                }  
            }
        }
        else if (words[0] == "MERGE")
        {
            int firstCell = SerializeNum(stoi(words[1]), stoi(words[2])); // Serialized 된 Cell의 번호를 가져온다.
            int secondCell = SerializeNum(stoi(words[3]), stoi(words[4])); // Same as above
            
            int firstRoot = Find(firstCell), secondRoot = Find(secondCell);
            
            if (firstRoot == secondRoot)
                continue;
            
            // 병합하려는 첫번째 셀에 값이 없다면 두번째 셀에서 값을 가져온다.
            string rootString = chart[firstRoot].empty() ? chart[secondRoot] : chart[firstRoot]; 
            
            chart[secondRoot] = ""; // 두번째 셀은 비워준다.
            chart[firstRoot] = rootString;
            
            Union(firstRoot, secondRoot); // 병합
        }
        else if (words[0] == "UNMERGE")
        {
            int cell = SerializeNum(stoi(words[1]), stoi(words[2]));
            int root = Find(cell);
            string rootString = chart[root];
            
            chart[root] = "";
            chart[cell] = rootString;
            
            // 병합 해제 될 셀들을 구한 후 병합 해제 (parent 초기화).
            vector<int> unmergedList;
            for (int i = 1; i <= CHART_SIZE; ++i)
            {
                if (Find(i) == root)
                    unmergedList.push_back(i);
            }
            
            for (int beUnmerged : unmergedList)
                parent[beUnmerged] = beUnmerged;
        }
        else if (words[0] == "PRINT")
        {
            int cell = SerializeNum(stoi(words[1]), stoi(words[2]));
            int root = Find(cell);
            if (chart[root].empty())
                answer.push_back("EMPTY");
            else
                answer.push_back(chart[root]);
        }
         
    }
    
    return answer;
}