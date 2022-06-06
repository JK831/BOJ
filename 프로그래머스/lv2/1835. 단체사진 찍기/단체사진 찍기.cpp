#include <string>
#include <vector>

using namespace std;

int answer;
bool Select[8];
char IToC[8] = {'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T'};

void DFS(int count, char Arr[], const vector<string>& data)
{
    if (count == 8)
    {
        for (int i = 0; i < data.size(); i++)
        {
            char N1 = data[i][0];
            char N2 = data[i][2];
            char cond = data[i][3];
            int dist = data[i][4] - '0';
            dist++;
            
            int Idx, IIdx;
            Idx = IIdx = -1;
            
            for (int j = 0; j < 8; j++)
            {
                if (Arr[j] == N1) Idx = j;
                if (Arr[j] == N2) IIdx = j;
                if (Idx != -1 && IIdx != -1) break;
            }
            
            if (cond == '=' && abs(Idx - IIdx) != dist) return;
            if (cond == '>' && abs(Idx - IIdx) <= dist) return;
            if (cond == '<' && abs(Idx - IIdx) >= dist) return;
        }
        
        answer++;
        return;
    }
    
    for(int i = 0; i < 8; i++)
    {
        if (Select[i] == true) continue;
        Select[i] = true;
        Arr[count] = IToC[i];
        DFS(count + 1, Arr, data);
        Select[i] = false;
    }
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    answer = 0;
    char Arr[8] = {NULL, };
    DFS(0, Arr, data);
    return answer;
}