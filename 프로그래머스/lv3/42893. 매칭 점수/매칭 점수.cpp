#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Key point: 특정 웹페이지에 특정 단어가 '대소문자 관계 없이' 몇 번 나오는지 체크해야 한다.
// 구해야 할 것 - 기본 점수, 외부링크 수, 링크 점수, 매칭 점수

// transform 함수를 사용하여 모든 단어 대문자로 변환
// transfrom(begin, end, position, function): begin 부터 end 까지의 원소들을 function으로 실행한 후, 그 결과를 position 부터 저장하는 함수.

// isalpah를 사용하여 단어 단위로 체크한다.
// isalpah: 주어진 문자가 알파벳 소문자면 2, 알파벳 대문자면 1, 알파벳이 아니라면 0을 반환해 주는 함수
 
// 링크 점수 = 기본 점수 / 외부링크 수
// 매칭 점수 = 기본 점수 + 링크 점수

struct Page
{
    int Idx;
    int BasicPoint;
    vector<string> OutLinkList;
    double LinkPoint;
    double MatchPoint;
};
 
string Word;
map<string, int> PageNum;
vector<Page> Pages;
 
bool Cmp(Page A , Page B)
{
    if (A.MatchPoint >= B.MatchPoint)
    {
        if (A.MatchPoint == B.MatchPoint)
        {
            if (A.Idx < B.Idx)
            {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}
 
string ToUpper(string Str)
{
    transform(Str.begin(), Str.end(), Str.begin(), ::toupper);
    return Str;
}

// URL 추출
string FindURL(string Str)
{
    string Target = "<META PROPERTY=\"OG:URL\" CONTENT=\"HTTPS://";
    int Idx = Str.find(Target); Idx += Target.length();
    string URL = "";
    while (Str[Idx] != '\"') URL += Str[Idx++];
    return URL;
}

// Body 내부에 있는 단어들 탐색
int FindWord(string Str)
{
    string Target1 = "<BODY>";
    string Target2 = "/<BODY>";
    int Idx1 = Str.find(Target1); Idx1 += Target1.length();
    int Idx2 = Str.find(Target2);
    Str = Str.substr(Idx1, Idx2 - Idx1);
 
    string Cur = "";
    int Cnt = 0;
    for (int i = 0; i < Str.length(); i++)
    {
        if (isalpha(Str[i]) == 0)
        {
            if (Cur == Word) Cnt++;
            Cur = "";
        }
        else Cur += Str[i];
    }
    return Cnt;
}

// 연결된 외부링크 파싱
vector<string> FindOutLink(string Str)
{
    vector<string> Result;
    string Target = "<A HREF=\"HTTPS://";
    int Idx = Str.find(Target); 
    while (Idx != -1)
    {
        Idx += Target.length();
        string Cur = "";
        while (Str[Idx] != '\"') Cur += Str[Idx++];
        Result.push_back(Cur);
        Str = Str.substr(Idx);
        Idx = Str.find(Target);
    }
    return Result;
}

// 링크 점수 계산
void CalculateLinkPoint()
{
    for (int i = 0; i < Pages.size(); i++)
    {
        vector<string> V = Pages[i].OutLinkList;
        int Size = V.size();
        for (int j = 0; j < V.size(); j++)
        {
            string Str = V[j];
            if (PageNum[Str] == 0) continue;
            int TargetIdx = PageNum[Str] - 1;
            Pages[TargetIdx].LinkPoint += ((double)Pages[i].BasicPoint / (double)Size);
        }
    }
    for (int i = 0; i < Pages.size(); i++)
    {
        Pages[i].MatchPoint = (double)Pages[i].BasicPoint + (double)Pages[i].LinkPoint;
    }
    sort(Pages.begin(), Pages.end(), Cmp);
}
 
void Function(vector<string> V)
{
    for (int i = 0; i < V.size(); i++)
    {
        string Str = ToUpper(V[i]);
        string URL = FindURL(Str);
        PageNum[URL] = i + 1;
        int BP = FindWord(Str);
        vector<string> OutLink = FindOutLink(Str);
        Pages.push_back({ i, BP, OutLink, 0.0, 0.0 });
    }
    CalculateLinkPoint();
}
 
int solution(string word, vector<string> pages) {
    int answer = 0;
    Word = ToUpper(word);
    Function(pages);
    answer = Pages[0].Idx;
    return answer;
}
