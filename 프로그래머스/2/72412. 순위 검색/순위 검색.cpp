#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Key point: map, 비트마스크 사용하여 사용자 데이터 구분하여 저장 후 점수 순으로 정렬한 뒤 이분탐색하여 해당하는 사람이 몇 명인지 계산

// 해당될 수 있는 모든 조건(경우의 수)에 점수 저장 -> Table을 만들어 Bitmask로 만들 수 있는 경우의 수 관리
// Id[cpp] = << 8 Id[java] = << 7 ...
// 점수 순으로 정렬 후에 주어진 점수에 대해 이분 탐색


int Case[16] = {0b000000000, 0b111000000, 0b000110000, 0b000001100, 0b000000011, 0b111110000, 0b111001100, 0b111000011, 0b000111100, 0b000110011, 0b000001111, 0b111111100, 0b111110011, 0b111001111, 0b000111111, 0b111111111};
map<string, int> Id;
map<int, vector<int>> Table;


int LowerBound(const vector<int>& v, int m)
{
    int L = 0, R = v.size() - 1;
    int Mid;
    int Ret = v.size();
    while(L <= R)
    {
        Mid = (L + R) / 2;
        if(v[Mid] < m)
            L = Mid + 1;
        else
        {
            Ret = Mid;
            R = Mid - 1;
        }
    }

    return v.size() - Ret;
}

int FindScore(const string& query)
{
    char ParsedInfo[4][10];
    int MinScore = 0;
    sscanf(query.c_str(), "%s and %s and %s and %s %d", &ParsedInfo[0], &ParsedInfo[1], &ParsedInfo[2], &ParsedInfo[3], &MinScore);
    
    int Mask = 0;
    
    for(int i = 0; i < 4; ++i)
    {
        if(ParsedInfo[i][0] == '-')
            Mask |= Case[i + 1];
        else
            Mask |= Id[ParsedInfo[i]];
    }
    
    return LowerBound(Table[Mask], MinScore);
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer(query.size());
    
    // Initialization
    Id["cpp"] = 1 << 8;
    Id["java"] = 1 << 7;
    Id["python"] = 1 << 6;
    Id["backend"] = 1 << 5;
    Id["frontend"] = 1 << 4;
    Id["junior"] = 1 << 3;
    Id["senior"] = 1 << 2;
    Id["chicken"] = 1 << 1;
    Id["pizza"] = 1;
    
    // Organize and store info using bitmask
    for (const string& inf : info)
    {
        char ParsedInfo[4][10];
        int Score;
        sscanf(inf.c_str(), "%s %s %s %s %d", &ParsedInfo[0], &ParsedInfo[1], &ParsedInfo[2], &ParsedInfo[3], &Score);
        int Mask = 0;
        
        for(int i = 0; i < 4; ++i)
            Mask |= Id[ParsedInfo[i]];
        for(int i = 0; i < 16; ++i)
            Table[(Mask | Case[i])].push_back(Score);
    }
    
    // Sort
    for (auto it = Table.begin(); it != Table.end(); ++it)
    {
        sort((it->second).begin(), (it->second).end());
    }
    
    
    for (int i = 0; i < query.size(); ++i)
        answer[i] = FindScore(query[i]);
    
    return answer;
}